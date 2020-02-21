#include <iostream>
#include <unistd.h> //required for getopt()
#include <string>
#include <vector>

#include "main.hpp"
#include "tokenizer.hpp"
#include "postinghandler.hpp"
#include "results.hpp"

int main(int argc, char * argv[]){
	//argument parsing
	int k;
	bool inp_flag = false;
	const char * FLAG_LIST = "i:d:p:h";
	std::string input_filename;
	std::string dictionary_filename = "dictionary.txt";
	std::string postings_filename = "postings.txt";
	while((k = getopt(argc, argv, FLAG_LIST)) != -1){
		switch(k){
			case 'i':
				std::cout << "input file is: " << optarg << std::endl;
				inp_flag = true;
				input_filename = optarg;
				break;
			case 'd':
				std::cout << "dictionary output file is: " << optarg << std::endl;
				dictionary_filename = optarg;
				break;
			case 'p':
				std::cout << "postings output file is: " << optarg << std::endl;
				postings_filename = optarg;
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
	//various lists needed to pass between classes.
	std::vector<TermPair> t_pairs;
	std::vector<DictionaryEntry> d_entries;

	//run the tokenizer to create the term pair list.
	Tokenizer t1(input_filename);
	t_pairs = t1.tokenize();
	for(auto i = t_pairs.begin(); i != t_pairs.end(); ++i){
		std::cout << i->term << std::endl;
	}

	//Run the PostingHandler to create the dictionary entries list.
	//PostingHandler p1(t_pairs);
	//d_entries = p1.calculate();

	//Run the Results to create the results.
	//Results r1(dictionary_filename, postings_filename, d_entries);
	//r1.print();
}
