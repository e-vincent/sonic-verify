#include "main.h"

int main(void) { }

void Init_verify()
{
	Rice::Data_Type<Builder> rb_cBuilder = 
		Rice::define_class<Builder>("Builder")
		.define_constructor(Rice::Constructor<Builder>())
		.define_method("makeRoot", &Builder::makeRoot)
		.define_method("addNode", &Builder::addNode)
		.define_method("addValue", &Builder::addValue)
		.define_method("addNumber", &Builder::addNumber)
		.define_method("setTreeSize", &Builder::setTreeSize);

	Rice::Data_Type<analysis::TimeMarker> rb_cTimeMarker =
		Rice::define_class<analysis::TimeMarker>("TimeMarker")
		.define_constructor(Rice::Constructor<analysis::TimeMarker>());
}