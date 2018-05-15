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

	/*ofstream of;
	of.open("/home/charlie/workspace/LEO2/cryptography/Blowfish/genfiles/PrivateKey.txt");

	of << key << endl;*/

}// keyGen()



// Encryption function
void Blowfish::encrypt(const unsigned char *msg)
{
	unsigned char cipher[BF_BLOCK];
	BF_ecb_encrypt(msg, cipher, &key, BF_ENCRYPT);	

	// Saving cipher
	ofstream of;
	of.open("/home/charlie/workspace/LEO2/cryptography/Blowfish/genfiles/cipher");
	of << cipher << endl;
	of.close();

}// encrypt()


// Decryption function
void Blowfish::decrypt()
{
	// Read cipher
	ifstream fs;
	fs.open("/home/charlie/workspace/LEO2/cryptography/Blowfish/genfiles/cipher");
	unsigned char cipher[BF_BLOCK];
	//char buff[8];
	//fs >> buff;
	//cipher = (unsigned char) buff;
	fs >> cipher;

	cout << cipher << endl;

	unsigned char msg[BF_BLOCK];
	BF_ecb_encrypt(cipher, msg, &key, BF_DECRYPT);
	
	cout << "Received message (decrypted):" << endl;
	cout << msg << endl;
	
	fs.close();

}// decrypt()
