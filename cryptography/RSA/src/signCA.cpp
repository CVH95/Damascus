// Signing 'CA'

#include<RSA.h>

using namespace std;

int main()
{
	// Set seed
	srand (time(0));
	RSA ca;

	cout << "Signing random CA" << endl;
	ca.signIdentity();
	
	return 0;

}// main()
