#!/usr/bin/env bash


if [[ "$@" == "resetdns" ]]; then                # reset dns list to one observed via dhcp:
    su admin -c "sudo sh -c \"networksetup -setdnsservers Wi-Fi empty ; networksetup -setdnsservers Ethernet empty\""
    exit 0
fi





WIFI_IP=$(ipconfig getifaddr en1)

if [[ "$@" == "localhost" ]]; then
    echo "local.ryctoic.com is 127.0.0.1 now" 
    THE_IP="127.0.0.1"
else
    THE_IP="$WIFI_IP"
    echo "local.ryctoic.com is $THE_IP now"
    echo "configure your smartphone or tablet to user this dns server: $WIFI_IP"
    echo "and you will be able to use the local.ryctoic.com address"
    echo "btw, now you can ping ryctoic_backend.dev.dnsdock or ryctoic_postgres.dev.dnsdock or anything"
    echo "---"
fi



# ETHERNET_IP=$(ipconfig getifaddr en0)
# if [[ ! -z "$ETHERNET_IP" ]]; then
#     OUR_IP="$ETHERNET_IP"
# else
#     OUR_IP="$WIFI_IP"
# fi



DOCKER_BRIDGE_IP=$(ssh vagrant@vagrant.local "ip -4 addr show docker0 | grep -Po 'inet \K[\d.]+'")   # dnsdock's port 53 is mapped on it
# DOCKER_VM_IP=$(ping -c 1 vagrant.local | awk -F'[()]' '/PING/{print $2}')
TAB=$'\t'   # sed doesn't understand tabs


# please don't laugh, I'm on mac using unprivileged account
su admin -c "sudo sh -c \"sed -i '' 's/^.*local.ryctoic.com/$THE_IP${TAB}local.ryctoic.com/g' /etc/hosts ; \
port unload dnsmasq ; \
port load dnsmasq ; \
route -n add 172.17.0.0/24 vagrant.local ; \
route -n add 172.18.0.0/16 vagrant.local ; \
route -n add 172.19.0.0/16 vagrant.local ; \
route -n add 172.20.0.0/16 vagrant.local ; \
route -n add 172.21.0.0/16 vagrant.local ; \
route -n add 172.22.0.0/16 vagrant.local ; \
route -n add 172.23.0.0/16 vagrant.local ; \
route -n add 172.24.0.0/16 vagrant.local ; \
route -n add 172.25.0.0/16 vagrant.local ; \
route -n add 172.26.0.0/16 vagrant.local ; \
route -n add 172.27.0.0/16 vagrant.local ; \
route -n add 172.28.0.0/16 vagrant.local ; \
route -n add 172.29.0.0/16 vagrant.local ; \
route -n add 172.30.0.0/16 vagrant.local ; \
networksetup -setdnsservers Wi-Fi $DOCKER_BRIDGE_IP 8.8.8.8 8.8.4.4 ; \
networksetup -setdnsservers Ethernet $DOCKER_BRIDGE_IP 8.8.8.8 8.8.4.4 ; \
killall -HUP mDNSResponder
\""







