// DECRYPTION ROUTINE

#include <Blowfish.h>

using namespace std;

int main()
{
	// Blowfish
	Blowfish BF;
	string fin = "../genfiles/cipher.txt";
	string key = "../Keys/BF_PrivateKey.txt";
	BF.keyGen(key);
	BF.decrypt(fin);

	return 0;

}// main()
