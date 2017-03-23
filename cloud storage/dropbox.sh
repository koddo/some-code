#!/usr/bin/env bash

# docker build -t koddo/dropbox - < Dockerfile_dropbox

docker run -d \
       --name dropbox \
       --restart on-failure \
       -v /mnt/hgfs/Dropbox:/home/theuser/Dropbox \
       koddo/dropbox



# docker logs --follow dropbox

