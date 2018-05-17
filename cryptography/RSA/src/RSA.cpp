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


// Encryption function (encrypted message of type long int)
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

//----------------------------------------------------------------------------------------------------------------------------------------

// Random prime generation:
long int RSA::randomPrime(long int min, long int max)
{
	//srand (time(NULL));
	while (true)
	{
		long int num = rand() %(max-min +1) + min;
		bool prime = RSA::isPrime(num);
		if(prime == true)
		{
			return num;
		}// if
		
	}// while

}// randomPrime();


// Verify that two prime long ints are not equal
long int RSA::primeVerification(long int p, long int q, long int min, long int max)
{
	while (true)
	{
		if ( q == p ) 
		{
			q = RSA::randomPrime(min, max);
		}// if
		else
		{
			return q;
		}// else

	}// while

}// primeVerification()
	

// Generate RSA key pair
void RSA::keyGen(long int p, long int q)	
{

	long int n = p*q;
	long int a = p-1;
	long int b = q-1;
	long int R = RSA::LCM(a, b);

	RSA::compute_e(p, q, R);

	//cout << "Possible Key-Pairs:" << endl;
    	/*for (long int h = 0; h < j - 1; h++)
	{
	        cout << h << ":   Public Key ( n = " << n <<  ", e = " << e[h] << " )   |     Private Key ( n = " << n << ", d = " << d[h] << " ) " << endl;
	}// for*/

	// Random key selection
	int i = rand() %j;
	long int e_rand = e[i];
	long int d_rand = d[i];

	cout << "Randomly generated Key:" << endl;
	cout << endl;
	cout << "	>> Private Key: n = " << n << ", d = " << d_rand << endl;
	cout << "	>> Private Key: n = " << n << ", e = " << e_rand << endl;

	// Save keys
	ofstream f, g;
	f.open("../Keys/RSA_PrivateKey.txt");
	f << n << " " << d_rand << endl;
	f.close();
	g.open("../Keys/RSA_PublicKey.txt");
	g << n << " " << e_rand << endl;
	g.close();

}// keyGen


// Encryption funtion ready to read and write to files
void RSA::encryption(char msg[100])
{

	ifstream inf;
	inf.open("../Keys/RSA_PublicKey.txt");

	
	long int val;
	vector<long int> values;
	while( inf >> val )
	{
		values.push_back(val);
	}

	inf.close();

	if( values.size() > 2)
	{
		cout << "An error ocurred when reading the Public Key" << endl;
	}

	long int pt, ct, k, len;
	long int n = values[0];
    	long int key = values[1];
	cout << "Public Key: (" << n << ", " << key << ")" << endl;
    	
	indx = 0;
    	len = strlen(msg);
	//char mn[len], te[len];

    	while (indx != len)
    	{
        	pt = m[indx];
        	pt = pt - 96;
        	k = 1;
        
		for (j = 0; j < key; j++)
        	{
        	    k = k * pt;
        	    k = k % n;

        	}// for

	        temp[indx] = k;
	        ct = k + 96;
	        en[indx] = ct;
	        indx++;

	}// while
	//cout << "temp: " << temp << endl;
	cout << "Ciphered BF Key:" << endl;
	
	en[indx] = -1;
	temp[indx] = -1;
	FILE * of;
	of = fopen("../genfiles/BF_Key_ciphered.txt", "w");
	for (indx = 0; en[indx] != -1; indx++)
	{        
		fprintf(of, "%u \n", en[indx]);
		printf("%u", en[indx]);
		
	} // for 
	
	cout << endl;	

	FILE * f;
	f = fopen("../genfiles/temp.txt", "w");
	//cout << "temp:" << endl;
	for (indx = 0; temp[indx] != -1; indx++)
	{        
		fprintf(f, "%u \n", temp[indx]);
		//printf("%u", temp[indx]);
		
	} // for 
	cout << endl;

}// encryption()




void RSA::decryption()
{
	// Get Private Key
	ifstream inf;
	inf.open("../Keys/RSA_PrivateKey.txt");

	
	long int val;
	vector<long int> values;
	while( inf >> val )
	{
		values.push_back(val);
	}

	inf.close();

	if( values.size() > 2)
	{
		cout << "An error ocurred when reading the Public Key" << endl;
	}

	// Get temp value from encryption
	ifstream file;
	file.open("../genfiles/temp.txt");

	string lines;
	int nl = 0;

	while( getline(file, lines) )
	{
		nl++;
	} // while 

	file.close();
	ifstream fs;
	fs.open("../genfiles/temp.txt");
	//cout << "temp:" << endl;
	for (int h = 0; h<nl; h++)
	{
		fs >> temp[h];
		//printf("%u", temp[h]);
	}
	//cout << endl;
	fs.close();

	// cout << "temp: " << temp << endl;

	// Start decryption
	long int pt, ct, k;
	long int n = values[0];
	long int key = values[1];
	cout << "Private Key: (" << n << ", " << key << ")" << endl;
	
	long int i = 0;
	en[10] = -1;
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

}// decryption()
