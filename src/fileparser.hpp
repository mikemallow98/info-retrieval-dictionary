#ifndef FILEPARSER
#define FILEPARSER

#include <string>
#include <vector>
#include "tokenizer.hpp"

class FileParser{
    public:
        FileParser(std::string filename);
        std::vector<Document> parse();
    private:
        std::string filename;
        std::vector<Document> document_list;
};

#endif