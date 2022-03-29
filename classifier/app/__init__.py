from flask import Flask, request, jsonify, render_template
from pymongo import MongoClient
import pickle
import pandas as pd
import numpy as np

def start_database():
    global classifier_metadata

    fdi_db = MongoClient('localhost', 27017).fdi
    classifier_metadata = fdi_db.classifier_metadata


app = Flask(__name__)
app.config['CORS_HEADERS'] = 'Content-Type'
classifier_metadata = None
clf = None
scaler = None

start_database()

def initialize():
    global scaler
    global clf

    scaler = pickle.load(open('scaler.pkl','rb'))
    clf = pickle.load(open('classifier_model.pkl','rb'))


@app.route('/classifier/predict', methods=['GET'])
def endpoint_predict():
    if (clf == None):
        initialize()

    meta = list(classifier_metadata.find({}))

    '''content = request.get_json()
    x = pd.read_json(content['x']).to_numpy().reshape(1,-1)'''

    '''pred = clf.predict_proba(x)
    threshold = [0.9, 0.66, 0.75]
    phi = threshold[0]
    for n in pred:
        if n[1] >= phi:
            r = 1
        elif n[2] >= phi:
            r = 2
        else:
            r = -1'''

    return jsonify({'y_hat': 9}) #call classifier



if __name__ == '__main__':
    app.run(port=5007, debug=True)