#include "tokenizer.hpp"
#include <iostream>
#include <ctype.h>
#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "fileparser.hpp"

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
    for( auto i = retval.begin(); i != retval.end(); ++i){
        std::cout << *i << std::endl;
    }   
    return retval;
}
/**
 * Removes all symbols listed in the char array sent as a parameter. Important, do not send a period as that needs to be treated in a special case.
 */ 
void Tokenizer::remove_punct(Document &d1, char symbols[]){
    boost::remove_erase_if(d1.contents, boost::is_any_of(symbols));
    //removing all periods that do not separate two numbers
    std::string::iterator prev = d1.contents.begin();
    std::string::iterator cur;
    if(*prev == '.'){
        prev = d1.contents.erase(prev);
        cur = ++prev;
    }
    else{
        for(cur = ++prev; cur <= d1.contents.end() -1; ++cur){
            if(*cur == '.'){
                if(isdigit(*prev)){
                    ++cur;
                    if(cur >= d1.contents.end()){
                        if(isdigit(*cur)){
                            cur--;
                        }
                        else{
                            //remove period
                            --cur;
                            cur = d1.contents.erase(cur);
                            prev = --cur;
                            return;
                        }
                    }
                    else{
                        //remove period and return because end of line.
                        --cur;
                        cur = d1.contents.erase(cur);
                        return;             
                    }
                }
                else{
                    //remove period
                    cur = d1.contents.erase(cur);
                    prev = --cur;
                }
            }
            prev++;
        }
    }

}

/**
 * Converts all alphabetical characters to lowercase.
 */ 
void Tokenizer::case_fold(Document &d1){
    boost::to_lower(d1.contents);
}
/**
 * First calls the fileparser to parse the file. After that, makes calls to private methods to tokenize the terms and then returns a vector<TermPair> of the terms.
 */ 
std::vector<TermPair> Tokenizer::tokenize(){  
    char C_REMOVE[] = {'-', '\'', '(', ')', ',', '?', ';', ':', '%', '$', '#', '@', '!', '&','*'};
    std::vector<TermPair> terms;
    FileParser fp(inp_file);
    docs = fp.parse();
    for(auto i = docs.begin(); i != docs.end(); ++i){
        case_fold(*i);
        remove_punct(*i, C_REMOVE);
        removeSpaces(i->contents);
    }
    return terms;
}

/*
https://iq.opengenus.org/porter-stemmer/
Following this link to apply Porter's Stemmer algorithm
*/

vector<string> Tokenizer::PorterStemmer(string input){

}

/*
The word "Y" is a consonant if it is preceded by a consonant, otherwise it is a vowel
*/

bool Tokenizer::consonant(vector<string> input,int i){

    if(input.at(i)=="a" or input.at(i)=="e" or input.at(i)=="i" or input.at(i)=="o" or input.at(i)=="u") return 0;
    else return 1;

    if(input.at(i)=="y" and (input.at(i-1)!="a" or input.at(i-1)!="e" or input.at(i-1)!="i" or input.at(i-1)!="o" or input.at(i-1)!="u")) return 0;
    else return 1;
}
/*
Words other than consonantes are vowels
*/
bool Tokenizer::vowel(vector<string> input,int i){
    if(consonant(input,i)==0) return 1;
    else return 0;
}

/*
Returns true if the input string str ends with "ending" string 
*/

bool Tokenizer::endsWith(string& str, string& ending){
    if (str.length() >= ending.length()) {
        return (0 == str.compare (str.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

/*bool Tokenizer::doubleConsonant(string& input){
    if (input.length()>=2){
      if(consonant(input.at(input.length())) and consonant(input.at(input.length()-1)) ) return true;
      else return false;
    }
    return false;
}*/



