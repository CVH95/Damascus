// DECRYPTION ROUTINE

#include <Blowfish.h>

using namespace std;

int main()
{
	// Blowfish
	Blowfish BF;
	BF.keyGen();
	BF.decrypt();

	return 0;

}// main()
