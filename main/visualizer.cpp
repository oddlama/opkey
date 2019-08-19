#include "visualizer.h"
#include "application.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


namespace OpKey {


Visualizer::Visualizer(Application& application)
	: onTickConnection(application.GetOnTickSink().connect<&Visualizer::OnTick>(*this))
{ }


void Visualizer::OnTick() {
	OPKEY_PROFILE_FUNCTION();
	//static int64_t t = 0;
	//static int64_t c = 0;
	//Test();
	//auto now = esp_timer_get_time();
	//auto diff = now - t;
	//if (diff > 1000000) {
	//	fmt::print("Led fps: {}\n", c * 1000000.0 / diff);
	//	t = now;
	//	c = 0;
	//}
	//++c;
}


} // namespace OpKey
