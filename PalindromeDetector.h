#ifndef PALINDROMEDETECTOR_H_
#define PALINDROMEDETECTOR_H_

#include <string>
using namespace std;


class PalindromeDetector {
public:
	PalindromeDetector(string inFilename, string outFileName);
	void detectPalindromes();

private:
	string myInFileName;
	string myOutFileName;

	bool isPalindrome(string line);
};

#endif /* PALINDROMEDETECTOR_H_ */
