# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/wojtess/Documents/programs/esp-idf-v5.2.1/components/bootloader/subproject"
  "/home/wojtess/Documents/programing/esp32/powertrain/model2/build/bootloader"
  "/home/wojtess/Documents/programing/esp32/powertrain/model2/build/bootloader-prefix"
  "/home/wojtess/Documents/programing/esp32/powertrain/model2/build/bootloader-prefix/tmp"
  "/home/wojtess/Documents/programing/esp32/powertrain/model2/build/bootloader-prefix/src/bootloader-stamp"
  "/home/wojtess/Documents/programing/esp32/powertrain/model2/build/bootloader-prefix/src"
  "/home/wojtess/Documents/programing/esp32/powertrain/model2/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/wojtess/Documents/programing/esp32/powertrain/model2/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
