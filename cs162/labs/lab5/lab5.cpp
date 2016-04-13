#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <istream>
#include <string>
#include <fstream>


using namespace std;



class Filter {
	private:
	
	string fromfile;
	
	public:
	
		string takeInput() {
			ifstream myfile("input.txt");
			if (myfile.is_open()){
				while(getline(myfile,fromfile)){
				return fromfile;
				}
				myfile.close();
			}	
		}
		
		void giveOutput(string message) {
			ofstream outfile("output.txt");
			if (outfile.is_open()){
				outfile << fromfile << endl;
			}
		}
		
		char transform(char ch){
		
		}
	
	
};


class Copy: public Filter{ 

};

class Encryption: public Filter{ 
	
	private:
		
		
	public:
	
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
	

};


class UpperCase: public Filter{
	private:
	
	public:
	
		void Raiseup(string msg) {
			std::locale loc;
			for (int i = 0; i < msg.length(); i++) {
				
			cout << toupper(msg[i], loc);
			}
		}
};

int main() { 
	UpperCase fileYell;
	Encryption fileEncode;
	string msg;
	char key[20];
	
	
	msg = fileEncode.takeInput();
	
	msg = fileEncode.encryptDecrypt(msg, key);
	
	fileEncode.giveOutput(msg);
	
	//fileYell.Raiseup(msg);
	
	return 0;
}
	