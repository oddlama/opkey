#include "packet.h"
#include "calibration.h"
#include "application.h"


namespace opkey {


size_t PacketSuccess::OnPacketRecv(Application& application, PacketBuffer& responseBuf) const {
	// No response for success
	return 0;
}


bool PacketGenericRequest::Verify(Application& application) const {
	if (static_cast<uint8_t>(request) >= static_cast<uint8_t>(GenericRequest::_EnumMax)) {
		esp::loge("Invalid packet PacketGenericRequest with request={}", static_cast<uint8_t>(request));
		return false;
	}

	return true;
}

size_t PacketGenericRequest::OnPacketRecv(Application& application, PacketBuffer& responseBuf) const {
	switch (request) {
		case GenericRequest::VersionInfo:
			return PacketVersionInfo{}.Flatten(responseBuf);

		case GenericRequest::PrintCalibrationInfo:
			calibration::Print();
			return PacketSuccess{}.Flatten(responseBuf);

		default:
			return PacketGenericError{GenericError::InvalidGenericRequest}.Flatten(responseBuf);
	}
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
	application.SetNextMode(newMode);
	return PacketSuccess{}.Flatten(responseBuf);
}


} // namespace opkey
