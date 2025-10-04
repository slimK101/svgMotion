#include "LexicalAnalyzer.h"



LexicalAnalyzer::LexicalAnalyzer() = default;

void LexicalAnalyzer::initBuffer(std::string& file)
{
	// allocate the buffer on the heap
	this->bufferStart = new char[this->bufferSize];
	// copy the string characters to the buffer
	int i = 0;
	while (i < file.size() && i < this->bufferSize) {
		*(this->bufferStart + i) = file[i];
		i++;
	}
}

void LexicalAnalyzer::printBuffer()
{
	for (int i = 0; i < this->bufferSize; i++) {
		std::cout << *(this->bufferStart + i);
	}
	std::cout << "\n";
}



std::ostream& operator<<(std::ostream& os, TokenType t) {
	switch (t) {
	case TokenType::OPENTAG:    return os << "OPENTAG";
	case TokenType::CLOSETAG:  return os << "CLOSETAG";
	case TokenType::EQUALS:   return os << "EQUALS";
	case TokenType::TEXT:   return os << "TEXT";
	case TokenType::QUOTE:   return os << "QUOTE";
	default:            return os << "Unknown token";
	}
}

void LexicalAnalyzer::parseInput() {

	std::string acc = "";
	// To indicate whether or not were inside a tag 
	bool isInTag = false;
	int i = 0;

	while (i < this->bufferSize) {

		char& p = *(this->bufferStart + i);
		if (isalpha(p) == 0 && p != ' ') { // Character but not a space

			if (acc != "") {
				this->tokens.push_back(Token(TokenType::TEXT, acc));

				acc = "";
			}

			if (p == '<') {
				this->tokens.push_back(Token(TokenType::OPENTAG, std::string() + p));
				isInTag = true;
			}

			if (p == '>') {
				this->tokens.push_back(Token(TokenType::CLOSETAG, std::string() + p));
				isInTag = false;
			}

			if (p == '/') {
				this->tokens.push_back(Token(TokenType::SLASH, std::string() + p));
			}

			if (p == '=') {
				this->tokens.push_back(Token(TokenType::EQUALS, std::string() + p));
			}

			if (p == '"') {
				this->tokens.push_back(Token(TokenType::QUOTE, std::string() + p));
			}
		}
		else if (p == ' ' && isInTag) { // Space but should be parsed 
			if (acc != "") {
				this->tokens.push_back(Token(TokenType::TEXT, acc));

				acc = "";
			}

		}
		else {
			//it's an alphabet
			acc += p;
		}




		i++;
	}
	//Verify last token 
	if (acc != "") {
		this->tokens.push_back(Token(TokenType::TEXT, acc));

		acc = "";
	}




}



