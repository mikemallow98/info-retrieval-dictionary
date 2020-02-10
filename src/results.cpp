#include "results.hpp"

/**
 * Prints the two output files based on an input of a vector of DictionaryEntry
 * 
 */ 

Results::Results(std::string ofile, std::string pfile, std::vector<DictionaryEntry> d_ent){
    output_filename = ofile;
    post_filename = pfile;
    entries = d_ent;
}


/**
 * Prints the results to the output files. The results will be calculated in private methods (undefined) based on the vector of dictionaryentry. 
 */ 
void Results::print(){

}