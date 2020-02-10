#include <iostream>
#include <fstream>

#include "fileparser.hpp"

/**
 * The FileParser class parses the input file, turning each line into a Document. The Document struct is a tuple with docID and contents.
 * 
 * 
 */ 

FileParser::FileParser(std::string filename){
    this->filename = filename;
}


/**
 * Creates documents based on the input file. Each line is a new document. A vector of these documents is returned. 
 */ 
std::vector<Document> FileParser::parse(){
    using namespace std;
    int nextID = 0;
    ifstream input_file;
    input_file.open(filename);
    if(!input_file.is_open()){
        cerr << "Input file is invalid. Exiting..." << endl;
        exit(-1);
    }
    string line = "";
    Document d1;
    while(getline(input_file, line)){
        d1.id = nextID;
        d1.contents = line;
        nextID++;
        document_list.push_back(d1);
    }
    input_file.close();

    return document_list;
}