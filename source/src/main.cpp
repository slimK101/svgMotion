// svgMotion.cpp : Defines the entry point for the application.
//

#include "svgMotion.h"
#include "core\utility\dataStructures\Tree.h"
#include "core\utility\DomParser.h"
#include "core\utility\LexicalAnalyzer.h"
#include <chrono>







int main()
{

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
	
	LexicalAnalyzer analyzer = LexicalAnalyzer();
	analyzer.loadInFile("C:\\Users\\slima\\source\\repos\\svgMotion\\source\\src\\core\\test.svg");

	for (auto token : analyzer.tokens) {
		std::cout << token.value << "\n";
	}
	
  
    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    
    std::cout << "Execution Time : " << ms_double.count() << "ms\n";
	return 0;
}
