#ifndef DICTIONARYHANDLER
#define DICTIONARYHANDLER

#include <vector>
#include "postinghandler.hpp"

class DictionaryHandler{
    public:
        DictionaryHandler();
        std::vector<DictionaryEntry> calculate();
        int addEntry(std::vector<Posting> postings);
    private:
        std::vector<Posting> postings_list;
        std::vector<DictionaryEntry> dic_ent;
};


#endif