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
    ground_truth = int(Y_label[k])

    if ground_truth in contador.keys():
        contador[ground_truth] = contador[ground_truth] + 1
    else:
        contador[ground_truth] = 1

    if (contador[ground_truth] > 200):
        y_pred = send('/predict', {'x': numpy2dict(x.to_numpy())})['y_pred']

        predict.append(y_pred)
        truth.append(ground_truth)

        #if (not (y_pred is None)):
         #   print(str(k) + ': # label : ' + str(contador[ground_truth]) + ' : y ' + str(y_pred))

    send('/learn', {'x': numpy2dict(x.to_numpy()), 'y': ground_truth})

print(accuracy_score(truth, predict))






