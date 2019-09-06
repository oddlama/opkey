#include "packet.h"
#include "application.h"


namespace opkey {


size_t PacketSuccess::OnPacketRecv(Application& application, PacketBuffer& responseBuf) const {
	// No response for success
	return 0;
}


size_t PacketRequestApplicationInfo::OnPacketRecv(Application& application, PacketBuffer& responseBuf) const {
	return PacketApplicationInfo{}.Flatten(responseBuf);
}


bool PacketSetOperationMode::Verify(Application& application) const {
	if (static_cast<uint8_t>(newMode) >= static_cast<uint8_t>(Mode::_EnumMax)) {
		esp::loge("Invalid packet PacketSetOperationMode with newMode={}", static_cast<uint8_t>(newMode));
		return false;
	}

	return true;
}

size_t PacketSetOperationMode::OnPacketRecv(Application& application, PacketBuffer& responseBuf) const {
	esp::logi("Received packet PacketSetOperationMode{{mode={}}}", static_cast<uint8_t>(newMode));
	application.SetMode(newMode);
	return PacketSuccess{}.Flatten(responseBuf);
}


} // namespace opkey
