#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include<iostream>
#include<vector>
#include <ctype.h>

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
		char* bufferStart;
		int bufferSize = 30;
		std::vector<Token> tokens;


		LexicalAnalyzer();
		void initBuffer(std::string& file);
		void parseInput();


		void printBuffer();
		std::vector<Token>* getTokens() {
			return &tokens;
		}


	
		
};



#endif