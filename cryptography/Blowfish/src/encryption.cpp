// ENCRYPTION ROUTINE

#include <Blowfish.h>
#include <fstream>

using namespace std;

int main()
{
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
	
	cout << "Ciphered and saved to cryptography/genfiles/cipher.txt" << endl;
	
	return 0;

}// main()
