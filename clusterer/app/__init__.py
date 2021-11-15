import requests
from flask import Flask, request, jsonify, render_template
from river import cluster
from river import stream
import asyncio
from threading import Thread
from pymongo import MongoClient
import numpy as np
from matplotlib import cm
from matplotlib import pyplot as plt
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
from matplotlib.figure import Figure
from matplotlib.colors import ListedColormap, LinearSegmentedColormap
from mpl_toolkits.mplot3d import Axes3D
import io
import base64
import datetime

# X = [[1, 0.5], [1, 0.625], [1, 0.75], [1, 1.125], [1, 1.5], [1, 1.75], [4, 1.5], [4, 2.25], [4, 2.5], [4, 3],[4, 3.25], [4, 3.5]]

app = Flask(__name__)
app.config['CORS_HEADERS'] = 'Content-Type'

model = None
unknown_collection = None
clusterer_metadata_collection = None


@app.route('/clusterer/', methods=['GET'])
def endpoint_info():
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
def endpoint_learn():
    global unknown_collection

    x = {k: v for i, (k, v) in enumerate(request.get_json()['x'].items())}

    c = learn(x)

    y_pred = c.predict_one(x) + 1

    unknown_collection.insert_one({
        "timestamp": datetime.datetime.now(),
        "sensors": x,
        "cluster": y_pred
    })

    return jsonify({'x': x, 'y': y_pred, 'n_clusters': c.n_clusters})


@app.route('/clusterer/show', methods=['GET'])
def endpoint_show():
    color = cm.hsv(np.linspace(0, 1, 20))
    unknowns = list(unknown_collection.find({}))

    # Generate plot
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    ax.set_xlabel('dim1')
    ax.set_ylabel('dim2')
    ax.set_zlabel('dim3')

    ax.scatter( list(map(lambda x: x['sensors']['0'], unknowns)),
                list(map(lambda x: x['sensors']['1'], unknowns)),
                list(map(lambda x: x['sensors']['2'], unknowns)),
                c=list(map(lambda x: color[x['cluster']], unknowns)),
                marker='.')

    ax.scatter( [centers['0'] for i, (k, centers) in enumerate(model.centers.items())],
                [centers['1'] for i, (k, centers) in enumerate(model.centers.items())],
                [centers['2'] for i, (k, centers) in enumerate(model.centers.items())],
                c='blue',
                marker='*')

    # Convert plot to PNG image
    pngImage = io.BytesIO()
    FigureCanvas(fig).print_png(pngImage)

    # Encode PNG image to base64 string
    pngImageB64String = "data:image/png;base64,"
    pngImageB64String += base64.b64encode(pngImage.getvalue()).decode('utf8')

    return render_template("clusters.html", image=pngImageB64String)


def initialize():
    start_database()
    start_model()

    print('clusterer component has been initialized...')


def start_database():
    global unknown_collection
    global clusterer_metadata_collection

    fdi_db = MongoClient('localhost', 27017).fdi
    unknown_collection = fdi_db.unknown
    clusterer_metadata_collection = fdi_db.clusterer_metadata


def start_model():
    global model

    model = cluster.DBSTREAM(
        clustering_threshold=2.3,
        fading_factor=0.75,
        cleanup_interval=1,
        intersection_factor=0.1,
        minimum_weight=3)

    start_metadata()
    retrain()


def start_metadata():
    global clusterer_metadata_collection

    clusterer_metadata = get_metadata()
    if clusterer_metadata:
        clusterer_metadata_collection.update_one({"_id" : clusterer_metadata["_id"]},
                                                 {"$set": {"last_start": datetime.datetime.now()}})
    else:
        clusterer_metadata_collection.insert_one({
            "create": datetime.datetime.now(),
            "last_start": datetime.datetime.now()
        })


def retrain():
    global unknown_collection

    unknowns = unknown_collection.find({})

    for unknown in unknowns:
        learn(unknown['sensors'])


def get_metadata():
    return clusterer_metadata_collection.find_one()


def learn(x):
    global model

    c = model

    c.learn_one(x)
    c._recluster()

    return c


if __name__ == '__main__':
    initialize()
    app.run(port=5002, debug=True)
