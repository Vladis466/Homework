#include <iostream>
#include <stdlib.h>
#include <iso646.h>
#include <string.h>
#include <istream>
#include <string>
using namespace std;


#include <iostream>

using namespace std;

string encryptDecrypt(string toEncrypt, char key[]) {
   
    string output = toEncrypt;
    int dummy;
	
    for (int i = 0; i < toEncrypt.size(); i++) {
		dummy = i % strlen(key);

        output[i] = (output[i] ^ key[dummy]);
		cout << key[dummy];
	
		cout << output[i] << endl;
	}
    cout << output << endl;
    return output;
}


int main()
{
	char key[50];
	string sentence;
	cout << "Enter a keyword" << endl;
	cin >> key;
	
	
	cout << "Enter a sentence less than 100 lines long."<< endl ;
	cin >> sentence;
	
	
	
    string encrypted = encryptDecrypt(sentence, key);
    cout << "Encrypted:" << encrypted << "\n";
    
    string decrypted = encryptDecrypt(encrypted, key);
    cout << "Decrypted:" << decrypted << "\n";
    
    return 0;
}
 
 
 
 
 
/* string codewriter(char key, char words[]) {

char codeMessage = words;


	for (int i = 0; i < strlen(words); i++) {
		codeMessage[i] = codeMessage[i] ^ key;	
	}

	return codeMessage;
}


main() {
	
	char key[100]; 
	char sentence[101];
	
	
	cout << "Enter a keyword" << endl;
	cin >> key;
	
	cout << "Enter a sentence less than 100 lines long."<< endl ;
	cin.getline(sentence, 100, '\n'); 
	cin >> sentence;
	
	codewriter(key, sentence);
	

	
	cout << "The encrypted data = " << sentence << endl;
}


 */