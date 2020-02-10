#include "tokenizer.hpp"

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
