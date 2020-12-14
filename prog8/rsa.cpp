#include <bits/stdc++.h>
#define int long long
using namespace std;

int gcd(int a, int b){
	while(b){
		a %= b;
		swap(a,b);
	}
	return a;
}

int prime(int x){
	for(int i=2; i*i<=x; i++)
		if(x%i == 0)
			return false;
	return true;
}

int encrypt(char c, int n, int e){
	int temp = 1;
	for(int i=0; i<e; i++)
		temp = (temp*c) % n;
	return temp;
}

char decrypt(int c, int n, int d){
	int temp = 1;
	for(int i=0; i<d; i++)
		temp = (temp*c)%n;
	return temp;
}
int cipher[10001];
int32_t main(){
	string input,output;
	cout << "Enter text upto 10000 characters" << endl;
	getline(cin, input);
	int len = input.size();
	
	int p, q;
	do{
		p = rand() % 1000;
	}while(!prime(p));
	do{
		q = rand() % 1000;
	}while(!prime(q));
	int n = p*q;
	int phi = (p-1)*(q-1);
	int e;
	do{
		e = rand() % phi;
	}while(gcd(e,phi)!=1);
	int d;
	do{
		d = rand() % phi;
	}while((d*e)%phi != 1);
	
	cout << "Two primes are " << p << " " << q << endl;
	cout << "n = " << p*q << endl;
	cout << "Phi(n) = " << phi << endl;
	cout << "Public key (n,e) = " << n << " " << e << endl;
	cout << "Private key (n,d) = " << n << " " << d << endl;
	for(int i=0; i<len; i++)
		cipher[i] = encrypt(input[i], n, e);
	cout << "Encrypted message - " ;
	for(int i=0; i<len; i++)
		cout << cipher[i];
	cout << endl;
	for(int i=0; i<len; i++)
		output += decrypt(cipher[i], n, d);
	cout << "Decrypted message - " << output << endl;
	
}
