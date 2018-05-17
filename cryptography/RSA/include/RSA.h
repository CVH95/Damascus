// RSA CLASS

#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <sstream>


using namespace std;

class RSA{

  public:
	// Declare e as an array to store more than one option.
	long int e[100];
	long int d[100];
	long int m[100];
	long int j;
	long int en[100];	

	bool isPrime(long int pr);
	long int LCM(long int a, long int b);
	void compute_e(long int p, long int q, long int R);
	long int compute_d(long int x, long int R);
	void encrypt(int ind, long int n, char msg[100]);
	void decrypt(int ind, long int n);

	// Individual encryption and decryption functions
	long int randomPrime(long int min, long int max);
	long int primeVerification(long int p, long int q, long int min, long int max);
	void keyGen(long int p, long int q);
	vector<long int> getKey(string filename);
	void encryption(char msg[100]);
	void decryption();

	// Authentication
	void signIdentity();
	void getIdentity();

  private:
	long int temp[100];
    	long int indx;

};
