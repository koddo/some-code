#!/usr/bin/env bash

## docker build -t koddo/disk-yandex - < Dockerfile_yandex-disk


## when I run `yandex-disk token`` instead of setup, it doesn't add dir option to config.cfg and then complains so I add it manually
## and it wants to have --dir option when with --no-daemon
CMD='
while [[ ! -f ~/.config/yandex-disk/passwd ]] ; do echo "run: docker exec -it yandex-disk yandex-disk token [username]" && sleep 3 ; done && \
echo "dir=~/Yandex.Disk" >> ~/.config/yandex-disk/config.cfg && \
echo "good" && \
yandex-disk --no-daemon --dir=~/Yandex.Disk
'

docker run -d \
       --name disk-yandex \
       --restart on-failure \
       -v /vagrant-disk-yandex:/home/theuser/Yandex.Disk \
       koddo/disk-yandex bash -c "$CMD"



## docker logs --follow disk-yandex
## docker exec -it disk-yandex yandex-disk token npoektop
## docker exec -it disk-yandex yandex-disk status
