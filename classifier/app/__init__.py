from flask import Flask, request, jsonify, render_template
from pymongo import MongoClient
import pickle
import pandas as pd
import numpy as np
import datetime

app = Flask(__name__)
app.config['CORS_HEADERS'] = 'Content-Type'

clf = None
scaler = None

classifier_metadata = None
unknown_collection = None

def start_database():
    global classifier_metadata
    global unknown_collection

    fdi_db = MongoClient('localhost', 27017).fdi
    classifier_metadata = fdi_db.classifier_metadata
    unknown_collection = fdi_db.unknown

def initialize():
    global scaler
    global clf

    scaler = pickle.load(open('scaler.pkl','rb'))
    clf = pickle.load(open('classifier_model.pkl','rb'))

start_database()

@app.route('/classifier/predict', methods=['GET'])
def endpoint_predict():
    global unknown_collection

    if (clf == None):
        initialize()

    meta = list(classifier_metadata.find({}))

    content = request.get_json()
    x = pd.read_json(content['x'])
    y = content['y']
    x = x.rename({x: 'c'+str(x) for x in np.arange(0, 55)}, axis=1)
    _x = scaler.transform(x).reshape(1,-1)

    pred = clf.predict_proba(_x)
    threshold = [0.9, 0.66, 0.75]
    phi = threshold[0]
    for n in pred:
        if n[1] >= phi:
            r = 1
        elif len(n) > 2 and n[2] >= phi:
            r = 2
        else:
            r = 9
            unknown_collection.insert_one({
                     "timestamp": datetime.datetime.now(),
                     "sensors": x.loc[0].to_dict(),
                     "y": y
                 })

    return jsonify({'y_hat': r}) #call classifier



if __name__ == '__main__':
    app.run(port=5001, debug=True,  use_reloader=False)