#!/bin/bash

docker pull ubuntu:24.04
docker build -t temp01 .
docker run -it -v $PWD/data:/opt -w /opt temp01
