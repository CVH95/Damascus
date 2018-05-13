# Connecting 2 Raspberry Pi's in Ad-Hoc network

## Direct mode: On both Raspberry Pi's:

Network's name (essid): leo2.

On the two Pi's:

```sh
$ sudo ifconfig wlan0 down
$ sudo iwconfig wlan0 channel 1 essid leo2 mode ad-hoc
$ sudo ifconfig wlan0 up
```

To confirm that both are broadcasting and in range:

```sh
$ iwlist wlan0 scan
```

The output should be something similar to this:

```
wlan0     Scan completed :
Cell 23 - Address: 02:11:87:F0:E0:00
                    ESSID:"leo2"
                    Protocol:IEEE 802.11bg
                    Mode:Ad-Hoc
                    Frequency:2.412 GHz (Channel 1)
                    Encryption key:off
                    Bit Rates:54 Mb/s
                    Quality=0/100  Signal level=74/100  
```

Then assign an IP to each node:

 - Kinsasa:

```sh
$ ifconfig wlan0 192.168.10.5 netmask 255.255.255.0
```

 - Monterrey:

```sh
$ ifconfig wlan0 192.168.10.6 netmask 255.255.255.0
```

Finally, to test the connection, try to ping one node from the other.


## Bringing up the network after reebot: starting node

To build the Ad-Hoc network, a first node has to start broadcasting. The `ad_hoc_network_configuration_files` directory contains the required files to create that network. It is important to create backups for all the original versions of these files. 

In this scenario, the `rc.local` file is the one that brings up the network by starting the first broadcasting node. It is necessary to change the rc.local files of the next nodes aswell, to accept being clients of the DHCP server started in this node.

It is necessary to install first the package isc-dhcp-server.

```sh
$ sudo apt-get install isc-dhcp-server
$ sudo cp rc.local /etc/
$ sudo cp interfaces /etc/network/
$ sudo cp dhcpd.conf /etc/dhcp/
$ sudo cp isc-dhcp-server /etc/default/
```  

After copying the configuration files into their respective directories, reboot the Pi.
