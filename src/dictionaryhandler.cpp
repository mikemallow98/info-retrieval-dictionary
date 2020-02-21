#include "dictionaryhandler.hpp"


#include <iostream>
/**
 * Given a vector of postings and a term, creates a DictionaryEntry and returns it.
 */ 

DictionaryHandler::DictionaryHandler(){
}

/**
 * Adds another entry to the dictionary.
 */ 
int DictionaryHandler::addEntry(std::string term, std::vector<Posting> postings){
    DictionaryEntry d1;
    d1.term = term;
    d1.document_frequency = postings.size();
    d1.p_list = postings;
    dic_ent.push_back(d1);
    //std::cout << "The term to be added: " << term << " with doc freq of: " << postings.size() << std::endl;
    return 0;
}



/**
 * Creates the list of dictionary entries and returns it. 
 */ 
std::vector<DictionaryEntry> DictionaryHandler::calculate(){
    return dic_ent;
}
