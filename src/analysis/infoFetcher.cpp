#include "analysis/infoFetcher.h"

// namespace analysis
// {

InfoFetcher::InfoFetcher() 
{
	std::cout << "raaaawr\n"; 
}

float InfoFetcher::programVT()
{
	return Builder::tree->trace()->totalVT();
}

void InfoFetcher::um()
{
	std::cout << "um" << "\n";
}

// } // namespace analysis