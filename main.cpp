#include <iostream>
#include<vector>
#include <string>

using namespace std;

// Function to find the greatest common divisor using the Euclidean algorithm
// Returns gcd(a, b) and calculates coefficients x and y such that ax + by = gcd(a, b)
int Evklid(int a, int b, int* x, int* y) {
	if (a == 0) {
		*x = 0;
		*y = 1;
		return b;
	}
	int x1, y1;
	int gcd = Evklid(b % a, a, &x1, &y1);
	*x = y1 - (b / a) * x1;
	*y = x1;
	return gcd;
}

// Function to check if a number is a prime number
// Returns true if the number is prime, otherwise returns false
int ifPrimeNumber(int a) {
	int b = 2, _sum = 0;
	while (b * b <= a && _sum == 0) {
		if (a % b == 0) {
			_sum++;
		}
		b++;
	}
	if (_sum == 0) return true;
	return false;
}

// Function to generate large prime numbers
// Updates variables q and p with two distinct prime numbers
void generateBigNumbers(int countOfNumbers, int& q, int& p) {
	for (int i = 1000000; countOfNumbers != 2; i++)
	{
		if (i > 1000000 && ifPrimeNumber(i)) {
			(countOfNumbers == 0) ? p = i : q = i;
			countOfNumbers++;
		}
	}
}

// Function to convert a number to its binary representation as a string
string binaryNumber(int number) {
	string output;
	while (number > 0) {
		output += ((number % 2) + 48);
		number /= 2;
	}
	output += '0';
	reverse(output.begin(), output.end());
	return output;
}

// Function to add a parity bit to a binary string based on the number of '1's in it
string parityBit(string text) {
	int countOfUnits = 0;
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == 49) countOfUnits++;
	}
	if (countOfUnits % 2 == 0) {
		reverse(text.begin(), text.end());
		text.push_back('0');
		reverse(text.begin(), text.end());
	}
	else {
		reverse(text.begin(), text.end());
		text.push_back('1');
		reverse(text.begin(), text.end());
	}
	return text;
}

// Function to calculate (base^exp) mod mod using modular exponentiation
int powMod(int base, int exp, int mod) {
	int result = 1;
	base %= mod;
	while (exp > 0) {
		if (exp & 1) {
			result = (result * base) % mod;
		}
		exp /= 2;
		base = (base * base) % mod;
	}
	return result;
}

// Function to calculate the block size for encryption based on the maximum of e and N
int blockSize(int N) {
	int count = 0;
	for (; N != 1; N /= 2)
	{
		count++;
	}
	return count;
}

// Function to encrypt a string using RSA algorithm
// Returns a vector containing encrypted integers
vector<int> encrypt(string text, int e, int N) {
	vector<int> encrypted_text;
	string block;
	int block_size = blockSize(max(e, N));
	for (int c : text)
	{
		int num = (int)c;
		string binary = binaryNumber(num);
		block += binary;
		if (block.size() >= block_size) {
			block = parityBit(block);
			int block_num = stoi(block, nullptr, 2);
			int encrypted_char = powMod(block_num, e, N);
			encrypted_text.push_back(encrypted_char);
			block = "";
		}
	}
	return encrypted_text;
}

int main() {
	int countOfNumbers = 0, p, q, e, N, funcOfEiler, x, y, d, closeKey[2] = {}, openKey[2] = {};
	generateBigNumbers(countOfNumbers, p, q);
	p = 19, q = 41; // only for example, for real, we must use function "generateBigNumbers"
	N = p * q, funcOfEiler = (p - 1) * (q - 1);
	for (int i = funcOfEiler; i > 0; i--)
	{
		if (i % funcOfEiler != 0 && ifPrimeNumber(i)) {
			e = i;
			break;
		}
	}
	Evklid(funcOfEiler, e, &x, &y);
	if (x > 0) swap(x, y);
	if (x < 0) x = -(x);
	d = funcOfEiler - x;
	closeKey[0] = d, closeKey[1] = N;
	openKey[0] = e, openKey[1] = N;
	string text = "Hello"; // text example
	vector<int> output = encrypt(text, e, N);
	for (int i : output)
	{
		cout << i;
	}
}
