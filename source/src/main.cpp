// svgMotion.cpp : Defines the entry point for the application.
//

#include "svgMotion.h"
#include "core\utility\dataStructures\Tree.h"
#include "core\utility\DomParser.h"
#include "core\utility\LexicalAnalyzer.h"


int main()
{
	std::string file = "<svg><ellipse></ellipse></svg>";
	LexicalAnalyzer analyzer = LexicalAnalyzer(file);
	analyzer.parseInput(file);
	for (auto child : (*analyzer.getTokens())) {
		std::cout << child.value << std::endl;

	}
	
	
	return 0;
}
