#!/bin/bash
app="clusterer.api"
docker build -t ${app} .
docker run -d --restart=always -p 5000:80 --name=${app} -v $PWD:/app ${app}
