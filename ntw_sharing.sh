#!/bin/bash

# Should be run by sudo
sysctl net/ipv4/ip_forward=1
iptables -t nat -I POSTROUTING -o wlan0 -j MASQUERADE
echo "Network sharing with RPi via ethernet is ENABLED"
