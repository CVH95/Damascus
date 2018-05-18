#include <Blowfish.h>
#include <RSA.h>
#include <Security.h>

using namespace std;

int main(int argc, char *argv[]) 
{
	srand (time(0));
	// Create Objects
	Security dfc;
	Security lti;
	RSA rsa;
	Blowfish bfsh;

	cout << "SELECTING SIGNATURE" << endl << endl;

	int sock, sock2;
	int port = 30001;
	char *sIP = argv[1];
	if (sIP == NULL) 
	{
		cout << "Failed to start client. MUST input server's IP!!!" << endl;
		return 0;
	}
	
	cout << "Server's IP address: " << sIP << endl;
	
	//Get random CA	
	string fk = "../sockets/Current_DS_key.txt";
	string fsg = "../sockets/SignedCA.txt";
	rsa.signIdentity(fk, fsg);
		
	vector<long int> sharedKey = rsa.getKey(fk);
	long int N = sharedKey[0];
	long int E = sharedKey[1];

	// Get RSA public key
	string PB = "../Keys/RSA_PublicKey.txt";
	vector<long int> pbk = rsa.getKey(PB);
	long int pbk_n = pbk[0];
	long int pbk_e = pbk[1];
	
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

	// INITIATE SEQUENCE

	cout << "##############################" << endl;	  
	cout << "# OPENED CHANNEL WITH SERVER #" << endl;
	cout << "##############################" << endl << endl;

	cout << "AUTHENTICATION" << endl << endl;

	// 1. Send Key
	char msg1[100];
	sprintf(msg1, "%Ld", N);
	dfc.sendMessage( sock, msg1 );
	char msg2[100];
	sprintf(msg2, "%Ld", E);
	dfc.sendMessage( sock, msg2 );
	cout << "Sent Authentication Key n = " << N << ", e =" << E << endl;

	//2. Send Signature
	char msg3[100];
	ifstream file;
	file.open("../sockets/SignedCA.txt");	
	string lines;
	int nl = 0;
	while( getline(file, lines) )
	{
		nl++;
	} // while 
	file.close();
	ifstream fs;
	long int gh[100];
	cout << "Sending signature" << endl;
	fs.open("../sockets/SignedCA.txt");
	for (int h = 0; h<nl; h++)
	{
		fs >> gh[h];
		printf("%u", gh[h]);
	}
	fs.close();
	cout << endl;
	for(int j=0; j<nl; j++)
	{ 
		msg3[j] = gh[j];
		printf("%c", gh[j]);	
	}
	cout << endl;
	cout << "Sent" << endl;
	dfc.sendMessage(sock, msg3);

	close(sock);
	
	if ( ( sock2 = socket(AF_INET, SOCK_STREAM, 0) ) < 0 )
        	perror("ERROR opening socket\n");

    	if ( ( server = gethostbyname( sIP ) ) == NULL ) 
        	perror("ERROR, no such host\n");

	if ( connect(sock2,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        	perror("ERROR connecting\n");
	
	// 3. Send Public Key to decode BF.
	cout << endl << "SECURE KEY EXCHANGE" << endl << endl;
	cout << "Sending now RSA random Public Key" << endl; 	
	char msg7[100];
	sprintf(msg7, "%Ld", pbk_n);
	lti.sendMessage( sock2, msg7 );
	char msg8[100];
	sprintf(msg8, "%Ld", pbk_e);
	lti.sendMessage( sock2, msg8 );
	cout << "Sent Public Key n = " << pbk_n << ", e =" << pbk_e << endl;
    	
	// 4. Receive internal BF key
	string raj = "../sockets/BF_encrypted_received.txt";
	dfc.readCrypto(sock2, 10, raj);	

	ifstream file7;
	file7.open(raj.c_str());
	string lis;
	int nj = 0;

	while( getline(file7, lis) )
	{
		nj++;
	
	} // while 

	file7.close();
	ifstream fss;
	fss.open(raj.c_str());
	for (int h = 0; h<nl; h++)
	{
		fss >> rsa.en[h];
	}
	fss.close();
	cout << "Before decryption" << endl;
	string k1 = "../Keys/RSA_PrivateKey.txt";
	string k2 = "../sockets/BF_key_received.txt";
	rsa.decryption(k1, k2);
	cout << "BF key received!" << endl;

	cout << endl << "CONFIRMATION" << endl << endl;

	// 5. Send confirmation message.
	char stream[8];
	cout << "Type confirmation message to send (8 bytes): ";	
	cin >> stream;
	cout << endl;
	const unsigned char *roar;
	roar = (const unsigned char *) stream;
	cout << "Sending confirmation message: " << roar << endl;
	string roarf = "../sockets/Confirmation_encrypted.txt";
	bfsh.keyGen(k2);
	bfsh.encrypt(roar, roarf);

	ifstream inf;
	inf.open(roarf.c_str());
	char roarbuf[100];
	inf >> roarbuf;
	inf.close();

	dfc.sendMessage(sock2, roarbuf);

	close(sock);
	return 0;

}// main()
