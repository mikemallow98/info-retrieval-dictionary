#ifndef RESULTS
#define RESULTS

#include <string>
#include <vector>

#include "postinghandler.hpp"

class Results{
    public:
        Results(std::string ofile, std::string pfile, std::vector<DictionaryEntry> d_ent);
        void print();
    private:
        std::string output_filename;
        std::string post_filename;
        std::vector<DictionaryEntry> entries;
};
#endif