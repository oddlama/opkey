#pragma once

#include "profiler.h"

#include <driver/spi_master.h>
#include <string>


namespace OpKey {


class SpiHost;

class SpiDevice {
	friend class SpiHost;

public:
	class AcquireGuard {
	public:
		AcquireGuard(SpiDevice& spiDevice);
		~AcquireGuard() noexcept;

		AcquireGuard(const AcquireGuard&) = delete;
		AcquireGuard(AcquireGuard&&) = delete;
		AcquireGuard& operator=(const AcquireGuard&) = delete;
		AcquireGuard& operator=(AcquireGuard&&) = delete;

	private:
		SpiDevice& spiDevice;
	};

	friend class AcquireGuard;

private:
	explicit SpiDevice(std::string name, spi_device_handle_t&& handle);

public:
	SpiDevice() noexcept = default;
	~SpiDevice() noexcept;

	SpiDevice(SpiDevice&& other) noexcept;
	SpiDevice& operator=(SpiDevice&& other) noexcept;

	SpiDevice(const SpiDevice&) = delete;
	SpiDevice& operator=(const SpiDevice&) = delete;

	const std::string& GetName() const noexcept { return name; }

	inline void Transfer(uint8_t* rxData, size_t rxLen, uint8_t* txData, size_t txLen) {
		spi_transaction_t transaction{};
		transaction.flags     = 0;
		transaction.length    = txLen * 8;
		transaction.rxlength  = rxLen * 8;
		transaction.tx_buffer = txData;
		transaction.rx_buffer = rxData;

		TransferPolling(transaction);
	}

	inline void Transfer(spi_transaction_t& transaction) {
		assert(handle != nullptr);

		if (auto rc = spi_device_transmit(handle, &transaction); rc != ESP_OK) {
			esp::loge("spi_device_transmit(SpiDevice{{name='{}'}}) returned {}", name, rc);
		}
	}

	inline void TransferPolling(uint8_t* rxData, size_t rxLen, uint8_t* txData, size_t txLen) {
		spi_transaction_t transaction{};
		transaction.flags     = 0;
		transaction.length    = txLen * 8;
		transaction.rxlength  = rxLen * 8;
		transaction.tx_buffer = txData;
		transaction.rx_buffer = rxData;

		TransferPolling(transaction);
	}

	inline void TransferPolling(spi_transaction_t& transaction) {
		assert(handle != nullptr);

		if (auto rc = spi_device_polling_transmit(handle, &transaction); rc != ESP_OK) {
			esp::loge("spi_device_polling_transmit(SpiDevice{{name='{}'}}) returned {}", name, rc);
		}
	}

	[[nodiscard]] AcquireGuard AcquireBus() {
		return AcquireGuard{*this};
	}

private:
	spi_device_handle_t handle = nullptr;
	std::string name{};
};


} // namespace OpKey
