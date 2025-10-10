#include "LexicalAnalyzer.h"



LexicalAnalyzer::LexicalAnalyzer() = default;

void LexicalAnalyzer::loadInFile(std::string filePath)
{
	inFile.open(filePath, std::ios::in | std::ios::binary | std::ios::ate);


	// TODO : Add error handling
	if (inFile.is_open()) {
		fileSize = inFile.tellg();
		inFile.seekg(0, std::ios::beg);
		buffer = std::vector<char>(fileSize);
		if (inFile.read(buffer.data(), fileSize)) this->bufferStart = nullptr;
		bufferStart = &buffer;
		parseInput();
		inFile.close();
	}




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
	stringBuffer = new std::vector<char>();
	char* stringArray = new char[fileSize];
	char* stringStart = stringArray;
	char* stringEnd = stringStart;
	bool catchElement = false;
	bool catchAttribute = false;
	int arrIdx = 0;


	// To indicate whether or not were inside a tag 
	bool isInTag = false;
	int i = 0;

	while (i < fileSize) {
		char p = (*bufferStart)[i];

		std::string_view stringView(bufferStart->data() + i, 1);
		if (isalpha(p) == 0 && p != ' ') { // Character but not a space

			if (stringStart != stringEnd) {
				// We consume the word
				this->tokens.push_back(Token(TokenType::TEXT, std::string_view(stringStart, stringEnd - stringStart)));
				if (catchElement) {
					tokenStack.push(tokens.back());
					catchElement = false;
					catchAttribute = true;
					
				}

				if (catchAttribute) {
					
					std::cout << "This element should be a child attribute to " << tokens.back().value;
					tokenStack.push(tokens.back());
					std::cout << " // " << tokens.back().value << "\n";
				}
				stringStart = stringEnd;

			}

			switch (p)
			{
			default:
				break;
			case '<':
				this->tokens.emplace_back(Token(TokenType::OPENTAG, stringView));
				isInTag = true;
				catchElement = true;
				break;
			case '>':
				this->tokens.emplace_back(Token(TokenType::CLOSETAG, stringView));
				isInTag = false;
				break;
			case '/':
				this->tokens.emplace_back(Token(TokenType::SLASH, stringView));

				break;
			case '=':
				this->tokens.emplace_back(Token(TokenType::EQUALS, stringView));

				break;
			case '"':
				this->tokens.emplace_back(Token(TokenType::QUOTE, stringView));

				break;
			}
		}
		else if (p == ' ' && isInTag) { // Space but should be parsed 
			if (stringStart != stringEnd) {
				this->tokens.push_back(Token(TokenType::TEXT, std::string_view(stringStart, stringEnd - stringStart)));
				if (catchElement) {
					tokenStack.push(tokens.back());
				}
				stringStart = stringEnd;
			}

		}
		else {
			//it's an alphabet
			stringArray[arrIdx] = p;
			arrIdx++;
			stringEnd = stringArray + arrIdx;

		}




		i++;
	}
	//Verify last token 
	if (stringStart != stringEnd) {
		this->tokens.push_back(Token(TokenType::TEXT, std::string_view(stringStart, stringEnd - stringStart)));
		stringStart = stringEnd;
	}




}



