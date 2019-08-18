#include "statistics.h"
#include "application.h"


namespace OpKey {


Statistics::Statistics(Application& application)
	: tickConnection(application.GetTickSink().connect<&Statistics::OnTick>(*this))
{ }


void Statistics::OnTick() {
}


} // namespace OpKey
