#include "main.h"

int main(void) { }

void Init_verify()
{
	Rice::Data_Type<Builder> rb_cBuilder = 
		Rice::define_class<Builder>("Builder")
		.define_constructor(Rice::Constructor<Builder>())
		.define_method("makeRoot", &Builder::makeRoot)
		.define_method("addNode", &Builder::addNode)
		.define_method("addValue", &Builder::addValue);

	Rice::Data_Type<TimeMarker> rb_cTimeMarker =
		Rice::define_class<TimeMarker>("TimeMarker")
		.define_constructor(Rice::Constructor<TimeMarker>());
}