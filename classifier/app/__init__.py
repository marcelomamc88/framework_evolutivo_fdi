import requests
from flask import Flask, request, jsonify, render_template
from river import cluster, stream
from river.utils import numpy2dict
from pymongo import MongoClient
import numpy as np
from matplotlib import cm
from matplotlib import pyplot as plt
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
from matplotlib.figure import Figure
from matplotlib.colors import ListedColormap, LinearSegmentedColormap
from mpl_toolkits.mplot3d import Axes3D
import pandas as pd
from sklearn.preprocessing import LabelEncoder
from river import linear_model, metrics, multiclass, preprocessing


app = Flask(__name__)
app.config['CORS_HEADERS'] = 'Content-Type'

model = None


@app.route('/classifier/', methods=['GET'])
def endpoint_info():
    pass

@app.route('/classifier/predict', methods=['GET'])
def endpoint_predict():
    r = request.get_json()

    y_pred = model.predict_one(r['x'])

    return jsonify({'y_pred': y_pred})


@app.route('/classifier/learn', methods=['GET'])
def endpoint_learn():
    r = request.get_json()

    learn(r['x'], r['y'])
    print({'msg': 'x,y has been learned...'})
    return jsonify({'msg': 'x,y has been learned...'})


def initialize():
    start_database()
    restart_model()
    print('classifier component has been initialized...')


def start_database():
    pass


def restart_model():
    global model

    scaler = preprocessing.StandardScaler()
    ovr = multiclass.OneVsRestClassifier(linear_model.LogisticRegression())
    model = scaler | ovr
    metric = metrics.MacroF1()

    #start_metadata()
    #retrain()



def learn(x, y):
    global model

    model.learn_one(x, y)

    return model


if __name__ == '__main__':
    initialize()
    app.run(port=5001, debug=True)