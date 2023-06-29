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

LDLIBS     += -ldl
# compile with assemblyline if possible
LIBS_AL = $(shell which pkg-config >/dev/null && pkg-config --exists assemblyline >/dev/null && echo 1 || echo 0)
ifeq ($(LIBS_AL), 1)
LDLIBS     += $(shell pkg-config --libs assemblyline)
CPPFLAGS   += $(shell pkg-config --cflags assemblyline) -DUSE_ASSEMBLYLINE
endif

## Enable debug with make DEBUG=1
DEBUG ?= 0
ifneq ($(DEBUG), 0)
CFLAGS += -g -DENABLE_DEBUG
endif

# use make -B DEBUG=1 CFLAGS='-g' for debug output and better debugging experience

.PHONY: all check clean 

.PRECIOUS: libmeasuresuite.so libmeasuresuite.a ms

all: lib/libmeasuresuite.so lib/libmeasuresuite.a ms

lib/libmeasuresuite.a lib/libmeasuresuite.so:
	$(MAKE) -C lib $(subst lib/,,$(@))

ms:  bin/arg_parse.c bin/ms.c lib/libmeasuresuite.a 
	$(CC) $(CFLAGS) -I./lib/src/include $(^) $(CPPFLAGS) $(LDLIBS) -o $(@)

publish: clean
	 tsc --emitDeclarationOnly -p ./ts/
	 npm run build
	 cp Readme.md ./ts/dist
	 @echo "If you've updated the versions (npm version minor), run 'npm publish' now"

clean:
	rm -rf ms \
		ts/coverage \
		ts/dist \
		build
	$(MAKE) -C lib $(@)

check: ms
	$(MAKE) -C lib test
	./ms  \
		-s add_two_numbers \
		./lib/test/test_data/add_two_numbers.asm \
		./lib/test/test_data/add_two_numbers.bin \
		./lib/test/test_data/add_two_numbers.so \
		./lib/test/test_data/add_two_numbers.o
