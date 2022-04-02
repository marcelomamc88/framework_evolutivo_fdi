from flask import Flask, request, jsonify
import requests
import pandas as pd
import torch
import numpy as np
from pymongo import MongoClient
from sklearn.cluster import  AgglomerativeClustering
from sklearn.preprocessing import StandardScaler
from sklearn.metrics.cluster import v_measure_score, silhouette_score
from bson.objectid import ObjectId

def start_database():
    global unknowns

    fdi_db = MongoClient('localhost', 27017).fdi
    unknowns = fdi_db.unknown

app = Flask(__name__)
app.config['CORS_HEADERS'] = 'Content-Type'
unknowns = None
scaler = None
clusterer = None

start_database()


def initialize():
    global scaler
    global clusterer

    scaler = StandardScaler()
    clusterer = AgglomerativeClustering(n_clusters=300, affinity='euclidean', linkage='ward')

    print('clusterer has been initialized')

start_database()

@app.route('/clusterer/group', methods=['GET'])
def clusterer_group():

    initialize()

    y_pred = []
    sensors = []
    y = []

    data = list(unknowns.find({}))

    for d in data:
        sensors.append(d['sensors'])
        y.append(d['y'])

    y_df = pd.DataFrame(y)
    sensors_df = pd.DataFrame(sensors)

    pred = clusterer.fit_predict(scaler.fit_transform(sensors_df))

    for n, p in enumerate(pred):

        y_pred.append(p)
        unknowns.update_one({'_id': ObjectId(str(data[n]['_id']))}, {'$set': {'cluster': int(p)}})

    silhouette = silhouette_score(scaler.transform(sensors_df), y_pred)
    homogeneity = v_measure_score(y, y_pred, beta=0) # 0 plus homogeneity | 2 completeness


if __name__ == '__main__':
    app.run(port=5002, debug=True, use_reloader=False)
