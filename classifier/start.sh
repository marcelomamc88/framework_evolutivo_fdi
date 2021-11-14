#!/bin/bash
app="classifier.api"
docker build -t ${app} .
docker run -d --restart=always -p 5001:80 --name=${app} -v $PWD:/app ${app}
