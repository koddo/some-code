#!/usr/bin/env bash

FIRST_LINE=$(head -n 1 ./docker-compose.yml)
PRJ="${FIRST_LINE/\# --project-name /}"

docker-compose --project-name "$PRJ" "$@"
