## Copyright 2023 University of Adelaide

## Licensed under the Apache License, Version 2.0 (the "License");
## you may not use this file except in compliance with the License.
## You may obtain a copy of the License at

##    http://www.apache.org/licenses/LICENSE-2.0

## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.

TEST_DATA   = $(addprefix ./add_two_numbers., so bin o) liball.so

.PHONY: _all 

_all: $(TEST_DATA)

%.o: %.asm
	nasm -felf64 $(<) -o $(@)

%.bin: %.o
	objcopy ${<} --dump-section .text=${@}
	# alternatively, using the asm file and AL: asmline $(<) -P $(@)

%.so: %.o
	$(CC) -shared -fPIC -fpie $(<) -o $(@)

lib%.so: %.c
	$(CC) -shared -fPIC -fpie $(<) -o $(@)

clean:
	rm -rf $(TEST_DATA)
