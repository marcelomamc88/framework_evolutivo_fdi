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
from river import ensemble
from river import neighbors
from river import tree


app = Flask(__name__)
app.config['CORS_HEADERS'] = 'Content-Type'

model = None


@app.route('/classifier/init', methods=['GET'])
def endpoint_init():
    #get type model
    #builder model
    r = request.get_json()
    initialize(type_model= r['type_model'])
    return jsonify({'msg': 'call init endpoint classifier... model: ' + str(model)})


@app.route('/classifier/', methods=['GET'])
def endpoint_info():
    pass


@app.route('/classifier/predict', methods=['GET'])
def endpoint_predict():
    global model

    r = request.get_json()

    if (r['type'] == 'proba'):
        y_pred = model.predict_proba_one(r['x'])
    else:
        y_pred = model.predict_one(r['x'])


    return jsonify({'y_pred': y_pred})


@app.route('/classifier/learn', methods=['GET'])
def endpoint_learn():

    r = request.get_json()

    learn(r['x'], int(r['y']))

    return jsonify({'msg': 'x,y has been learned...'})


def initialize(type_model = 1):
    start_model(type_model)


def start_model(type_model = 1):
    global model

    model = builder_model(type_model)


def learn(x, y):
    global model

    model.predict_one(x) #needed ... ?!?
    model = model.learn_one(x, y)


def builder_model(type_model = 1):
    if (type_model == 1):
        model = builder_ovr_class_plus_lr()
    elif (type_model == 2):
        model = builder_ensemble_bagging()
    elif (type_model == 3):
        model = builder_knn()
    elif (type_model == 4):
        model = builder_knn_adwin()
    elif (type_model == 5):
        model = builder_hoeffding_adptive_tree()

    return model


def builder_ovr_class_plus_lr():
    scaler = preprocessing.StandardScaler()
    ovr = multiclass.OneVsRestClassifier(linear_model.LogisticRegression())
    model = scaler | ovr
    #metric = metrics.MacroF1()

    return model

def builder_ensemble_bagging():
    return ensemble.BaggingClassifier(
        model=(
            preprocessing.StandardScaler() |
            linear_model.LogisticRegression()
        ),
        n_models=3,
        seed=42
    )


def builder_knn():
    return ensemble.BaggingClassifier(
        model=(
            preprocessing.StandardScaler() |
            neighbors.KNNClassifier()
        )
    )


def builder_knn_adwin():
    return ensemble.BaggingClassifier(
        model=(
            preprocessing.StandardScaler() |
            neighbors.KNNADWINClassifier()
        )
    )

def builder_hoeffding_adptive_tree():
    return preprocessing.StandardScaler() | tree.HoeffdingAdaptiveTreeClassifier(seed=0)



if __name__ == '__main__':
    app.run(port=5001, debug=True)