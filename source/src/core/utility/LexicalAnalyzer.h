#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include<iostream>
#include<vector>
#include <ctype.h>
#include <fstream>

enum class TokenType {
	OPENTAG,		//<
	CLOSETAG,	    // >
	EQUALS,			// = 
	SLASH,			// /
	QUOTE,			// "
	TEXT,			// Aa-Zz

};

std::ostream& operator<<(std::ostream& os, TokenType t);

struct Token {
	TokenType type;
	std::string value;

	Token(TokenType t, std::string value) : type(t), value(value) {}
};

class  LexicalAnalyzer {
public:
	std::ifstream inFile;
	std::string str;
	std::string fileContents;
	char* bufferStart;
	std::streamsize bufferSize = 600;
	int bufferCount;
	std::streamsize fileSize;
	std::vector<Token> tokens;
	



	LexicalAnalyzer();
	void loadInFile(std::string filePath);
	void parseInput(std::streamsize bytesread);


	void printBuffer();
	std::vector<Token>* getTokens() {
		return &tokens;
	}




};



#endif