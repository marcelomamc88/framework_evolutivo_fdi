import requests
import json
from river.utils import numpy2dict
import pandas as pd
from sklearn.preprocessing import LabelEncoder
from river import datasets
import numpy as np
from sklearn.metrics import accuracy_score

url = 'http://127.0.0.1:5001/classifier'
headers = {'Accept' : 'application/json', 'Content-Type' : 'application/json'}


def send(endpoint, params_dict):
    return requests.get(url+endpoint, data=json.dumps(params_dict), headers=headers).json()


dataset = pd.read_csv(datasets.ImageSegments().path)

dataset['categorical_label'] = LabelEncoder().fit_transform(dataset['category'])

df = dataset
Y = df.pop('category')
Y_label = df.pop('categorical_label')

contador = {}
predict = []
truth = []

for k, x in df.iterrows():
    send('/learn', {'x': numpy2dict(x.to_numpy()), 'y': int(Y_label[k])})

for k, x in df.iterrows():
    predict.append(send('/predict', {'x': numpy2dict(x.to_numpy())})['y_pred'])
    truth.append(int(Y_label[k]))


print(accuracy_score(truth, predict))






