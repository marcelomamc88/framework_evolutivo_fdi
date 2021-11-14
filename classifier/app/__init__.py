import requests
from flask import Flask, request, jsonify, render_template
from river import cluster
from river import stream
import asyncio
from threading import Thread

# X = [[1, 0.5], [1, 0.625], [1, 0.75], [1, 1.125], [1, 1.5], [1, 1.75], [4, 1.5], [4, 2.25], [4, 2.5], [4, 3],[4, 3.25], [4, 3.5]]

app = Flask(__name__)
app.config['CORS_HEADERS'] = 'Content-Type'
clusterer = None


def initialize_clusterer():
    global clusterer
    clusterer = dbstream = cluster.DBSTREAM(
        clustering_threshold=2.3,
        fading_factor=0.75,
        cleanup_interval=1,
        intersection_factor=0.1,
        minimum_weight=3)

    print('clusterer initialized - clusterer componenet')


@app.route('/clusterer/learn', methods=['GET'])
def clusterer_learn():
    if (clusterer == None):
        initialize_clusterer()

    content = request.get_json()
    _x = content['x']

    x = {k: v for i, (k, v) in enumerate(_x.items())}
    print(x)
    dbstream = clusterer

    dbstream.learn_one(x)
    dbstream._recluster()

    return jsonify({'x': x,
                    'y': dbstream.predict_one(x) + 1,
                    'n_clusters': dbstream.n_clusters})


if __name__ == '__main__':
    app.run(port=5001, debug=True)