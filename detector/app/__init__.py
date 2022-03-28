from flask import Flask, request, jsonify
from river import cluster
import pandas as pd
import torch
import numpy as np
from torch import nn
from pymongo import MongoClient

def start_database():
    global detector_metadata

    fdi_db = MongoClient('localhost', 27017).fdi
    detector_metadata = fdi_db.detector_metadata


app = Flask(__name__)
app.config['CORS_HEADERS'] = 'Content-Type'
detector_metadata = None
net = None
loss_function = nn.L1Loss()

start_database()

class Autoencoder(nn.Module):
    def __init__(self, encode_l, decode_l):
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


def initialize():
    global net

    net = torch.load('autoencoder_model.pt')

    print('clusterer initialized - detector componenet')

@app.route('/detector/predict', methods=['GET'])
def detector_precict():
    if (net == None):
        initialize()

    meta = list(detector_metadata.find({}))

    content = request.get_json()
    _x = pd.read_json(content['x'])
    real = _x.to_numpy().reshape(1,-1).astype(np.float32)

    regenerate = net(torch.from_numpy(real))
    l = loss_function(regenerate, torch.from_numpy(real)).item()

    if (l <= meta[0]['threshold']):
        return jsonify({'y_hat': 0})
    else:
        return jsonify({'y_hat': 1}) #call classifier

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
    app.run(port=5000, debug=True)
