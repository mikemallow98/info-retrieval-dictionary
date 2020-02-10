#include <iostream>
#include <unistd.h> //required for getopt()
#include "main.hpp"

int main(int argc, char * argv[]){
	//argument parsing
	int k;
	bool inp_flag = false;
	const char * FLAG_LIST = "i:d:p:h";
	while((k = getopt(argc, argv, FLAG_LIST)) != -1){
		switch(k){
			case 'i':
				std::cout << "input file is: " << optarg << std::endl;
				inp_flag = true;
				break;
			case 'd':
				std::cout << "dictionary output file is: " << optarg << std::endl;
				break;
			case 'p':
				std::cout << "postings output file is: " << optarg << std::endl;
				break;
			case 'h':
				std::cout << "Required flags:\n-i <input file>\nOptional flags: \n-d <dictionary output filename> \n-p <posting output filename>" << std::endl;
				exit(-1);
			case '?':
				std::cerr << "Error: Invalid input. Run with -h flag for help." << std::endl;
				exit(-1);
		}
	}
	if(!inp_flag){
		std::cerr << "Error. Missing input file argument. Run with -h for help." << std::endl;
		exit(-1);
	}
}
