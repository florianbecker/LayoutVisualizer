#!/usr/bin/env python3
#
# Copyright (c) 2023 Florian Becker <fb@vxapps.com> (VX APPS).
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

# Imports
import os
import sys

# Workflow
# 1. Find all .html files in $OUTPUT
# 2. Find all external links, remove the .html suffix
# 3. Open all external links in new browser window

folder = sys.argv[1] + "/html"

# Fix all .html files
for file in os.listdir(folder):
  if file.endswith('.html'):
    f = open(os.path.join(folder, file), 'r', errors='ignore')
    filedata = f.read()
    f.close()

    # find: 'href="https://' than find '.html"' and replace with '" target="_blank"'
    pos = len(filedata)
    while True:
      pos = filedata.rfind('href="https://', 0, pos)
      if pos == -1:
        break

      replace = filedata.find('.html"', pos)
      if replace == -1:
        continue

      # except sqlite functions
      if 'sqlite' in filedata[pos:replace]:
        filedata = filedata[:replace+6] + ' target="_blank"' + filedata[replace+6:]
        continue

      filedata = filedata[:replace] + '" target="_blank"' + filedata[replace+6:]

    f = open(os.path.join(folder, file),'w')
    f.write(filedata)
    f.close()

# Fix all .js files
for file in os.listdir(folder):
  if file.endswith('.js'):
    f = open(os.path.join(folder, file), 'r', errors='ignore')
    filedata = f.read()
    f.close()

    # find: 'href="https://' than find '.html"' and replace with '" target="_blank"'
    pos = len(filedata)
    while True:
      pos = filedata.rfind('"https://', 0, pos)
      if pos == -1:
        break

      replace = filedata.find('.html', pos + 1)
      if replace == -1:
        continue

      # except sqlite functions
      if 'sqlite' in filedata[pos:replace]:
        continue

      filedata = filedata[:replace] + '"' + filedata[replace + 6]

    f = open(os.path.join(folder, file),'w')
    f.write(filedata)
    f.close()
