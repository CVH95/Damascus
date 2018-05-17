#include <Security.h>

using namespace std;

int main()
{
	Security auth;
	string sig = "../genfiles/DigitalSignatureAuthentication.txt"; 
	bool status = auth.verifyAuthentication(sig);
	cout << "Authentication Status: " << status << endl;
	
	if ( status == true )
	{
		cout << "Correct Authentication. Device accepted" << endl;
	}// if
	else
	{
		cout << "Wrong credentials. Device rejected" << endl;
	}// else

	return 0; 

}// main
