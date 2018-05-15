// ENCRYPTION ROUTINE

#include <Blowfish.h>
#include <fstream>

using namespace std;

int main()
{
	// Files
	//const string key_file = "/home/charlie/workspace/LEO2/cryptography/Blowfish/genfiles/PrivateKey.txt";
	//const string en_file = "/home/charlie/workspace/LEO2/cryptography/Blowfish/genfiles/cipher.txt";

	// Get message
	const unsigned char *msg;	
	char stream[8];
	cout << "Enter message to send (64-bits / 8 bytes):" << endl;
	cin >> stream;
	msg = (const unsigned char *) stream;

	// Blowfish
	Blowfish BF;
	BF.keyGen();
	BF.encrypt(msg);
	
	cout << "Ciphered and saved to genfiles/cipher.txt" << endl;
	
	return 0;

}// main()
