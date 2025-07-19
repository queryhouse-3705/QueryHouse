#!/bin/bash

set -e

if [ -z "$1" ]; then
    IMG_NAME="test_qh"
    CONT_NAME="test_qh"
else
    IMG_NAME="$1"
    CONT_NAME="$1"
fi

# copy_to_docker
rm -rf docker/srcs docker/third_party
cp -r srcs docker/
cp -r third_party docker/
cp scripts/oracle_run.sh docker/
cp CMakeLists.txt docker/
cp lint.cmake docker/
# cp .clang-format docker/
# cp .clang-tidy docker/

# docker_build
echo "Image name: ${IMG_NAME}"
docker build --build-arg MULTI_CORE=0 -t $IMG_NAME .

# docker_run
echo "Container name: ${CONT_NAME}"
docker run -it --name $CONT_NAME $IMG_NAME
