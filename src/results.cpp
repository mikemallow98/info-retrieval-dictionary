#include "results.hpp"

#include <fstream>
#include <iostream>

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
    std::ofstream dictionary_writer;
    std::ofstream posting_writer;
    dictionary_writer.open(output_filename);
    posting_writer.open(post_filename);
    create_offset();
    int offset = 0;
    if(!dictionary_writer.is_open()){
        std::cerr << "No work" << std::endl;
    }
    for(auto i = entries.begin(); i != entries.end(); ++i){
        dictionary_writer << i->term << "\t" << offset << std::endl;
        offset = offset + i->document_frequency;
        for(auto k = i->p_list.begin(); k != i->p_list.end(); ++k){
            posting_writer << k->docID << "\t" << k->term_frequency << std::endl;
        }
    }
    dictionary_writer.close();
    posting_writer.close();
}