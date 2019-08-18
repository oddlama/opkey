#include "visualizer.h"
#include "application.h"


namespace OpKey {


Visualizer::Visualizer(Application& application)
	: tickConnection(application.GetTickSink().connect<&Visualizer::OnTick>(*this))
{ }


void Visualizer::OnTick() {
}


} // namespace OpKey
