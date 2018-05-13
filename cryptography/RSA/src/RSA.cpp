// Simple implementation of the RSA algorithm

#include<RSA.h>


using namespace std;


// Function that checks if a number is prime.
bool RSA::isPrime(long int pr)
{

    int i;
    j = sqrt(pr);
    for (i = 2; i <= j; i++)
    {

        if (pr % i == 0)
            return false;

    }

    return true;

}


// Function to compute the Least Commont Multiple of two long integers.
long int RSA::LCM(long int a, long int b)
{
	long int hcf, temp, lcm;
	hcf = a;
    	temp = b;
    
    	while(hcf != temp)
    	{
        	if(hcf > temp)
            		hcf -= temp;
        	else
            		temp -= hcf;
    	}// while

    	lcm = (a * b) / hcf;

	return lcm;

}// LCM

// Calculate modular exponential parameter e (public key)
void RSA::compute_e(long int p, long int q, long int R)
{
	long int k;
	k = 0;
	long int joker;

	for (long int i = 2; i < R; i++)
	{
		if (R % i == 0)
	       	    continue;

        	bool check_i = isPrime(i);
        	if (check_i == true && i != p && i != q)
	        {
		            e[k] = i;
		            joker = RSA::compute_d(e[k], R);

		            if (joker > 0)
		            {
		                d[k] = joker;
               		 	k++;
		            }//if 

		            if (k == 99)
		                break;
	        }// if

    	}// for

}// compute_e()


// Calculate modular exponential parameter d (private key)
long int RSA::compute_d(long int x, long int R)
{
    long int k = 1;
    while (1)
    {
        k = k + R;
        if (k % x == 0)
            return (k / x);
    }// while

}// compute_d()


// Encryption function
void RSA::encrypt(int ind, long int n, char msg[100])
{
    	long int pt, ct, k, len;
    	long int  key = e[ind];
    	long int i = 0;

    	len = strlen(msg);

    	while (i != len)
    	{
        	pt = m[i];
        	pt = pt - 96;
        	k = 1;
        
		for (j = 0; j < key; j++)
        	{
        	    k = k * pt;
        	    k = k % n;

        	}// for

	        temp[i] = k;
	        ct = k + 96;
	        en[i] = ct;
	        i++;

	}// while

    	en[i] = -1;
    	cout << endl;
    	cout << "Encrypted Message:" << endl;
    	for (i = 0; en[i] != -1; i++)
	{        
		printf("%c", en[i]);
	} // for 
	cout << endl;

}// encrypt


// Decryption function
void RSA::decrypt(int ind, long int n)
{
	long int pt, ct, k;
	long int  key = d[ind];
    	long int i = 0;

    	while (en[i] != -1)
	{

	        ct = temp[i];
	        k = 1;

	        for (j = 0; j < key; j++)
	        {
            		k = k * ct;
		        k = k % n;

        	}// for

        	pt = k + 96;
	        m[i] = pt;
	        i++;

	}// while

    	m[i] = -1;
	cout << endl;	
   	cout << "Decrypted Message:" << endl;
    	for (i = 0; m[i] != -1; i++)
	{
        	printf("%c", m[i]);
	} //for
	cout << endl;

}// decrypt()
