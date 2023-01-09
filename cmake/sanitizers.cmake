#
# Copyright (c) 2022 Florian Becker <fb@vxapps.com> (VX APPS).
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

include(CheckCXXCompilerFlag)

if(UNIX OR CMAKE_CXX_COMPILER_ID MATCHES "[cC][lL][aA][nN][gG]")
  set(CMAKE_REQUIRED_FLAGS -fsanitize=address)
  check_cxx_compiler_flag(-fsanitize=address HAVE_ASAN)

  set(CMAKE_REQUIRED_FLAGS "-fsanitize=cfi -flto")
  check_cxx_compiler_flag(-fsanitize=cfi HAVE_CFI)

  set(CMAKE_REQUIRED_FLAGS -fsanitize=fuzzer)
  check_cxx_compiler_flag(-fsanitize=fuzzer HAVE_FUZZER)

  set(CMAKE_REQUIRED_FLAGS -fsanitize=leak)
  check_cxx_compiler_flag(-fsanitize=leak HAVE_LSAN)

  set(CMAKE_REQUIRED_FLAGS -fsanitize=memory)
  check_cxx_compiler_flag(-fsanitize=memory HAVE_MSAN)

  set(CMAKE_REQUIRED_FLAGS -fsanitize=thread)
  check_cxx_compiler_flag(-fsanitize=thread HAVE_TSAN)

  set(CMAKE_REQUIRED_FLAGS -fsanitize=undefined)
  check_cxx_compiler_flag(-fsanitize=undefined HAVE_USAN)
else()
  set(CMAKE_REQUIRED_FLAGS /fsanitize=address)
  check_cxx_compiler_flag(/fsanitize=address HAVE_ASAN)

  set(CMAKE_REQUIRED_FLAGS /fsanitize=fuzzer)
  check_cxx_compiler_flag(/fsanitize=fuzzer HAVE_FUZZER)
endif()
  unset(CMAKE_REQUIRED_FLAGS)

if(HAVE_ASAN)
  option(SANITIZER_ADDRESS "Build with address sanitizer" ON)
  if(SANITIZER_ADDRESS)
    if(UNIX)
      set(SANITIZER_ADDRESS_FLAGS "-fsanitize=address -fno-omit-frame-pointer -fsanitize-address-use-after-scope -fno-optimize-sibling-calls")
    else()
      set(SANITIZER_ADDRESS_FLAGS /fsanitize=address)
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_ADDRESS_FLAGS}")
    set(EXTRA_CXX_FLAGS "${EXTRA_CXX_FLAGS} ${SANITIZER_ADDRESS_FLAGS}")
  endif()
endif()

if(HAVE_CFI)
  option(SANITIZER_CFI "Build with control flow integration" OFF)
  if(SANITIZER_CFI)
    set(SANITIZER_CFI_FLAGS -fsanitize=cfi)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_CFI_FLAGS}")
    set(EXTRA_CXX_FLAGS "${EXTRA_CXX_FLAGS} ${SANITIZER_CFI_FLAGS}")
  endif()
endif()

if(HAVE_FUZZER)
  option(SANITIZER_FUZZER "Build with fuzzer" ON)
  if(SANITIZER_FUZZER)
    if(UNIX)
      set(SANITIZER_FUZZER_FLAGS -fsanitize=fuzzer)
    else()
      set(SANITIZER_FUZZER_FLAGS /fsanitize=fuzzer)
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FUZZER_FLAGS}")
    set(EXTRA_CXX_FLAGS "${EXTRA_CXX_FLAGS} ${SANITIZER_FUZZER_FLAGS}")
  endif()
endif()

if(HAVE_LSAN)
  option(SANITIZER_LEAK "Build with leak sanitizer" OFF)
  if(SANITIZER_LEAK)
    set(SANITIZER_LEAK_FLAGS -fsanitize=leak)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_LEAK_FLAGS}")
    set(EXTRA_CXX_FLAGS "${EXTRA_CXX_FLAGS} ${SANITIZER_LEAK_FLAGS}")
  endif()
endif()

if(HAVE_MSAN)
  option(SANITIZER_MEMORY "Build with memory sanitizer" OFF)
  if(SANITIZER_MEMORY)
    set(SANITIZER_MEMORY_FLAGS "-fsanitize=memory -fsanitize-memory-track-origins -fno-optimize-sibling-calls")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_MEMORY_FLAGS}")
    set(EXTRA_CXX_FLAGS "${EXTRA_CXX_FLAGS} ${SANITIZER_MEMORY_FLAGS}")
  endif()
endif()

if(HAVE_TSAN)
  option(SANITIZER_THREAD "Build with thread sanitizer" OFF)
  if(SANITIZER_THREAD)
    set(SANITIZER_THREAD_FLAGS -fsanitize=thread)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_THREAD_FLAGS}")
    set(EXTRA_CXX_FLAGS "${EXTRA_CXX_FLAGS} ${SANITIZER_THREAD_FLAGS}")
  endif()
endif()

if(HAVE_USAN)
  option(SANITIZER_UNDEFINED "Build with undefined sanitizer" ON)
  if(SANITIZER_UNDEFINED)
    set(SANITIZER_UNDEFINED_FLAGS -fsanitize=undefined)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_UNDEFINED_FLAGS}")
    set(EXTRA_CXX_FLAGS "${EXTRA_CXX_FLAGS} ${SANITIZER_UNDEFINED_FLAGS}")
  endif()
endif()
