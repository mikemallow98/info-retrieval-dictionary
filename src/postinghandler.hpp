#ifndef POSTINGHANDLER
#define POSTINGHANDLER

#include <string>
#include <vector>

#include "tokenizer.hpp"

struct Posting{
    int docID;
    int term_frequency;
};

struct DictionaryEntry{
    std::string term;
    int document_frequency;
    std::vector<Posting> p_list;
};

class PostingHandler{
    public: 
        PostingHandler(std::vector<TermPair> terms);
        std::vector<DictionaryEntry> calculate();
    private:
        std::vector<TermPair> terms_list;
        std::vector<DictionaryEntry> dic_ent;
};




#endif