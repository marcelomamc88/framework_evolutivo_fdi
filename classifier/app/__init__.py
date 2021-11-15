import requests
from flask import Flask, request, jsonify, render_template
from river import cluster
from river import stream
import asyncio
from threading import Thread
from pymongo import MongoClient
import numpy as np
from matplotlib import cm
from matplotlib import pyplot as plt
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
from matplotlib.figure import Figure
from matplotlib.colors import ListedColormap, LinearSegmentedColormap
from mpl_toolkits.mplot3d import Axes3D
import io
import base64
import datetime
import mpld3
from mpld3 import plugins

app = Flask(__name__)
app.config['CORS_HEADERS'] = 'Content-Type'


@app.route('/classifier/', methods=['GET'])
def endpoint_info():
    pass


@app.route('/classifier/learn', methods=['GET'])
def endpoint_learn():
    pass


def initialize():
    start_database()

    print('classifier component has been initialized...')


def start_database():
    pass

def learn(x):
   pass


if __name__ == '__main__':
    initialize()
    app.run(port=5001, debug=True)
