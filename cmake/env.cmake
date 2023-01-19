#
# Copyright (c) 2020 Florian Becker <fb@vxapps.com> (VX APPS).
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

# for debugging of build steps
option(CMAKE_VERBOSE_MAKEFILE "Show the complete build commands" OFF)

# possibility to disable build steps
option(LAYOUTVISUALIZER_BUILD_EXAMPLES "Build examples for LayoutVisualizer" ON)
option(LAYOUTVISUALIZER_BUILD_TESTS "Build tests for LayoutVisualizer" ON)

# General
set(CMAKE_TLS_VERIFY TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")
cmake_host_system_information(RESULT CPU_COUNT QUERY NUMBER_OF_LOGICAL_CORES)

# CMake
set(CMAKE ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Force C23 or C17 if available
include(CheckCCompilerFlag)
if(CMAKE_C_COMPILER_ID STREQUAL "MSVC" OR CMAKE_C_SIMULATE_ID STREQUAL "MSVC")
  check_c_compiler_flag(/std:c23 HAVE_FLAG_STD_C23)
  check_c_compiler_flag(/std:c17 HAVE_FLAG_STD_C17)
  # Visual Studio 2019 will have clang-12, Visual Studio will have clang-15, but cmake do not know how to set the standard for that.
  if(CMAKE_C_COMPILER_ID MATCHES Clang AND CMAKE_C_COMPILER_VERSION VERSION_LESS 16.0)
    set(HAVE_FLAG_STD_C23 OFF)
  endif()
else()
  check_c_compiler_flag(-std=c23 HAVE_FLAG_STD_C23)
  check_c_compiler_flag(-std=c17 HAVE_FLAG_STD_C17)
endif()

if(HAVE_FLAG_STD_C23)
  set(CMAKE_C_STANDARD 23)
elseif(HAVE_FLAG_STD_C17)
  set(CMAKE_C_STANDARD 17)
else()
  set(CMAKE_C_STANDARD 11)
endif()
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Force C++23 or C++20 if available
include(CheckCXXCompilerFlag)
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" OR CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
  check_cxx_compiler_flag(/std:c++23 HAVE_FLAG_STD_CXX23)
  check_cxx_compiler_flag(/std:c++20 HAVE_FLAG_STD_CXX20)
  # Visual Studio 2019 will have clang-12, but cmake do not know how to set the standard for that.
  if(CMAKE_CXX_COMPILER_ID MATCHES Clang AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13.0)
    set(HAVE_FLAG_STD_CXX23 OFF)
  endif()
else()
  check_cxx_compiler_flag(-std=c++23 HAVE_FLAG_STD_CXX23)
  check_cxx_compiler_flag(-std=c++2b HAVE_FLAG_STD_CXX2B)
  check_cxx_compiler_flag(-std=c++20 HAVE_FLAG_STD_CXX20)
  check_cxx_compiler_flag(-std=c++2a HAVE_FLAG_STD_CXX2A)
endif()

# Clang-8 have some issues, that are not repairable
if(CMAKE_CXX_COMPILER_ID MATCHES Clang AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
  set(HAVE_FLAG_STD_CXX20 OFF)
  set(HAVE_FLAG_STD_CXX2A OFF)
endif()

if(HAVE_FLAG_STD_CXX23 OR HAVE_FLAG_STD_CXX2B)
  set(CMAKE_CXX_STANDARD 23)
elseif(HAVE_FLAG_STD_CXX20 OR HAVE_FLAG_STD_CXX2A)
  set(CMAKE_CXX_STANDARD 20)
else()
  set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# IPO/LTO
if(LAYOUTVISUALIZER_MASTER_PROJECT)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT HAVE_IPO_SUPPORT OUTPUT IPO_ERROR)
  if(HAVE_IPO_SUPPORT)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
  else()
    message(WARNING "IPO is not supported: ${IPO_ERROR}")
  endif()
endif()

# Compiler configuration
include(${CMAKE}/clang_warnings.cmake)
include(${CMAKE}/gcc_warnings.cmake)
include(${CMAKE}/msvc_warnings.cmake)

# Project modules/variables
set(CMAKE_MODULE_PATH ${CMAKE}/modules)

# Includes
if(LAYOUTVISUALIZER_MASTER_PROJECT)
  include(${CMAKE}/documentation.cmake)
endif()
include(${CMAKE}/find_package.cmake)
