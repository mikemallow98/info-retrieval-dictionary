#include "postinghandler.hpp"
#include "dictionaryhandler.hpp"

/**
 * The PostingHandler class parses through the TermPairs, creating Postings. Once a new term is found (since TermPair is alphabetical), the old postings will be sent to the DictionaryHanlder to 
 * create a DictionaryEntry for that term. The PostingHandler will return a vector of DictionaryEntry
 * 
 */ 

PostingHandler::PostingHandler(std::vector<TermPair> terms){
    terms_list = terms;
}


/**
 * Goes through the list of the TermPairs, turning them into Postings. These postings are saved in an internal buffer until a new term is reached, at which point the terms will be sent to
 *  the DictionaryHandler.
 */ 
std::vector<DictionaryEntry> PostingHandler::calculate(){
    return dic_ent;
}