#include <Blowfish.h>

using namespace std;

void Blowfish::keyGen()
{
	// Read psswd 
	ifstream f;
	f.open("/home/charlie/workspace/LEO2/cryptography/Blowfish/genfiles/PrivateKey.txt");

	const unsigned char *psswd;
	char buff[10];
	f >> buff;
	psswd = (const unsigned char *) buff;
	
	// Generate key OpenSSL
	BF_set_key(&key, 10, psswd);
	f.close();

}// keyGen()



// Encryption function
void Blowfish::encrypt(const unsigned char *msg)
{
	unsigned char cipher[BF_BLOCK];
	BF_ecb_encrypt(msg, cipher, &key, BF_ENCRYPT);	

	// Saving cipher
	ofstream of;
	of.open("/home/charlie/workspace/LEO2/cryptography/Blowfish/genfiles/cipher.txt");
	of << cipher << endl;
	of.close();

}// encrypt()


// Decryption function
void Blowfish::decrypt()
{
	// Read cipher
	ifstream file ("/home/charlie/workspace/LEO2/cryptography/Blowfish/genfiles/cipher.txt", ios::in|ios::binary|ios::ate);

	file.seekg(0,ios::end);
	int length = file.tellg(); // file length == ciphered message length
	file.seekg(0);

	char *memblock = new char[length];
	file.read(memblock, length);

	const unsigned char *cipher;
	cipher = (const unsigned char*) memblock;
	//cout << cipher << endl; // For debugging

	file.close();

	// Decrypt
	unsigned char msg[BF_BLOCK];
	BF_ecb_encrypt(cipher, msg, &key, BF_DECRYPT);
	
	cout << "Received message (decrypted):" << endl;
	cout << msg << endl;

}// decrypt()
