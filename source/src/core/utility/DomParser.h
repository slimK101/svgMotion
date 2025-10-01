#ifndef DOMPARSER_H
#define DOMPARSER_H


#include <iostream>
#include <memory>
#include "dataStructures\Tree.h"



Tree<std::string>* parseDom(std::string& filename);
	




#endif