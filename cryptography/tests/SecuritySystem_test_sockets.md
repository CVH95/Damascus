# Testing the system over sockets.

The security system was test over a series of socket connections. Test C++ files are in _cryptography/src/_ as _client.cpp_ and _server.cpp_

### Output on the server side:

```sh
$ ./server 
##############################
# OPENED CHANNEL WITH CLIENT #
##############################

AUTHENTICATION

n = 4559
e = 29
Authentication Key received in ../sockets/Shared_Authentication_key.txt
a�{�:��
Received ciphered data and saved to ../sockets/Signature_encrypted.txt
Authentication decoding key: (4559, 29)

Decrypted 'CA':
realoviedo
Received CA: realoviedo
Authorization status == 1
Correct identification. Preparing to send internal BF key.

SECURE KEY EXCHANGE

n = 2231
e = 59
Public Key received in ../sockets/Shared_Public_key.txt
Public Key: (2231, 59)
Ciphered BF Key:
315120621736059760522489717661037

Sending encrypted BF key:
315120621736059760522489717661037
;�}]a]�a�
Sent

CONFIRMATION

Receiving BF encrypted confirmation:
�x����
Received message (decrypted):
iminside

```

### Output on the client side:

```sh
$ ./client 192.168.0.103
SELECTING SIGNATURE

Server's IP address: 192.168.0.103
../Keys/Signature_PublicKey_4.txt
Key to export: 4559, 29
Authentication encoding key: (4559, 533)
Signed 'CA':
369318219741002313707327318213642231
Saved to ../sockets/SignedCA.txt

##############################
# OPENED CHANNEL WITH SERVER #
##############################

AUTHENTICATION

Sent Authentication Key n = 4559, e =29
Sending signature
369318219741002313707327318213642231
ma�{�:�
Sent

SECURE KEY EXCHANGE

Sending now RSA random Public Key
Sent Public Key n = 2231, e =59
;�}]a]�a�
Received ciphered data and saved to ../sockets/BF_encrypted_received.txt
Before decryption
Private Key: (2231, 179)

Decrypted Message:
ciudadlago
BF key received!

CONFIRMATION

Type confirmation message to send (8 bytes): iminside

Sending confirmation message: iminside

```
