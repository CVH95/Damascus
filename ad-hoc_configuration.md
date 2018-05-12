# Ad Hoc Network Configuration

It is necessary to have a USB WiFi adapter (Edimax 7811Un). The first step is to configure the wireless network. 'Naples' will be the starting node; then, the rest will connect to the ad hoc network that 'Naples' is broadcasting.

##### 1. Hardware checks

First, check that the USB adapter is recognized:

```sh
naples@raspberrypi:~/workspace/LEO2 $ lsusb
```

It should appear in the output like this:

```
Bus 001 Device 004: ID 7392:7811 Edimax Technology Co., Ltd EW-7811Un 802.11n Wireless Adapter [Realtek RTL8188CUS]
Bus 001 Device 003: ID 0424:ec00 Standard Microsystems Corp. SMSC9512/9514 Fast Ethernet Adapter
Bus 001 Device 002: ID 0424:9514 Standard Microsystems Corp. SMC9514 Hub
Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
```

##### 2. Current network status

Using `ifconfig` to check `wlan0` status:

```sh
naples@raspberrypi:~/workspace/LEO2 $ ifconfig

eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 10.42.0.194  netmask 255.255.255.0  broadcast 10.42.0.255
        inet6 fe80::d9ef:32f8:395f:66a6  prefixlen 64  scopeid 0x20<link>
        ether b8:27:eb:f5:88:f9  txqueuelen 1000  (Ethernet)
        RX packets 20994  bytes 24231357 (23.1 MiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 6620  bytes 631058 (616.2 KiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10<host>
        loop  txqueuelen 1  (Local Loopback)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

wlan0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
        ether 74:da:38:e1:f3:cd  txqueuelen 1000  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

```

##### 3. Broadcasting an ad hoc network.

Start by backupping the current `/etc/network/interfaces/` and then modify it to contain the following configuration:

```sh
naples@raspberrypi:~/workspace/LEO2 $ sudo cp /etc/network/interfaces /etc/network/interfaces.backup

naples@raspberrypi:~/workspace/LEO2 $ sudo vim /etc/network/interfaces
```

- Interfaces file:

```
# interfaces(5) file used by ifup(8) and ifdown(8)

# Please note that this file is written to be used with dhcpcd
# For static IP, consult /etc/dhcpcd.conf and 'man dhcpcd.conf'

# Include files from /etc/network/interfaces.d:
#source-directory /etc/network/interfaces.d

auto lo
iface lo inet loopback
iface eth0 inet dhcp

# Naples  
auto wlan0
iface wlan0 inet static
  address 192.168.10.1
  netmask 255.255.255.0
  wireless-channel 1
  wireless-essid leo2_adhoc
  wireless-mode ad-hoc

```

Save it and restart the `wlan0` by bringing it down and up:

```sh
naples@raspberrypi:~/workspace/LEO2 $ sudo ifconfig wlan0 down 

naples@raspberrypi:~/workspace/LEO2 $ sudo ifconfig wlan0 up

```

Finally, confirm that wlan0 is broadcasting with the created network by checking that it's IP address is the one set.

```sh
naples@raspberrypi:~/workspace/LEO2 $ ifconfig wlan0
wlan0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
        inet 192.168.10.1  netmask 255.255.255.0  broadcast 192.168.10.255
        ether 74:da:38:e1:f3:cd  txqueuelen 1000  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

```

#### 4. Configuring the DHCP server.

In order for other devices to join the ad hoc network created in RPi 'Naples', it needs to act as a DHCP server to give IPs within its range to all devices that want to join the ad hoc network.

To install the DHCP server (if necesary)

```sh
naples@raspberrypi:~/workspace/LEO2 $ sudo apt-get install isc-dhcp-server
```

To configure the server, edit the file `dhcpd.conf` in /etc/dhcp directory.

```sh 
naples@raspberrypi:~/workspace/LEO2 $ cd /etc/dhcp

naples@raspberrypi:/etc/dhcp $ sudo cp dhcpd.conf dhcpd.conf.backup

naples@raspberrypi:/etc/dhcp $ sudo vim dhcpd.conf
```

To look like the following:

```
# dhcpd.conf
#
# Sample configuration file for ISC dhcpd
#

# option definitions common to all supported networks...
option domain-name "leo2";
option domain-name-servers 192.168.1.1;

default-lease-time 600;
max-lease-time 7200;

# The ddns-updates-style parameter controls whether or not the server will
# attempt to do a DNS update when a lease is confirmed. We default to the
# behavior of the version 2 packages ('none', since DHCP v2 didn't
# have support for DDNS.)
#ddns-update-style none;

# If this DHCP server is the official DHCP server for the local
# network, the authoritative directive should be uncommented.
authoritative;

# Use this to send dhcp log messages to a different log file (you also
# have to hack syslog.conf to complete the redirection).
log-facility local7;

# No service will be given on this subnet, but declaring it helps the 
# DHCP server to understand the network topology.

subnet 192.168.10.0 netmask 255.255.255.0 {
  range 192.168.10.5 192.168.10.60;
  option routers 192.168.10.1;
}

```

Finally, reboot the Pi and start the DHCP by:

```sh
naples@raspberrypi:~/ $ service dhcp start
```
