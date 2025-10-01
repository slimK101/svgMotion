#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include<iostream>
#include<vector>
enum class TokenType {
	OPENTAG,
	CLOSETAG, 
	EQUALS,  
	SLASH, 
	QUOTE,
	TEXT, 

};

struct Token {
	TokenType type;
	std::string value;

	Token(TokenType t, std::string value) : type(t), value(value) {}
};

class  LexicalAnalyzer {
	private:
		std::string input;
		std::vector<Token> tokens;

	public:
		LexicalAnalyzer(std::string input);
		void parseInput(std::string input);

		std::vector<Token>* getTokens() {
			return &tokens;
		}

		
};



#endif