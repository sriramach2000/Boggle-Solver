/*
Author: Sriram Acharya
Class: CS 301
*/

#include "Dictionary.h"
#include <iomanip>
#include <fstream>
using namespace std;

bool verbose = false;
int numWords = 0;
const int BOARD_SIZE = 4;

void SolveBoard(string board[BOARD_SIZE][BOARD_SIZE], int previous[BOARD_SIZE][BOARD_SIZE], Dictionary& dict, Dictionary& wordsFound, bool printBoard, string stringSoFar,ofstream& out_file);
void SearchForWord(int row, int col, int step_count, string board[BOARD_SIZE][BOARD_SIZE], int previous[BOARD_SIZE][BOARD_SIZE], Dictionary& wordsFound, string stringSoFar, Dictionary& dict, bool printBoard,ofstream& out_file);
void insert_char(int row, int col, int previous[BOARD_SIZE][BOARD_SIZE], string board[BOARD_SIZE][BOARD_SIZE],ofstream& out_file);
int main()
{
	string ans;
	bool printBoard=true;
	string board[BOARD_SIZE][BOARD_SIZE];
	int previous[BOARD_SIZE][BOARD_SIZE];
	
	// code for output file tests 
	ofstream out_file;
	out_file.open("a_u_c_o_test_no.txt");
	
	
	Dictionary dict("BoggleDictionary.txt");

	
	cout << dict.wordCount() << " words loaded." << endl << endl;

	
	string wordSoFar;


	cout << "Enter Board" << endl;
	cout << "-----------" << endl;
	for (int r = 0; r < BOARD_SIZE; r++) {
		cout << "Row " << r << ": ";
		for (int c = 0; c < BOARD_SIZE; c++) {
			
			cin >> board[r][c];
			
		}
	}
	string choice;
	cout << "Show Board (y/n)?: ";
	cin >> choice;
	if (choice == "n") {
		printBoard = false;
	}
	
	Dictionary wordsFound;
	SolveBoard(board, previous,dict ,wordsFound, printBoard,wordSoFar,out_file);
	out_file.close();

	return 0;
}

// This is for Part B
void SolveBoard(string board[BOARD_SIZE][BOARD_SIZE], int previous[BOARD_SIZE][BOARD_SIZE],Dictionary& dict, Dictionary& wordsFound, bool printBoard, string stringSoFar, ofstream& out_file) {
	for (int r = 0; r < BOARD_SIZE; r++) {
		for (int c = 0; c < BOARD_SIZE; c++) {
			previous[r][c] = 0;
		}
	}
	int step_count = 0;
	for (int  r = 0; r < BOARD_SIZE; r++) {
	
		for (int c = 0; c < BOARD_SIZE; c++) {
			
			
			//Initial calls to SolveBoardHelper
			
			SearchForWord(r, c, step_count, board, previous, wordsFound, stringSoFar, dict,printBoard,out_file);	
		}
		
	}
	
}

void SearchForWord(int row, int col, int step_count, string board[BOARD_SIZE][BOARD_SIZE],int previous[BOARD_SIZE][BOARD_SIZE], Dictionary& wordsFound, string stringSoFar, Dictionary& dict, bool printBoard,ofstream& out_file) {
	//intialize the previous board with all 0's
	
	
	if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
		
		return;
	}

	//cannot revisit places youve already been to
	if (previous[row][col] > 0) {
		return;
	}
	
	////if the current string is not a prefix
	if (!dict.isPrefix(stringSoFar)) {
		return;
	}

	// updating string so far with the letter on the board
	stringSoFar += board[row][col];
	step_count++;
	previous[row][col] = step_count;
	//if the word is found, then it is added to a dictionary that keeps track of found words
	if (dict.isWord(stringSoFar) && !wordsFound.isWord(stringSoFar)) {
		wordsFound.addWord(stringSoFar);
		if (printBoard) {
			cout << "Word: " << stringSoFar << endl;
			out_file << "Word: " << stringSoFar << endl;

			cout << "Number of words: " << wordsFound.wordCount() << endl;
			out_file << "Number of words: " << wordsFound.wordCount() << endl;

			insert_char(row, col, previous, board,out_file);
			cout << endl;
			out_file << endl;
		}
		else {
			cout << wordsFound.wordCount() << "\t"<< stringSoFar<<endl;
			out_file << wordsFound.wordCount() << "\t" << stringSoFar << endl;
		}
		
		


	}
	
	
	// to keep track of the step 
	
	

	//recursive calls go here
	SearchForWord(row, col + 1, step_count, board, previous, wordsFound, stringSoFar, dict, printBoard,out_file); // right
	SearchForWord(row , col-1, step_count, board, previous, wordsFound, stringSoFar, dict, printBoard, out_file); // left
	
	SearchForWord(row - 1, col, step_count, board, previous, wordsFound, stringSoFar, dict, printBoard, out_file); // top
	SearchForWord(row + 1, col, step_count, board, previous, wordsFound, stringSoFar, dict,printBoard,out_file); // bottom
	
	SearchForWord(row - 1, col + 1, step_count, board, previous, wordsFound, stringSoFar, dict,printBoard,out_file); // top_right
	SearchForWord(row-1, col - 1, step_count, board, previous, wordsFound, stringSoFar, dict,printBoard,out_file); // top_left
	
	SearchForWord(row + 1, col + 1, step_count, board, previous, wordsFound, stringSoFar, dict,printBoard,out_file); // bottom_right
	SearchForWord(row + 1, col - 1, step_count, board, previous, wordsFound, stringSoFar, dict,printBoard,out_file); // bottom_left
	


	// fills index with 0 if there is no prefix
	
	previous[row][col] = 0;
	
}
// this is simply a format function
void insert_char(int row,int col,int previous[BOARD_SIZE][BOARD_SIZE],string board[BOARD_SIZE][BOARD_SIZE],ofstream& out_file) {
	for (row = 0; row < BOARD_SIZE; row++) {
		
		cout << endl;
		out_file << endl;
		for (col = 0; col < BOARD_SIZE;col++) {
		
			if (previous[row][col] > 0) {
				cout << " "<<"'" << board[row][col] << "'" <<"  ";
				out_file << " " << "'" << board[row][col] << "'" << "  ";
			}
			else {
				cout << "  "<< board[row][col] << "   ";
				out_file << "  " << board[row][col] << "   ";
			}

		}
		cout << "\t";
		out_file << "\t";
		for (col = 0; col < BOARD_SIZE; col++) {

			cout << previous[row][col] << "    ";
			out_file << previous[row][col] << "    ";
		}
		
	}
}
