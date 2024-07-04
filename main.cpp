//main.cpp

#include <iostream>
#include "2024 alg.h"

int main(){
	bool keepgoing = true;
	while (keepgoing){
		std::cout << "Would you like to run a numerology algorithm?\n";
		std::cout << "1) 2024\n";
		std::cout << "0) quit\n";
		std::string response;
		std::cin >> response;
		if (response.compare("0")==0){
			std::cout << "goodbye\n\n";
			keepgoing = false;
		}else if (response.compare("1")==0){
			main_2024();
		}else{
			std::cout << "Error: You must type the number for one of the options.\n\n";
		}
	}
	return 0;
}
