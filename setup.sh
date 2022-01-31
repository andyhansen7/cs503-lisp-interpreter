#!/usr/bin/env bash

set -euxo pipefail

mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Release ../
