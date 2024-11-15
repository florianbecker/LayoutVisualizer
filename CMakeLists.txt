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

cmake_minimum_required(VERSION 3.18...3.28)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/policy.cmake)
update_policy()

# Determine if this is built as a subproject (using add_subdirectory)
# or if it is the master project.
if(NOT DEFINED LAYOUTVISUALIZER_MASTER_PROJECT)
  set(LAYOUTVISUALIZER_MASTER_PROJECT OFF)
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(LAYOUTVISUALIZER_MASTER_PROJECT ON)
  endif()
endif()

project(LayoutVisualizer VERSION 0.3 DESCRIPTION "Visualize Qt Layouts" HOMEPAGE_URL "https://vxapps.com" LANGUAGES C CXX)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/env.cmake)
include(${CMAKE}/checks.cmake)
if(LAYOUTVISUALIZER_MASTER_PROJECT AND CMAKE_BUILD_TYPE STREQUAL Debug)
  include(${CMAKE}/sanitizers.cmake)
endif()

# Fetch Content Dependencies
include(${CMAKE}/fetch/doxygen-awesome-css.cmake)

add_subdirectory(source)

if(LAYOUTVISUALIZER_MASTER_PROJECT)
  if(LAYOUTVISUALIZER_BUILD_EXAMPLES)
    add_subdirectory(examples)
  endif()
endif()
