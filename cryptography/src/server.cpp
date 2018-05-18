#include <Blowfish.h>
#include <RSA.h>
#include <Security.h>

using namespace std;


int main(int argc, char *argv[]) 
{
	srand (time(0));
	// Create objects
	Security dfc;
	RSA rsa;
	Blowfish bfsh;

	int sock, newsock, sock2;
	int port = 30001;
	struct sockaddr_in client_addr;
	int lc = sizeof(client_addr);

	sock = dfc.createSocket(port);

	if ( ( newsock = accept( sock, (struct sockaddr *) &client_addr, (socklen_t*) &lc) ) < 0 )
        	perror("ERROR on accepting client\n");

	cout << "##############################" << endl;	  
	cout << "# OPENED CHANNEL WITH CLIENT #" << endl;
	cout << "##############################" << endl << endl;

	cout << "AUTHENTICATION" << endl << endl;

	// INITIATE SEQUENCE

	// 1. Receive Signature Autehtication public key
	long int N = dfc.readKey(newsock);
	cout << "n = " << N << endl;
	long int E = dfc.readKey(newsock);
	cout << "e = " << E << endl;

	string file1 = "../sockets/Shared_Authentication_key.txt";
	dfc.savePublicKey(N, E, file1);			
	cout << "Authentication Key received in " << file1 << endl;

	// 2. Receive signature
	string file2 = "../sockets/Signature_encrypted.txt";
	dfc.readCrypto(newsock, 10, file2);	

	// Decrypt CA
	ifstream file;
	file.open("../sockets/Signature_encrypted.txt");
	string lines;
	int nl = 0;

	while( getline(file, lines) )
	{
		nl++;
	
	} // while 

	file.close();
	ifstream fs;
	fs.open("../sockets/Signature_encrypted.txt");
	for (int h = 0; h<nl; h++)
	{
		fs >> rsa.en[h];
	}
	fs.close();
	
	string CAk = "../sockets/Shared_Authentication_key.txt";
	string CAf = "../sockets/DigitalSignatureAuthentication.txt";
	rsa.getIdentity(CAk, CAf);
		
	bool CAstat = dfc.verifyAuthentication(CAf);
	cout << "Authorization status == " << CAstat << endl;
	// Authentication status
	if( CAstat == false )
	{	 
		close( newsock );
		return 0;
	}
	
	cout << "Correct identification. Preparing to send internal BF key." << endl << endl;
	cout << "SECURE KEY EXCHANGE" << endl << endl;
	close(newsock);

	if ( ( sock2 = accept( sock, (struct sockaddr *) &client_addr, (socklen_t*) &lc) ) < 0 )
        	perror("ERROR on accepting client\n");	
	// 3. Receive public key to encrypt BF key.
	long int pbk_n = dfc.readKey(sock2);
	cout << "n = " << pbk_n << endl;
	long int pbk_e = dfc.readKey(sock2);
	cout << "e = " << pbk_e << endl;

	string file4 = "../sockets/Shared_Public_key.txt";
	dfc.savePublicKey(pbk_n, pbk_e, file4);			
	cout << "Public Key received in " << file4 << endl;

	// 4. Encrypt & send BF key
	string file3 = "../Keys/BF_PrivateKey.txt";
	ifstream inf;
	inf.open(file3.c_str());
	char msgBF[100];
	inf >> msgBF;
	inf.close();

	for (long int i = 0; msgBF[i] != '\0'; i++)
		{rsa.m[i] = msgBF[i];}
	string ebo = "../sockets/BF_KEY_ciphered.txt";
	rsa.encryption(msgBF, file4, ebo);
	// Sending
	char BFK[100];
	ifstream file7;
	file7.open("../sockets/BF_KEY_ciphered.txt");	
	string lies;
	int nls = 0;
	while( getline(file7, lies) )
	{
		nls++;
	} // while 
	file7.close();
	ifstream fss;
	long int gh[100];
	cout << "Sending encrypted BF key:" << endl;
	fss.open("../sockets/BF_KEY_ciphered.txt");
	for (int h = 0; h<nl; h++)
	{
		fss >> gh[h];
		printf("%u", gh[h]);
	}
	fss.close();
	cout << endl;
	for(int j=0; j<nl; j++)
	{ 
		BFK[j] = gh[j];
		printf("%c", gh[j]);	
	}
	cout << endl;
	cout << "Sent" << endl;
	dfc.sendMessage(sock2, BFK);

	cout << endl << "CONFIRMATION" << endl << endl;

	// 5. Receive confirmation message
	cout << "Receiving BF encrypted confirmation:" << endl;
	string fj = "../sockets/BF_encrypted_confirmation";
	dfc.shutdownSocket(sock2, 8, fj);
	bfsh.keyGen(file3);
	bfsh.decrypt(fj);

	close( sock2 );

	return 0;

}// main()
