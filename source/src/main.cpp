// svgMotion.cpp : Defines the entry point for the application.
//

#include "svgMotion.h"
#include "core\utility\dataStructures\Tree.h"
#include "core\utility\DomParser.h"
#include "core\utility\LexicalAnalyzer.h"



int main()
{
	std::string file = "<svg id =\"hello\"><elipse>Hello World</e>>ipse></svg>";
	LexicalAnalyzer analyzer = LexicalAnalyzer();
	analyzer.initBuffer(file);
	analyzer.printBuffer();
	analyzer.parseInput();
	for (auto token : analyzer.tokens) {
		std::cout << token.value << "\n";
	}
	
	
	return 0;
}
