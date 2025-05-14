#!/bin/bash

set -xe

if [ ! -d .env ]; then
    conda env create -f env.yml --prefix .env
else
    conda env update -f env.yml --prefix .env --prune
fi

eval "$(conda shell.bash hook)"
conda activate ./.env

rm -rf build
mkdir -p build
cd build
cmake ..
make VERBOSE=1
