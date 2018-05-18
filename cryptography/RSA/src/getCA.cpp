// Signing 'CA'

#include<RSA.h>

using namespace std;

int main()
{
	RSA ca;

	cout << "Decoding CA for authentication" << endl;
	
	// Getting ciphered CA
	ifstream file;
	file.open("../genfiles/SignedCA.txt");	
	
	string lines;
	int nl = 0;

	while( getline(file, lines) )
	{
		nl++;
	
	} // while 

	file.close();
	cout << "Cipher Length = " << nl << endl;
	ifstream fs;
	fs.open("../genfiles/SignedCA.txt");
	cout << "Message to decode:" << endl;
	for (int h = 0; h<nl; h++)
	{
		fs >> ca.en[h];
		cout << ca.en[h];
	}
	cout << endl;
	fs.close();
	
	string fin = "../Keys/Current_DS_key.txt";
	string fout = "../genfiles/DigitalSignatureAuthentication.txt";
	ca.getIdentity(fin, fout);
	
	return 0;

}// main()
