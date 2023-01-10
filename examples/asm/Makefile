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

LIBDIR=../../lib/

.PHONY: example-ts-asm

all: example-c-asm example-ts-asm

LDLIBS     += $(shell pkg-config --libs assemblyline)
CPPFLAGS   += $(shell pkg-config --cflags assemblyline) -DUSE_ASSEMBLYLINE

libmeasuresuite.a:
	CPPFLAGS="$(CPPFLAGS)" LDLIBS="$(LDLIBS)" $(MAKE) -B -C $(LIBDIR) libmeasuresuite.a
	cp $(LIBDIR)/libmeasuresuite.a .
	

example-c-asm: add_two_numbers.c libmeasuresuite.a
	$(CC) $(^) $(LDLIBS) $(CPPFLAGS) -I $(LIBDIR)/src/include -o  ${@}
	./${@} | $(shell which jq 2>/dev/null || echo "cat")
	rm -f libmeasuresuite.a ${@}

example-ts-asm: add_two_numbers.ts 
	npm i 
	npm test
	rm -f add_two_numbers.js
