import numpy as np
import requests
import json
import pandas as pd


url = 'http://127.0.0.1:5002/clusterer/learn'
headers = {'Accept' : 'application/json', 'Content-Type' : 'application/json'}

dataset = np.loadtxt('iris2.txt')

X = dataset[:, 0:4]

for sensors in X:
    data = {}
    data['x'] = {}
    for index, sensor in enumerate(sensors):
        data['x'][str(index)] = float(sensor)
    r = requests.get(url, data=json.dumps(data), headers=headers)

a = 69