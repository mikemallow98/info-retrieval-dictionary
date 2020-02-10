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
    return document_list;
}