#ifndef POSTINGHANDLER
#define POSTINGHANDLER

#include <string>
#include <vector>

struct Posting{
    int docID;
    int term_frequency;
};

struct DictionaryEntry{
    std::string term;
    int document_frequency;
    std::vector<Posting> p_list;
};


#endif