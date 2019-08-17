set(COMPONENT_SRCS
	main.cpp
	application.cpp
	profiler.cpp
	adc_controller.cpp
	spi_host.cpp
	spi_device.cpp
	)

set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_REQUIRES esp_adc_cal cpp_utils)

register_component()

target_compile_features(${COMPONENT_LIB} PUBLIC cxx_std_17)
target_compile_options(${COMPONENT_LIB} PRIVATE ${PEDANTIC_COMPILE_FLAGS})
target_compile_options(${COMPONENT_LIB} PRIVATE -fdiagnostics-color=always)
