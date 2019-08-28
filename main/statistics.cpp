#include "statistics.h"
#include "application.h"


namespace opkey {


Statistics::Statistics(Application& application)
	: onTickConnection(application.GetOnTickSink().connect<&Statistics::OnTick>(*this))
{ }


void Statistics::OnTick() {
	OPKEY_PROFILE_FUNCTION();
}


} // namespace opkey
