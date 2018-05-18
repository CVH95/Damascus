// Signing 'CA'

#include<RSA.h>

using namespace std;

int main()
{
	// Set seed
	srand (time(0));
	RSA ca;

	cout << "Signing random CA" << endl;
	string fkout = "../Keys/Current_DS_key.txt";
	string fout = "../genfiles/SignedCA.txt";
	ca.signIdentity(fkout, fout);
	
	return 0;

}// main()
