#ifndef TOKENIZER
#define TOKENIZER

#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>

using namespace std;


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
        vector<string> PorterStemmer(string input);
    private:
        
        std::string inp_file;
        std::vector<Document> docs;
        void case_fold(Document &d1);
        void remove_punct(Document &d1 , char symbols[]);
        std::vector<std::string> removeSpaces(std::string line);
        bool consonant(vector<string> input,int i);
        bool vowel(vector<string> input,int i);
        bool endsWith(string& str, string& ending);
        //bool doubleConsonant(vector <string> input);


};



#endif