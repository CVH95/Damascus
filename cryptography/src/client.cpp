#include <Blowfish.h>
#include <RSA.h>
#include <Security.h>

using namespace std;

int main(int argc, char *argv[]) 
{
	// Create Objects
	Security dfc;
	int sock;
	int port = 30001;
	char *sIP = argv[1];
	if (sIP == NULL) 
	{
		cout << "Failed to start client. MUST input server's IP!!!" << endl;
		return 0;
	}
	
	cout << "Server's IP address: " << sIP << endl;
	
	char msg[100] = "ciudadlago";
	struct sockaddr_in serv_addr;
    	struct hostent *server;

	if ( ( sock = socket(AF_INET, SOCK_STREAM, 0) ) < 0 )
        	perror("ERROR opening socket\n");

    	if ( ( server = gethostbyname( sIP ) ) == NULL ) 
        	perror("ERROR, no such host\n");
    
	bzero( (char *) &serv_addr, sizeof(serv_addr));
    	serv_addr.sin_family = AF_INET;
    	bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    	serv_addr.sin_port = htons(port);
    	if ( connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        	perror("ERROR connecting\n");

	//for (int n = 0; n < 10; n++ ) 
	//{
		dfc.sendMessage( sock, msg );
		
		// Receive 10-byte message
		dfc.readMessage( sock, 10 );
    	//}

	close(sock);
	return 0;

}// main()
