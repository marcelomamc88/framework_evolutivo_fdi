import requests
from flask import Flask, request, jsonify, render_template
from river import cluster
from river import stream
import asyncio
from threading import Thread
from pymongo import MongoClient


# X = [[1, 0.5], [1, 0.625], [1, 0.75], [1, 1.125], [1, 1.5], [1, 1.75], [4, 1.5], [4, 2.25], [4, 2.5], [4, 3],[4, 3.25], [4, 3.5]]

app = Flask(__name__)
app.config['CORS_HEADERS'] = 'Content-Type'
model = None
db_unknown = None


def initialize_model():
    global model
    global db_unknown

    model = dbstream = cluster.DBSTREAM(
        clustering_threshold=2.3,
        fading_factor=0.75,
        cleanup_interval=1,
        intersection_factor=0.1,
        minimum_weight=3)

    db = MongoClient('localhost', 27017).fdi
    db_unknown = db.unknown

    print('clusterer initialized - clusterer componenet')

@app.route('/clusterer/', methods=['GET'])
def info():
    if (model == None):
        initialize_model()

    c = model

    clusters = { k : {'center': cluster.center,
                            'last_update': cluster.last_update,
                            'weight': cluster.weight}
          for i, (k, cluster) in enumerate(c.clusters.items())}

    micro_clusters = { k : {'center': mc.center,
                            'last_update': mc.last_update,
                            'weight': mc.weight}
          for i, (k, mc) in enumerate(c.micro_clusters.items())}

    return jsonify({
        'centers': c.centers,
        'clusters': clusters,
        'micro_clusters': micro_clusters,
        'n_clusters': c.n_clusters})

@app.route('/clusterer/learn', methods=['GET'])
def clusterer_learn():

    global db_unknown
    global model

    if (model == None):
        initialize_model()

    content = request.get_json()
    _x = content['x']

    x = {k: v for i, (k, v) in enumerate(_x.items())}

    c = model

    c.learn_one(x)
    c._recluster()

    y_pred = c.predict_one(x) + 1
    n_clusters = c.n_clusters

    print(x)
    print(y_pred)
    print(n_clusters)


    db_unknown.insert_one({
        "timestamp": 202111141211,
        "sensors": x,
        "class": y_pred
    })

    return jsonify({'x': x,
                    'y': y_pred,
                    'n_clusters': n_clusters})




if __name__ == '__main__':
    app.run(port=5002, debug=True)