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

project(LayoutVisualizer)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(${PROJECT_NAME}
  ../.github/workflows/linux.yml
  ../.github/workflows/macos.yml
  ../.github/workflows/windows.yml
  ../README.md
  LayoutVisualizer.cpp
  LayoutVisualizer.h
)

add_library(Layout::Visualizer ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  Qt${QT_VERSION_MAJOR}::Widgets
)

add_custom_target(${PROJECT_NAME}_documentation
  SOURCES
  ../docs/cppreference-doxygen-web.tag.xml
  ../docs/Doxyfile.in
  ../docs/footer.html
  ../docs/header.html
  ../docs/magic_enum-doxygen-web.tag.xml
  ../docs/post_doxygen.py
  ../.clang-format
  ../CODE_OF_CONDUCT.md
  ../LICENSE
  ../README.md
)

add_custom_target(${PROJECT_NAME}_workflows
  SOURCES
  ../.github/workflows/linux-codeql.yml
  ../.github/workflows/linux.yml
  ../.github/workflows/macos-codeql.yml
  ../.github/workflows/macos.yml
  ../.github/workflows/windows-codeql.yml
  ../.github/workflows/windows.yml
)
