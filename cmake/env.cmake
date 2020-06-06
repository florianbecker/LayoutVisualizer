#/*
# * Copyright (c) 2020 Florian Becker <fb@vxapps.com> (VX APPS).
# * All rights reserved.
# *
# * Redistribution and use in source and binary forms, with or without
# * modification, are permitted provided that the following conditions are met:
# *
# * 1. Redistributions of source code must retain the above copyright notice, this
# *    list of conditions and the following disclaimer.
# *
# * 2. Redistributions in binary form must reproduce the above copyright notice,
# *    this list of conditions and the following disclaimer in the documentation
# *    and/or other materials provided with the distribution.
# *
# * 3. Neither the name of the copyright holder nor the names of its
# *    contributors may be used to endorse or promote products derived from
# *    this software without specific prior written permission.
# *
# * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# */

#for debugging of build steps
#set(CMAKE_VERBOSE_MAKEFILE ON)

# Pathes
if(NOT LV_DEV)
  get_filename_component(LV_DEV "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
endif()

set(LV_CMAKE ${LV_DEV}/cmake)

# Force C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(USE_CLANG false)
if (CMAKE_CXX_COMPILER_ID MATCHES "[cC][lL][aA][nN][gG]") #Case insensitive match
  set(USE_CLANG true)
else()
  set(USE_CLANG false)
endif()

set(USE_GCC false)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(USE_GCC true)
else()
  set(USE_GCC false)
endif()

# Warning flags
if(USE_CLANG)
include(${LV_CMAKE}/clang_warnings.cmake)

set(LV_WARNING_FLAGS_SPACED "")
  foreach(LV_WARNING_FLAG ${LV_WARNING_FLAGS})
    set(LV_WARNING_FLAGS_SPACED "${LV_WARNING_FLAGS_SPACED} ${LV_WARNING_FLAG}")
endforeach()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LV_WARNING_FLAGS_SPACED}")
endif()

if(USE_GCC)
  include(${LV_CMAKE}/gcc_warnings.cmake)

set(LV_WARNING_FLAGS_SPACED "")
  foreach(LV_WARNING_FLAG ${LV_WARNING_FLAGS})
    set(LV_WARNING_FLAGS_SPACED "${LV_WARNING_FLAGS_SPACED} ${LV_WARNING_FLAG}")
endforeach()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LV_WARNING_FLAGS_SPACED}")
endif()

if(MSVC)
  # Force to always compile with W4
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  endif()
endif()

add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Project modules/variables
set(CMAKE_MODULE_PATH ${LV_CMAKE}/modules)

# Includes
include(${LV_CMAKE}/find_package.cmake)
