# Original code from nkolban, licensed under Apache-2.0.
# (See https://github.com/nkolban/esp32-snippets)
#
# Modified by oddlama (oddlama@oddlama.org).
# All modifications are licensed under The MIT License,
# a copy of which can be found in the 'LICENSE' file at
# the project's root directory.

# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES
  "bt"
  "console"
  "fatfs"
  "json"
  "mdns"
  "nvs_flash"
)
set(COMPONENT_PRIV_REQUIRES )

file(GLOB COMPONENT_SRCS
  LIST_DIRECTORIES false
  "*.h"
  "*.cpp"
  "*.c"
  "*.S"
)
set(COMPONENT_ADD_INCLUDEDIRS ".")

register_component()

target_compile_features(${COMPONENT_LIB} PUBLIC cxx_std_17)
target_compile_options(${COMPONENT_LIB} PRIVATE -fdiagnostics-color=always)
