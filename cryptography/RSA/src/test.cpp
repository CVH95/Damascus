#include <RSA.h>

using namespace std;

int main()
{
	cout << "ASYMMETRIC CRYPTOGRAPHY - RSA ALGORITHM - TEST EXAMPLE" << endl;
	cout << "LEO2 - SDU Robotics" << endl;
	cout << endl;
	RSA secret; 
	
	long int p, q, n;
	char msg[100];

	cout << "Enter the first prime number (p) to generate the key-pair:  ";
	cin >> p;
	cout << endl;
   
	bool inputCheck = secret.isPrime(p);
    	if (inputCheck == false)
    	{
        	cout << "Number is not prime, cannot continue." << endl;;
        	return 0;
    	}

	cout << "Enter the second prime number (q) to generate the key-pair:  ";
	cin >> q;
	cout << endl;

	bool inputCheck2 = secret.isPrime(q);
    	if (inputCheck2 == false || p == q)
    	{

        	cout << "Not a valid input. Cannot continue";
        	return 0;
    	}

    	cout << "Enter the message to send: " << endl;
    	fflush(stdin);
    	cin >> msg;
	cout << endl;

    	for (long int i = 0; msg[i] != '\0'; i++)
        secret.m[i] = msg[i];

	cout << "Generating Keys..." << endl << endl;

	// Get N parameter
    	n = p * q;

	// Getting the least common multiple (Carmichael's totient function):
	long int a = p-1;
	long int b = q-1;
	long int R = secret.LCM(a, b);

	// Computing keys
	secret.compute_e(p, q, R);
    	cout << "Possible Key-Pairs:" << endl;
    	for (long int h = 0; h < secret.j - 1; h++)
	{
	        cout << h << ":   Public Key ( n = " << n <<  ", e = " << secret.e[h] << " )   |     Private Key ( n = " << n << ", d = " << secret.d[h] << " ) " << endl;
	}// for

	int index;
	cout << endl;
	cout << "Select Key Pair:" << endl;
	cin >> index;

	// Testing encryption and decryption
    	secret.encrypt(index, n, msg);
    	secret.decrypt(index, n);

    	return 0;

}// main()

