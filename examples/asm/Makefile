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
