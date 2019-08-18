#include "ble_server.h"
#include "application.h"


namespace OpKey {


BleServer::BleServer(Application& application)
	: tickConnection(application.GetTickSink().connect<&BleServer::OnTick>(*this))
{ }

void BleServer::OnTick() {
}


} // namespace OpKey
