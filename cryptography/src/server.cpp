#include <Blowfish.h>
#include <RSA.h>
#include <Security.h>

using namespace std;


int main(int argc, char *argv[]) 
{
	// Create objects
	Security dfc;
	RSA rsa;
	//Blowfish bfsh;

	int sock, newsock;
	int port = 30001;
     	char msg[100] = "putamadree";
	struct sockaddr_in client_addr;
	int lc = sizeof(client_addr);

	sock = dfc.createSocket(port);

	if ( ( newsock = accept( sock, (struct sockaddr *) &client_addr, (socklen_t*) &lc) ) < 0 )
        	perror("ERROR on accepting client\n");
		  
	cout << "Opened Channel with client" << endl;

	// INITIATE SEQUENCE

	// 1. Receive Signature Autehtication public key
	long int N = dfc.readKey(newsock);
	long int E = dfc.readKey(newsock);

	string file1 = "../sockets/Shared_Authentication_key.txt";
	dfc.savePublicKey(N, E, file1);			
	cout << "Public Key received" << endl;

	string file2 = "../sockets/Signature_encrypted.txt";
	dfc.readCrypto(newsock, 10, file2);	

	dfc.sendMessage( newsock, msg);
			
	






	close( newsock );

	return 0;

}// main()
