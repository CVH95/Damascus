// Decryption 

#include<RSA.h>

using namespace std;

int main()
{
	RSA secret;

	ifstream file;
	file.open("../genfiles/BF_Key_ciphered.txt");//, ios::in|ios::binary|ios::ate);

	string lines;
	int nl = 0;

	while( getline(file, lines) )
	{
		nl++;
	
	} // while 

	file.close();
	cout << "Cipher Length = " << nl << endl;
	ifstream fs;
	fs.open("../genfiles/BF_Key_ciphered.txt");
	cout << "Message to decode:" << endl;
	for (int h = 0; h<nl; h++)
	{
		fs >> secret.en[h];
		cout << secret.en[h];
	}
	cout << endl;
	fs.close();

	secret.decryption();	

	return 0;

}// main()
