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
		.define_method("addSymbol", &Builder::addSymbol)
		.define_method("addIf", &Builder::addIf)
		.define_method("setTreeSize", &Builder::setTreeSize)
		.define_method("exitFuncs", &Builder::exitFuncs)
		.define_method("returnTest", &Builder::returnTest)
		.define_method("returnTestTwo", &Builder::returnTestTwo)
		.define_method("returnCumVTs", &Builder::returnCumVTs);

	Rice::Data_Type<InfoFetcher> rb_cInfoFetcher =
		Rice::define_class<InfoFetcher>("InfoFetcher")
		.define_constructor(Rice::Constructor<InfoFetcher>())
		.define_method("um", &InfoFetcher::um);
		// .define_method("programVT", &analysis::InfoFetcher::programVT);

	Rice::Data_Type<analysis::TimeMarker> rb_cTimeMarker =
		Rice::define_class<analysis::TimeMarker>("TimeMarker")
		.define_constructor(Rice::Constructor<analysis::TimeMarker>());

	Rice::Data_Type<analysis::Planner> rb_cPlanner =
		Rice::define_class<analysis::Planner>("Planner")
		.define_constructor(Rice::Constructor<analysis::Planner>())
		.define_method("setUp", &analysis::Planner::setUp)
		.define_method("printDetails", &analysis::Planner::printDetails);
}