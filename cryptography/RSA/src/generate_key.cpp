#include <RSA.h>

using namespace std;

int main()
{
	// Set seed
	srand (time(0));

	cout << "Random Key Generation" << endl;

	RSA secret;

	long int min = 20; // Minimum sufficiently large
	long int max = 100; 
	long int p = secret.randomPrime(min, max);
	long int q = secret.randomPrime(min, max);
	
	// Verify p and q are valid 
	q = secret.primeVerification(p, q, min, max);		

	cout << "Generated: " << p << ", " << q << endl;

	secret.keyGen(p, q);

	cout << endl << "Key-pair saved to RSA/genfiles/" << endl;

	return 0;
}
