#include "postinghandler.hpp"

/**
 * The PostingHandler class parses through the TermPairs, creating Postings. Once a new term is found (since TermPair is alphabetical), the old postings will be sent to the DictionaryHanlder to 
 * create a DictionaryEntry for that term. The PostingHandler will return a vector of DictionaryEntry
 * 
 */ 