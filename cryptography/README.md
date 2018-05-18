# Cryptography Code

Security system overview:
![alt text](sss.png)


### Build and Compile

```sh
$ cd build
$ cmake ../
$ make
```

Executables in `bin/`. 

### Blowfish Symmetric Key Cipher (OpenSSL).

Network's internal confidentiality. Works with messages of 8 bytes and keys of 10 bytes. The key is in `Keys/BF_PrivateKey.txt`.

Programs:

  - Basic test with user inputs.
  - Encryption executable (user enters the message to encrypt). 
  - Decryption executable.


### RSA Algorithm

Used for authentication (as digital signature method) and for exchanging blowfish keys encrypted. All keys and signatures are in `Keys/`.


Programs:

  - Basic test with user inputs.
  - Encryption (ciphers the blowfish key).
  - Decryption.
  - Signature cipher.
  - Signature decryptor.

### Security Class

Implements a series of useful functions, such as verification, sockets...

Programs:
  - Verification.
  - Client/Server test that runs a test of the whole system described in the figure above.
