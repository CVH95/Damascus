#include <iostream>
#include <fstream>
#include <string>
#include <openssl/blowfish.h>

using namespace std;

class Blowfish{
  public:

	void keyGen(const string filename);
	unsigned char encrypt(const unsigned char *msg);
	unsigned char decrypt(unsigned char cipher);

  private:
	
	ifstream keyTXT;
	BF_key key;
};
