#include <iostream>

#include <ruby.h>

//#include "rice/Class.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"

//#include "lib/parser"

class Builder
{

public:
	Builder(){}

	void entry(Rice::Symbol thing)
	{
		std::cout << "Current Node: <" << thing << ">\n";	
	}

	void makeRoot(Rice::Symbol root, int index)
	{
		// has node marker 0
		std::cout << "Node Index::: " << index << "\n";
		std::cout << "Root is Symbol Type: <" << root << ">\n";
	}

	void addNode(Rice::Symbol nodeType, int index, int parent)
	{
		std::cout << "Node Index::: " << index << "\n";
		std::cout << "Given Node: <" << nodeType << "> has parent ";
		std::cout << parent << "\n";
	}

	void addValue(std::string val, int index, int parent)
	{
		std::cout << "Node Index::: " << index << "\n";
		std::cout << "Leaf Value: <" << val << "> has parent";
		std::cout << parent << "\n";
	}

};

extern "C"
void Init_builder()
{
	Rice::Data_Type<Builder> rb_cBuilder = 
		Rice::define_class<Builder>("Builder")
		.define_constructor(Rice::Constructor<Builder>())
		.define_method("entry", &Builder::entry)
		.define_method("makeRoot", &Builder::makeRoot)
		.define_method("addNode", &Builder::addNode)
		.define_method("addValue", &Builder::addValue);
}

