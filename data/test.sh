#!/bin/bash

set -xe

eval "$(conda shell.bash hook)"
conda activate ./.env

export LIBGL_ALWAYS_SOFTWARE=true
export GALLIUM_DRIVER=llvmpipe

./build/test
