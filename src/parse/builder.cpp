#include <iostream>
#include "rice/Class.hpp"


class Builder
{

public:
	void entry(int thing)
	{
		std::cout << thing << "\n";	
	}

};

extern "C"
void Init_builder()
{
	Rice::define_class("Builder")
		.define_method("entry", &Builder::entry);
}

