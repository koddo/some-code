#!/usr/bin/env bash

docker run -d \
       -v /var/run/docker.sock:/var/run/docker.sock \
       --name dnsdock -p 172.17.0.1:53:53/udp \
       --restart on-failure \
       aacebedo/dnsdock:latest-amd64 --domain dnsdock --environment dev        # --verbose


