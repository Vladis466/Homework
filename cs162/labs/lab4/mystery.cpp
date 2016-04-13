/**
 * This is a mystery function! You need to figure out what it does.
 */

#include <iostream>
#include <string>


std::string mystery(std::string s);
std::string mystery_helper(std::string s, std::string result);

int main() {
	std::cout << mystery("dog") << std::endl;
}

std::string mystery(std::string s) {
	std::string temp;
	return mystery_helper(s, temp);
}

std::string mystery_helper(std::string s, std::string result) {
	if( s.length() == 0 ) 
		return result;
	else {
		return mystery_helper(s.substr(1,s.length()-1),s.substr(0,1)+result);
	}
}


