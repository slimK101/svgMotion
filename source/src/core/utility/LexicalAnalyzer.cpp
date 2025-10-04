#include "LexicalAnalyzer.h"



LexicalAnalyzer::LexicalAnalyzer() = default;

void LexicalAnalyzer::loadInFile(std::string filePath)
{
	inFile.open(filePath, std::ios::in | std::ios::binary | std::ios::ate);

	if (inFile.is_open()) { // TODO : Add error handling
		inFile.seekg(0, std::ios::end);
		fileSize = inFile.tellg();
		this->bufferStart = new char[this->bufferSize];
		//Getting the buffer count before segmenting the file
		//TODO : assigning automatic buffer size , have to run benchmarks first
		std::streamsize remainder = fileSize % this->bufferSize;
		bufferCount = remainder > 0 ? fileSize / this->bufferSize + 1 : fileSize / this->bufferSize;
		std::streamsize  readSize;
		int i = 0;
		while (i < bufferCount) {
			
			if (i == bufferCount - 1 && remainder > 0) {
				readSize = remainder;
			}
			else {
				readSize = this->bufferSize;
			}
			
			inFile.seekg(i * this->bufferSize);
			inFile.read(this->bufferStart, readSize);
			std::streamsize bytesRead = inFile.gcount();
			this->parseInput(bytesRead);

			i++;
		}

		inFile.close();

		//Delete the buffer after parsing complete
		delete[] this->bufferStart;

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

void LexicalAnalyzer::parseInput(std::streamsize bytesread) {

	std::string acc = "";
	// To indicate whether or not were inside a tag 
	bool isInTag = false;
	int i = 0;

	while (i < bytesread) {

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



