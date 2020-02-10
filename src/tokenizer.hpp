#ifndef TOKENIZER
#define TOKENIZER

#include <string>

struct Document{
    int id;
    std::string contents;
};

struct TermPair{
    std::string term;
    int docID;
};

#endif