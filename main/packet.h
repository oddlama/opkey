#pragma once

#include "fmt.h"
#include "mode.h"

#include <array>

#include <host/ble_gatt.h>


namespace opkey {


using PacketBuffer alignas(16) = std::array<uint8_t, 64>;

enum class PacketType : uint8_t {
	Success,
	GenericError,
	GenericResponse,
	GenericRequest,
	SetOperationMode,
};

enum class GenericRequest : uint8_t {
	VersionInfo,
	PrintCalibrationInfo,
	_EnumMax,
};

enum class GenericError : uint8_t {
	Unknown,
	InvalidGenericRequest,
	PacketDataInvalid,
	InvalidPacketSize,
	InvalidPacketType,
	_EnumMax,
};


class Application;

template<typename Derived, PacketType P>
class Packet {
public:
	size_t Flatten(PacketBuffer& buf) const noexcept {
		const auto* begin = reinterpret_cast<const uint8_t*>(this);
		const auto* end = begin + sizeof(Derived);

		std::copy(begin, end, buf.data());
		return sizeof(Derived);
	}

public:
	PacketType type = P;
};


class PacketSuccess
	: public Packet<PacketSuccess, PacketType::Success>
{
public:
	bool Verify(Application& application) const { return true; }
	size_t OnPacketRecv(Application& application, PacketBuffer& responseBuf) const;
};

class PacketGenericError
	: public Packet<PacketGenericError, PacketType::GenericError>
{
public:
	explicit PacketGenericError(GenericError error)
		: error(error)
	{ }

public:
	GenericError error;
};

class PacketGenericRequest
	: public Packet<PacketGenericRequest, PacketType::GenericRequest>
{
public:
	bool Verify(Application& application) const;
	size_t OnPacketRecv(Application& application, PacketBuffer& responseBuf) const;

public:
	GenericRequest request = GenericRequest::VersionInfo;
};

class PacketVersionInfo
	: public Packet<PacketVersionInfo, PacketType::GenericResponse>
{
public:
	struct {
		uint8_t major = 0;
		uint8_t minor = 0;
		uint8_t patch = 1;
	} version;
};

class PacketSetOperationMode
	: public Packet<PacketSetOperationMode, PacketType::SetOperationMode>
{
public:
	bool Verify(Application& application) const;
	size_t OnPacketRecv(Application& application, PacketBuffer& responseBuf) const;

public:
	Mode newMode = Mode::Idle;
};


template<typename TPacket>
inline size_t HandlePacketTyped(Application& application, PacketBuffer& buf, size_t len, PacketBuffer& responseBuf) {
	if (len != sizeof(TPacket)) {
		esp::loge("Received packet with invalid size {} (expected {})", len, sizeof(TPacket));
		return PacketGenericError{GenericError::InvalidPacketSize}.Flatten(responseBuf);
	}
	auto& packet = reinterpret_cast<TPacket&>(buf);
	if (not packet.Verify(application)) {
		return PacketGenericError{GenericError::PacketDataInvalid}.Flatten(responseBuf);
	}
	return packet.OnPacketRecv(application, responseBuf);
}

inline size_t HandlePacket(Application& application, PacketType type, PacketBuffer& buf, size_t len, PacketBuffer& responseBuf) {
	switch (type) {
		case PacketType::Success:          return HandlePacketTyped<PacketSuccess>(application, buf, len, responseBuf);
		case PacketType::GenericRequest:   return HandlePacketTyped<PacketGenericRequest>(application, buf, len, responseBuf);
		case PacketType::SetOperationMode: return HandlePacketTyped<PacketSetOperationMode>(application, buf, len, responseBuf);

		default:
			esp::loge("Received packet with invalid type 0x{:02x}", static_cast<uint8_t>(type));
			return PacketGenericError{GenericError::InvalidPacketType}.Flatten(responseBuf);
	}

	esp::loge("Error in HandlePacket() - Reached dead code! Aborting.");
	abort();
	return BLE_ATT_ERR_UNLIKELY;
}


} // namespace opkey
