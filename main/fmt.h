#pragma once

#include <esp_err.h>
#include <esp_log.h>

#define FMT_HEADER_ONLY
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wctor-dtor-privacy"
#include "fmt/format.h"
#pragma GCC diagnostic pop

using namespace fmt::literals;

namespace esp {
	template<typename... Args> void loge(Args&&... args) { auto str = fmt::format(std::forward<Args>(args)...); const char* cstr = str.data(); ESP_LOGE("OpKey", "%s", cstr); }
	template<typename... Args> void logw(Args&&... args) { auto str = fmt::format(std::forward<Args>(args)...); const char* cstr = str.data(); ESP_LOGW("OpKey", "%s", cstr); }
	template<typename... Args> void logi(Args&&... args) { auto str = fmt::format(std::forward<Args>(args)...); const char* cstr = str.data(); ESP_LOGI("OpKey", "%s", cstr); }
	template<typename... Args> void logd(Args&&... args) { auto str = fmt::format(std::forward<Args>(args)...); const char* cstr = str.data(); ESP_LOGD("OpKey", "%s", cstr); }
	template<typename... Args> void logv(Args&&... args) { auto str = fmt::format(std::forward<Args>(args)...); const char* cstr = str.data(); ESP_LOGV("OpKey", "%s", cstr); }

	template<typename... Args>
	inline void check(esp_err_t error, const char* functionMessage, Args&&... args) {
		if (error != ESP_OK) {
			auto msg = fmt::format(functionMessage, std::forward<Args>(args)...);
			esp::loge("{} returned {}", msg, esp_err_to_name(error));
			throw std::runtime_error("{} returned {}"_format(msg, esp_err_to_name(error)));
		}
	}
}
