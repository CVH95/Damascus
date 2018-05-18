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

}// verifyAuthentication()


// Create Socket
int Security::createSocket(int port)
{
	int s;
    	struct sockaddr_in addr;

    	addr.sin_family = AF_INET;
    	addr.sin_port = htons(port);
    	addr.sin_addr.s_addr = htonl(INADDR_ANY);

    	s = socket(AF_INET, SOCK_STREAM, 0);

   	if (s < 0) 
	{
		perror("Failed to create socket\n");
		exit(EXIT_FAILURE);
    	}// if

    	if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) 
	{
		perror("Failed to bind address\n");
		exit(EXIT_FAILURE);
    	}// if

    	if (listen(s, 1) < 0) 
	{
		perror("Failed to listen\n");
		exit(EXIT_FAILURE);
    	}// if

    return s;

}// createSocket()


// Send data over socket
int Security::sendMessage(int socket, char msg[100])
{
	// Get actual message size
	int length = strlen(msg);
	char buffer[length];
	for(int i=0; i< length; i++)	
	{
		buffer[i] = msg[i];
	}// for

	// Send buffer
	int n;
	if ( (n = write( socket, buffer, length ) ) < 0 )
   		perror("ERROR writing to socket\n");
  
	buffer[n] = '\0';

	return length;

}//sendMessage()


// Read regular data in the socket & save into file
void Security::readMessage(int socket, string file)
{
	char buffer[100];
	int n;

	if ( (n = read(socket, buffer, sizeof(int)) ) < 0 )
    		perror("ERROR reading from socket\n");
 	buffer[n] = -1;
	
	FILE * ofc;
	ofc = fopen(file.c_str(),"w");
	for(int i=0; buffer[i] != -1; i++)
	{
		fprintf(ofc, "%c", buffer[i]);
		printf("%c", buffer[i]);
	}// for
	fclose(ofc);
	cout << endl;
	cout << "Received Message and saved to " << file << endl;

}// readMessage()


// Read Public Keys on socket
long int Security::readKey(int socket)
{
	char buffer[100];
	int n;
	if ( (n = read(socket, buffer, sizeof(int) ) ) < 0 )
    		perror("ERROR reading from socket\n");

 	buffer[n] = '\0';	

	long int key = atol(buffer);
	return key;

}// readKey();



// Read RSA encrypted messages
void Security::readCrypto(int socket, int length, string file)
{
	char buffer[length];
	int n;
	if ( (n = read(socket, buffer, length) ) < 0 )
    		perror("ERROR reading from socket\n");

 	buffer[n] = '\0';


	long int crypt[length];
	for(int i = 0; buffer[i] != '\0'; i++)
	{
		crypt[i] = buffer[i];
		printf("%c", buffer[i]);		
	}// for
	cout << endl;

	crypt[length] = -1;
	FILE * ofu;
	ofu = fopen(file.c_str(), "w");
	for(int j=0; crypt[j] != -1; j++)
	{
		fprintf(ofu, "%u \n", crypt[j]); 
	}// for
	fclose(ofu);
	cout << "Received ciphered data and saved to " << file << endl;

}// readCrypto()


// Closing message
void Security::shutdownSocket( int socket, int length, string file)
{
	int n;

  	char buffer[length];
  	if ( (n = read( socket, buffer, length ) ) < 0 )
      		perror("ERROR sending closing message to socket");
  	buffer[n] = '\0';

	FILE * ofu;
	ofu = fopen(file.c_str(), "w");
	for(int j=0; buffer[j] != '\0'; j++)
	{
		fprintf(ofu, "%c", buffer[j]);
		printf("%c", buffer[j]); 
	}// for
	cout << endl;
	fclose(ofu);	

}// shutdownSocket()

// Save shared public keys into file
void Security::savePublicKey(long int n, long int e, string file)
{
	ofstream of;
	of.open(file.c_str());
	
	of << n << " " << e << endl;
	
	of.close();

}// savePublicKey()

