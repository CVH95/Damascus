// SECURITY CLASS

#include <Security.h>

using namespace std;


bool Security::verifyAuthentication(string filename)
{
	// Read Signature	
	ifstream inf;
	inf.open(filename.c_str());
	char msg[10];
	inf >> msg;
	inf.close();

	cout << "Received CA: " << msg << endl;
	
	// Verify it
	bool allowed;
	
	// With my signatures
	//if( msg == "california" || msg == "napolitano" || msg == "gunsnroses" )
	if(strcmp ("realoviedo", msg) == 0)	
	{
		allowed = true;
	}// if
	else if(strcmp ("napolitano", msg) == 0)
	{
		allowed = true;
	}
	else if(strcmp ("gunsnroses", msg) == 0)
	{
		allowed = true;
	}
	else 
	{

		allowed = false;
	}

	return allowed;
}

