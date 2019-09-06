#pragma once

#include "fmt.h"

#include <optional>

#include <nvs_flash.h>


namespace opkey::nvs {

inline constexpr const char* opkeyNamespace = "opkey";


class NvsStorage {
public:
	NvsStorage(const char* storageNamespace) {
		esp::check(nvs_open(storageNamespace, NVS_READWRITE, &handle), "nvs_open(\"opkey\", rw);");
	}

	~NvsStorage() noexcept {
		nvs_close(handle);
	}

	bool Erase(const char* key) {
		auto err = nvs_erase_key(handle, key);
		if (err == ESP_ERR_NVS_NOT_FOUND) {
			return false;
		}
		esp::check(err, "nvs_erase_key()");
		return true;
	}

	template<typename T>
	void Set(const char* key, const T& value) {
		esp::check(nvs_set_blob(handle, key, static_cast<const void*>(&value), sizeof(T)), "nvs_set_blob()");
	}

	template<typename T>
	bool Get(const char* key, T& value) const {
		size_t len = 0;
		auto err = nvs_get_blob(handle, key, nullptr, &len);
		if (err == ESP_ERR_NVS_NOT_FOUND) {
			return false;
		}
		esp::check(err, "nvs_get_blob()");

		if (len != sizeof(T)) {
			esp::logw("nvs_get_blob(\"{}\") stored size ({}) mismatches required size ({})", len, sizeof(T));
			return false;
		}

		esp::check(nvs_get_blob(handle, key, static_cast<void*>(&value), &len), "nvs_get_blob()");
		return true;
	}

	void Set(const char* key,   int8_t value) { esp::check( nvs_set_i8(handle, key, value),  "nvs_set_i8()"); }
	void Set(const char* key,  uint8_t value) { esp::check( nvs_set_u8(handle, key, value),  "nvs_set_u8()"); }
	void Set(const char* key,  int16_t value) { esp::check(nvs_set_i16(handle, key, value), "nvs_set_i16()"); }
	void Set(const char* key, uint16_t value) { esp::check(nvs_set_u16(handle, key, value), "nvs_set_u16()"); }
	void Set(const char* key,  int32_t value) { esp::check(nvs_set_i32(handle, key, value), "nvs_set_i32()"); }
	void Set(const char* key, uint32_t value) { esp::check(nvs_set_u32(handle, key, value), "nvs_set_u32()"); }
	void Set(const char* key,  int64_t value) { esp::check(nvs_set_i64(handle, key, value), "nvs_set_i64()"); }
	void Set(const char* key, uint64_t value) { esp::check(nvs_set_u64(handle, key, value), "nvs_set_u64()"); }

	bool Get(const char* key,   int8_t& value) const { auto err =  nvs_get_i8(handle, key, &value); if (err == ESP_ERR_NVS_NOT_FOUND) { return false; } esp::check(err,  "nvs_get_i8()"); }
	bool Get(const char* key,  uint8_t& value) const { auto err =  nvs_get_u8(handle, key, &value); if (err == ESP_ERR_NVS_NOT_FOUND) { return false; } esp::check(err,  "nvs_get_u8()"); }
	bool Get(const char* key,  int16_t& value) const { auto err = nvs_get_i16(handle, key, &value); if (err == ESP_ERR_NVS_NOT_FOUND) { return false; } esp::check(err, "nvs_get_i16()"); }
	bool Get(const char* key, uint16_t& value) const { auto err = nvs_get_u16(handle, key, &value); if (err == ESP_ERR_NVS_NOT_FOUND) { return false; } esp::check(err, "nvs_get_u16()"); }
	bool Get(const char* key,  int32_t& value) const { auto err = nvs_get_i32(handle, key, &value); if (err == ESP_ERR_NVS_NOT_FOUND) { return false; } esp::check(err, "nvs_get_i32()"); }
	bool Get(const char* key, uint32_t& value) const { auto err = nvs_get_u32(handle, key, &value); if (err == ESP_ERR_NVS_NOT_FOUND) { return false; } esp::check(err, "nvs_get_u32()"); }
	bool Get(const char* key,  int64_t& value) const { auto err = nvs_get_i64(handle, key, &value); if (err == ESP_ERR_NVS_NOT_FOUND) { return false; } esp::check(err, "nvs_get_i64()"); }
	bool Get(const char* key, uint64_t& value) const { auto err = nvs_get_u64(handle, key, &value); if (err == ESP_ERR_NVS_NOT_FOUND) { return false; } esp::check(err, "nvs_get_u64()"); }

private:
	nvs_handle_t handle{};
};


void Init();


inline NvsStorage Open() {
	return NvsStorage(opkeyNamespace);
}


} // namespace opkey::nvs
