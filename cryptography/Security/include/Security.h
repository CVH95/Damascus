// SECURITY CLASS

// General
#include <iostream>
#include <fstream> 
#include <vector>
#include <math.h> 
#include <numeric>
#include <algorithm>
#include <iterator>
#include <boost/foreach.hpp>
#include <string>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <cstdlib>
#include <time.h> 

using namespace std;


class Security{
   public:
	
	bool verifyAuthentication(string filename);
	int createSocket(int port);
	int sendMessage(int socket, char msg[100]);
	void readMessage(int socket, string file);
	long int readKey(int socket);
	void readCrypto(int socket, int length, string file);
	void shutdownSocket( int socket, int length, string file);
	void savePublicKey(long int n, long int e, string file);

   //private:
	

};
