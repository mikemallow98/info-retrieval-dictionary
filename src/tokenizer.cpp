#include "tokenizer.hpp"
#include <iostream>

#include "fileparser.hpp"


/**
 * The tokenizer first creates the FileParser and calls parse. The return of parse is a vector of documents. Tokenizer will then do the following:
 * 1. Remove special symbols
 * 2. case-fold (convert to lower case)
 * 3. Stem
 * During this process, each term will be added a vector of TermPair
 * 
 * After doing this, the tokenizer will sort the terms alphabetically and return the list. 
 * 
 */



Tokenizer::Tokenizer(std::string input_filename){
    inp_file = input_filename;
}

/**
 * First calls the fileparser to parse the file. After that, makes calls to private methods to tokenize the terms and then returns a vector<TermPair> of the terms.
 */ 
std::vector<TermPair> Tokenizer::tokenize(){
    std::vector<TermPair> terms;
    std::vector<Document> docs;
    FileParser fp(inp_file);
    docs = fp.parse();

    return terms;
}

