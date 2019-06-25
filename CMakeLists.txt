# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

set(SANITIZE_FLAGS -fsanitize=address -fsanitize=undefined)
set(PEDANTIC_COMPILE_FLAGS -Wall -Wextra -Weffc++ -pedantic
	-Wold-style-cast -Wundef -Wredundant-decls -Wwrite-strings
	-Wpointer-arith -Wcast-qual -Wformat=2 -Wmissing-include-dirs
	-Wcast-align -Wctor-dtor-privacy -Wdisabled-optimization -Winvalid-pch
	-Woverloaded-virtual -Wnon-virtual-dtor)
if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.6)
	set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS} -Wnoexcept)
endif()
if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.0)
	set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS} -Wdouble-promotion
		-Wtrampolines -Wzero-as-null-pointer-constant -Wuseless-cast
		-Wvector-operation-performance -Wsized-deallocation)
endif()
if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6.0)
	set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS} -Wshift-overflow=2
		-Wnull-dereference -Wduplicated-cond)
endif()

set(WERROR_FLAG -Werror)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(piano-controller)
