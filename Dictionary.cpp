#include "Dictionary.h"
#include <fstream>
Dictionary::Dictionary()
{
    root = new Node;
    numWords = 0;
    
}

Dictionary::Dictionary(string file)
{
    
    root = new Node;
    numWords = 0;
    ifstream dict_file;
    string words;

    dict_file.open(file.c_str());
    if (!dict_file) {
        cerr << "file not found" << endl;
    
    }
    while (!dict_file.eof()) {
        dict_file >> words;
        addWord(words);
    }
    dict_file.close();

    
}

void Dictionary::addWord(string word)
{
   //Pre word is given in dictionary file
   //Post: word is added to dictionary
    
    Node* currNode = root;

    for (int i = 0; i < word.size(); i++) {
        
        if (currNode->letters[word[i]-(int)'a'] == NULL) {
            
            currNode->letters[word[i] - (int)'a'] = new Node;
            
            currNode->letters[word[i] - (int)'a']->isWord = false;
            
        
        }
        
        currNode = currNode->letters[word[i] - (int)'a'];
    }

    numWords += 1;
    currNode->isWord = true;
}



bool Dictionary::isPrefix(string word)
{
    //Pre: word read is correct
    //Post: will return true if the path for prefix exists else will return false
    int i = 0;
   
    Node* currNode = root;
    
    for (int i = 0; i < word.size(); i++) {

        if (currNode->letters[word[i] - (int)'a'] == NULL) {
           
            return false;
        }
        currNode = currNode->letters[word[i] - (int)'a'];
    }

  
    return true;
    
    
}
bool Dictionary::isWord(string word)
{
    //Pre: word exists in dictionary
    //Post: will return true if a path exists for that word
    Node* currNode = root;
    
    //check for dict being empty
    if (numWords == 0) {
        return false;
    }
    int i = 0;
    
    while (currNode != NULL  && i < word.size() ) {
        
       currNode = currNode->letters[word[i] - (int)'a']; 
       if (currNode == nullptr) {
           return false;
       }
       i++;
    }
    
    
    return currNode->isWord;

}
int Dictionary::wordCount()
{
    return numWords;
}


