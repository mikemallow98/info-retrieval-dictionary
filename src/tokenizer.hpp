#ifndef TOKENIZER
#define TOKENIZER

#include <string>
#include <vector>


struct Document{
    int id;
    std::string contents;
};

struct TermPair{
    std::string term;
    int docID;
};

class Tokenizer{
    public:
        Tokenizer(std::string input_filename);
        std::vector<TermPair> tokenize();
    private:
        std::string inp_file;
        std::vector<Document> docs;
};



#endif