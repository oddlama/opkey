#pragma once

#include <freertos/FreeRTOS.h>
#include <esp_system.h>

#include <algorithm>
#include <memory>

#include <cstdio>
#include <cstdlib>


namespace opkey {


enum class DmaChannel {
	None = 0,
	Dma1 = 1,
	Dma2 = 2,
};


template<typename T>
T* DmaMalloc(size_t size) {
	// DMA operates in units of 4 bytes, so extend the allocated range if necessary.
	if ((size & 0x3ul) != 0) {
		size = (size & ~0x3ul) + 0x4;
	}

	return static_cast<T*>(heap_caps_malloc(size, MALLOC_CAP_DMA));
}

template<typename T, typename... Args>
T* DmaNew(Args&&... args) {
	T* t = DmaMalloc<T>(sizeof(T));
	new(t) T(std::forward<Args>(args)...);
	return t;
}

struct DmaDelete {
	void operator()(void* ptr) {
		heap_caps_free(ptr);
	}
};

template<typename T>
using unique_ptr_dma = std::unique_ptr<T, DmaDelete>;

template<typename T, typename... Args>
unique_ptr_dma<T> make_unique_dma(Args&&... args) {
	return unique_ptr_dma<T>(DmaNew<T>(std::forward<Args>(args)...));
}


} // namespace opkey
