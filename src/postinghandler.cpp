#include "postinghandler.hpp"
#include "dictionaryhandler.hpp"

#include <algorithm>
#include <iostream>

/**
 * The PostingHandler class parses through the TermPairs, creating Postings. Once a new term is found (since TermPair is alphabetical), the old postings will be sent to the DictionaryHandler to 
 * create a DictionaryEntry for that term. The PostingHandler will return a vector of DictionaryEntry
 * 
 */ 

PostingHandler::PostingHandler(std::vector<TermPair> terms){
    terms_list = terms;
}

/**
 * comparison function between TermPairs, comparing based on documentID. 
 * 
 * Returns true if t1 has a smaller document id than t2 (e.g. doc 1 < doc2)
 */ 
 bool PostingHandler::compare_terms(TermPair t1, TermPair t2){
	 if(t1.docID < t2.docID){
		 return true;
	 }
	 return false;
 }

/**
 * Goes through the list of the TermPairs, turning them into Postings. These postings are saved in an internal buffer until a new term is reached, at which point the terms will be sent to
 *  the DictionaryHandler.
 */ 
std::vector<DictionaryEntry> PostingHandler::calculate(){
	DictionaryHandler dict_handler;
	std::vector<TermPair> temp_buffer;
	std::vector<Posting> posting_buffer;
	std::string current_term = terms_list.begin()->term;
	for(auto term_itr = terms_list.begin(); term_itr != terms_list.end(); ++term_itr){
		if(term_itr->term.compare(current_term) == 0){
			temp_buffer.push_back(*term_itr);
		} else{ //Create a Postings entry and send it to the DictionaryHandler
			std::sort(temp_buffer.begin(), temp_buffer.end(), PostingHandler::compare_terms);
			int k =0;
			int docID = temp_buffer.begin()->docID;
			Posting tmp;
			for(auto post_itr = temp_buffer.begin(); post_itr != temp_buffer.end(); ++post_itr){
				if(post_itr->docID == docID){
					k++;
				} else{
					tmp.docID = docID;
					tmp.term_frequency = k;
					posting_buffer.insert(posting_buffer.begin(), tmp);
					k = 1;
					docID = post_itr->docID;
				}
				//need to add for the end of the vector sending it as well
			}
			tmp.docID = docID;
			tmp.term_frequency = k;
			posting_buffer.insert(posting_buffer.begin(), tmp);
			//std::cout << "current term: " << current_term << " " << posting_buffer.size() << std::endl;
			dict_handler.addEntry(current_term, posting_buffer);
			current_term = term_itr->term;
			posting_buffer.erase(posting_buffer.begin(), posting_buffer.end());
			temp_buffer.erase(temp_buffer.begin(), temp_buffer.end());
			temp_buffer.push_back(*term_itr);
		}
		
	}
	dic_ent = dict_handler.calculate();
    return dic_ent;
}
