#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include<iostream>
#include<vector>
#include <ctype.h>
#include <fstream>
#include <iterator>
#include <string_view>
#include <stack>
#include "dataStructures\Tree.h"

enum class TokenType {
	OPENTAG,		//<
	CLOSETAG,	    // >
	EQUALS,			// = 
	SLASH,			// /
	QUOTE,			// "
	TEXT,			// Aa-Zz

};


struct Token {
	TokenType type;
	std::string_view value;

	Token(TokenType t, std::string_view value) : type(t), value(value) {}
};
std::ostream& operator<<(std::ostream& os, TokenType t);
class  LexicalAnalyzer {
public:

	std::vector<char>* stringBuffer;
	std::vector<char> buffer;
	std::vector<char>* bufferStart;
	Tree<Token> tokenTree;
	std::stack<Token> tokenStack;
	std::vector<Token> tokens;
	std::streamsize fileSize;
	std::ifstream inFile;
	
	
	



	LexicalAnalyzer();
	void loadInFile(std::string filePath);
	void parseInput();


	void printBuffer();
	std::vector<Token>* getTokens() {
		return &tokens;
	}




};



#endif