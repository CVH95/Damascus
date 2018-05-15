#include <iostream>
#include <fstream>
#include <stdio.h>
#include <openssl/blowfish.h>

using namespace std;


int main()
{
	cout << "SYMMETRIC CRYPTOGRAPHY - BLOWFISH ALGORITHM - TEST" << endl << endl;

	// Blowfish key - 10 bytes
	const unsigned char *key;
	char psswd[10];
	fflush(stdin);
	cout << "Enter key psswd:" << endl;
	cin >> psswd;	
	cout << endl;
	key = (const unsigned char *) psswd;

	BF_KEY bfKey;
	BF_set_key(&bfKey, 10, key);
	
	cout << "Generated Blowfish's private key:" << endl;
	
	// Message to be encrypted must be 64 bits. OpenSSL does not provide padding. If it is bigger than 64 bits, the last part of the message it's igonred. 
	const unsigned char *msg;	
	char stream[8];
	cout << "Enter message to send (64-bits / 8 bytes):" << endl;
	cin >> stream;
	msg = (const unsigned char *) stream;

	// Outputs of the OpenSSL encryption & decryption functions
	unsigned char cipher[BF_BLOCK];
	unsigned char plain[BF_BLOCK];

	BF_ecb_encrypt(msg, cipher, &bfKey, BF_ENCRYPT);
	
	cout << "Encrypted message" << endl;
	cout << cipher << endl;
	
	BF_ecb_encrypt(cipher, plain, &bfKey, BF_DECRYPT);

	cout << "Decrypted message" << endl;
	cout << plain << endl;

	return 0;
}

	

