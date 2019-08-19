set(COMPONENT_SRCS
	main.cpp
	profiler.cpp
	spi_host.cpp
	spi_device.cpp
	adc_controller.cpp
	statistics.cpp
	visualizer.cpp
	ble_server.cpp
	application.cpp
	sensor_manager.cpp
	)

set(COMPONENT_ADD_INCLUDEDIRS ".")
#set(COMPONENT_REQUIRES nvs)

register_component()

target_compile_features(${COMPONENT_LIB} PUBLIC cxx_std_17)
target_compile_options(${COMPONENT_LIB} PRIVATE ${PEDANTIC_COMPILE_FLAGS})
target_compile_options(${COMPONENT_LIB} PRIVATE -fdiagnostics-color=always)
