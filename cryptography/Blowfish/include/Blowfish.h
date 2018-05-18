// BLOWFISH CLASS

// General
#include <iostream>
#include <fstream> 
#include <vector>
#include <math.h> 
#include <numeric>
#include <algorithm>
#include <iterator>
#include <boost/foreach.hpp>
#include <string>
#include <vector>
#include <stdio.h>
#include <openssl/blowfish.h>

using namespace std;

class Blowfish{
  public:

	void keyGen(string fin);
	void encrypt(const unsigned char *msg, string fout);
	void decrypt(string fin);

  private:
	
	BF_KEY key;
};
