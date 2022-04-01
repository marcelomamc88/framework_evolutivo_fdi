from flask import Flask, request, jsonify
import requests
import pandas as pd
import torch
import numpy as np
from torch import nn
from pymongo import MongoClient
import json
import pickle

class Autoencoder(nn.Module):
    def __init__(self):
        super().__init__()
        self.encoder = nn.Sequential(
            nn.Linear(54, 32),
            nn.ReLU(),
            nn.Linear(32, 9),
        )

        self.decoder = nn.Sequential(
            nn.Linear(9, 32),
            nn.ReLU(),
            nn.Linear(32, 54),
            nn.Tanh()
        )

    def forward(self, x):
        return self.decoder(self.encoder(x))

def start_database():
    global detector_metadata

    fdi_db = MongoClient('localhost', 27017).fdi
    detector_metadata = fdi_db.detector_metadata


app = Flask(__name__)
app.config['CORS_HEADERS'] = 'Content-Type'
detector_metadata = None
net = None
scaler = None
loss_function = nn.L1Loss()

start_database()

url = 'http://127.0.0.1:5001/classifier'
headers = {'Accept' : 'application/json', 'Content-Type' : 'application/json'}

def send(endpoint, params_dict):
    return requests.get(url+endpoint, data=json.dumps(params_dict), headers=headers).json()

def initialize():
    global net
    global scaler

    net = Autoencoder()
    net.load_state_dict(torch.load('autoencoder_model.pt'))

    scaler = pickle.load(open('scaler.pkl','rb'))


    print('clusterer initialized - detector componenet')

@app.route('/detector/predict', methods=['GET'])
def detector_precict():
    if (net == None):
        initialize()

    meta = list(detector_metadata.find({}))

    content = request.get_json()
    x = pd.read_json(content['x'])
    y = content['y']
    _x = scaler.transform(x).reshape(1,-1)
    real = _x.astype(np.float32)

    regenerate = net(torch.from_numpy(real))
    l = loss_function(regenerate, torch.from_numpy(real)).item()

    if (l <= meta[0]['threshold']):
        return jsonify({'y_hat': 0})
    else:
        _x_ = x.to_numpy().reshape(-1)
        r = send('/predict', {'x': pd.DataFrame(_x_).T.to_json(), 'y': y}) #call classifier
        return jsonify({'y_hat': r['y_hat']})

@app.route('/detector/learn', methods=['GET'])
def clusterer_learn():
    if (net == None):
        initialize()

    content = request.get_json()
    _x = content['x']

    x = {k: v for i, (k, v) in enumerate(_x.items())}
    dbstream = net

    dbstream.learn_one(x)
    dbstream._recluster()

    y_pred = dbstream.predict_one(x) + 1
    n_clusters = dbstream.n_clusters

    print(x)
    print(y_pred)
    print(n_clusters)

    return jsonify({'x': x,
                    'y': y_pred,
                    'n_clusters': n_clusters})



if __name__ == '__main__':
    app.run(port=5000, debug=True, use_reloader=False)
