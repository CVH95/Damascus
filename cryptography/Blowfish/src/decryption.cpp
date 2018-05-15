// DECRYPTION ROUTINE

#include <Blowfish.h>

using namespace std;

int main()
{
	// Files
	//const string key_file = "/home/charlie/workspace/LEO2/cryptography/Blowfish/genfiles/PrivateKey.txt";
	//const string en_file = "/home/charlie/workspace/LEO2/cryptography/Blowfish/genfiles/cipher.txt";

	// Read cipher
	//ifstream ifs;
	//ifs.open(en_file);
	//unsigned char cipher;
	//char buff[10];
	//ifs >> buff;
	//cipher = (const unsigned char *) buff;

	// Blowfish
	Blowfish BF;
	BF.keyGen();
	BF.decrypt();

	return 0;

}// main()
