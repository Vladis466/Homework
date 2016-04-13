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
	
	
	
};


int main() { 
	
	Filter fileEncode;
	string msg;
	
	msg = fileEncode.takeInput();
	fileEncode.giveOutput(msg);
	
	return 0;
}
	