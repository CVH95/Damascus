#include <Blowfish.h>


void Blowfish::keyGen(const string filename)
{
	// Read psswd 
	keyTXT.open(filename);
	const unsigned char *psswd;
	char buff[10];
	keyTXT >> buff;
	cout << "PSSWD read: " << psswd << endl;
	key = (const unsigned char *) psswd;
	
	// Generate key OpenSSL
	BF_set_key(&key, 10, psswd);

}// keyGen()



// Encryption function
unsigned char Blowfish::encrypt(const unsigned char *msg)
{
	unsigned char cipher[BF_BLOCK];
	BF_ecb_encrypt(msg, cipher, &key, BF_ENCRYPT);	

}// encrypt()


// Decryption function
unsigned char Blowfish::decrypt(unsigned char cipher)
{
	unsigned char msg[BF_BLOCK];
	BF_ecb_encrypt(cipher, msg, &key, BF_DECRYPT);
	
	return msg;
}// decrypt()
