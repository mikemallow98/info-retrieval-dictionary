#include "tokenizer.hpp"

#include <iostream>
#include <cctype>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

#include "fileparser.hpp"
#include "stemmer.h"

/**
 * The tokenizer first creates the FileParser and calls parse. The return of parse is a vector of documents. Tokenizer will then do the following:
 * 1. Remove special symbols
 * 2. case-fold (convert to lower case)
 * 3. Stem
 * During this process, each term will be added a vector of TermPair
 * 
 * After doing this, the tokenizer will sort the terms alphabetically and return the list. 
 * 
 */
Tokenizer::Tokenizer(std::string input_filename){
    inp_file = input_filename;
}

/**
 * Removes spaces. Returns a string vector of the terms.
 * TODO: small error- includes empty strings in the list. Need to clean list at some point... Maybe in the TermPair creation stage?
 */ 
std::vector<std::string> Tokenizer::removeSpaces(std::string line){
    std::vector<std::string> retval;
    boost::algorithm::split(retval, line, boost::algorithm::is_any_of(" "));  
    return retval;
}
/**
 * Removes all symbols listed in the char array sent as a parameter. Important, do not send a period as that needs to be treated in a special case.
 */ 
void Tokenizer::remove_punct(Document &d1, char symbols[]){
    std::string::iterator prev = d1.contents.begin();
    std::string::iterator cur;
    if(*prev == '.' || *prev == '-' || *prev == '\''   || *prev == '(' || *prev == ')' || *prev == ',' || *prev == '?' || *prev == ';' || *prev == ':' || *prev == '%' || *prev == '$'|| *prev == '#'|| *prev == '@'|| *prev == '!'|| *prev== '&'|| *prev== '*' || *prev == '`' || *prev == 39){
        prev = d1.contents.erase(prev);
        cur = prev + 1;
    }
        for(cur = prev +1; cur <= d1.contents.end() -1; ++cur){
            if(*cur == '.'){
                if(std::isdigit(*prev)){
                    ++cur;
                    if(cur <= d1.contents.end()){
                        if(std::isdigit(*cur)){
                            //this means the period is in between two numbers and should be ignored.
                            cur--;
                        }
                        else{
                            //remove period
                            --cur;
                            cur = d1.contents.erase(cur);
                            prev =  cur -1;
                        }
                    }
                    else{
                        //remove period 
                        --cur;
                        cur = d1.contents.erase(cur);                                
                    }
                }
                else{
                    //remove period
                    cur = d1.contents.erase(cur);
                    prev =  cur -1;
                }
            }
            if(*cur == '-' || *cur == '\'' || *cur == '(' || *cur == ')' || *cur == ',' || *cur == '?' || *cur == ';' || *cur == ':' || *cur == '%' || *cur == '$'|| *cur == '#'|| *cur == '@'|| *cur == '!'|| *cur == '&'|| *cur == '*' || *cur == '`' || *cur == 39){
                cur = d1.contents.erase(cur);
                prev = cur -1;
            }
            
            prev++;
        }
}

/**
 * Converts all alphabetical characters to lowercase.
 */ 
void Tokenizer::case_fold(Document &d1){
    boost::to_lower(d1.contents);
}

void Tokenizer::add_to_term_list(std::string termIn, int docIDIn){
    TermPair temp;
    temp.docID = docIDIn;
    temp.term = termIn;
    terms.push_back(temp);
}

/**
 * Comparison method needed for sorting the terms alphabetically.
 */ 
static bool compare_terms(TermPair t1, TermPair t2){
    return t1.term < t2.term;
}

/**
 * Sorts terms alphabetically, using the compare_terms static method as the comparator.
 */ 
void Tokenizer::sort_terms(){
    std::sort(terms.begin(), terms.end(), compare_terms);
}

/**
 * First calls the fileparser to parse the file. After that, makes calls to private methods to tokenize the terms and then returns a vector<TermPair> of the terms.
 */ 
std::vector<TermPair> Tokenizer::tokenize(){  
    char C_REMOVE[] = {'-', '\'', '(', ')', ',', '?', ';', ':', '%', '$', '#', '@', '!', '&','*'};
    std::vector<std::string> tmp_str;
    FileParser fp(inp_file);
    docs = fp.parse();
    //std::cout << "The number of documents is: " << docs.size() << std::endl;
    for(auto i = docs.begin(); i != docs.end(); ++i){
        case_fold(*i);
        remove_punct(*i, C_REMOVE);
        tmp_str = removeSpaces(i->contents);
        for(auto s = tmp_str.begin(); s != tmp_str.end(); ++s){
            add_to_term_list(*s, i->id);
        }
    }
    //std::cerr << "No seg fault before the stemming " << terms.size() << std::endl;
    //runs the terms through Porter's stemmer.  
    for(auto i = terms.begin(); i != terms.end(); ++i){
        //std::cerr << i->term << "->";
        char tmp[i->term.length() +  4];
        int m;
        std::strcpy(tmp, i->term.c_str());
        m = stem(tmp, 0, i->term.length()-1);
        std::string str1 = i->term.substr(0, m+1);
        i->term = str1;
        //std::cerr << i->term << " "<< i->docID <<std::endl;
    }
    //std::cerr << "Stemming is done" << std::endl;
    sort_terms();
    return terms;
}

