#include "LexicalAnalyzer.h"



LexicalAnalyzer::LexicalAnalyzer(std::string input)
{
	LexicalAnalyzer::input = input;
}

void LexicalAnalyzer::parseInput(std::string input) {
	char currChar = input[0];
	std::string keyword = "";
	for (int i = 0; i < input.size(); i++) {
		currChar = input[i];
		if (currChar == '<') {
			int pos = i + 1;
			while (input[pos] != '>') {
				if (input[pos] != '/') {
					keyword +=input[pos];
					
				}
				pos++;
			}

			Token token(TokenType::OPENTAG, keyword);
			tokens.push_back(token);
			i = pos;
			keyword = "";

		}
	}
}


