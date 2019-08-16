#pragma once

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
	template<typename... Args> void loge(const char* tag, Args&&... args) { auto str = fmt::format(std::forward<Args>(args)...); const char* cstr = str.data(); ESP_LOGE(tag, "%s", cstr); }
	template<typename... Args> void logw(const char* tag, Args&&... args) { auto str = fmt::format(std::forward<Args>(args)...); const char* cstr = str.data(); ESP_LOGW(tag, "%s", cstr); }
	template<typename... Args> void logi(const char* tag, Args&&... args) { auto str = fmt::format(std::forward<Args>(args)...); const char* cstr = str.data(); ESP_LOGI(tag, "%s", cstr); }
	template<typename... Args> void logd(const char* tag, Args&&... args) { auto str = fmt::format(std::forward<Args>(args)...); const char* cstr = str.data(); ESP_LOGD(tag, "%s", cstr); }
	template<typename... Args> void logv(const char* tag, Args&&... args) { auto str = fmt::format(std::forward<Args>(args)...); const char* cstr = str.data(); ESP_LOGV(tag, "%s", cstr); }
}
