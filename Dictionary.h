#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
enum alphabet {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z};

const int LETTERS = 26;
struct Node {
	// Your data structure goes here
	
	Node* letters[LETTERS];
	//flag 
	bool isWord;
	Node() {
	
		for (int i = 0; i < LETTERS; i++) {
			letters[i] = NULL;
		}
	
	}
};

class Dictionary
{
public:
	Dictionary();
	Dictionary(string file);
	void addWord(string word);
	bool isWord(string word);
	bool isPrefix(string word);
	
	int wordCount();

private:
	Node* root;
	int numWords;
	//void addChar(char* letters[]);
	// Any private methods you need/want
};


