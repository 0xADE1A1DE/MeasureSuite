LIBDIR=../../lib/

# compile with assemblyline if possible
LIBS_AL = $(shell pkg-config --libs assemblyline >/dev/null && echo 1 || echo 0)
ifeq ($(LIBS_AL), 1)
LDLIBS     += $(shell pkg-config --libs assemblyline)
CPPFLAGS   += $(shell pkg-config --cflags assemblyline) -DUSE_ASSEMBLYLINE
endif

.PHONY: example-ts-elf

all: example-c-elf example-ts-elf

libmeasuresuite.a:
	CPPFLAGS="$(CPPFLAGS)" LDLIBS="$(LDLIBS)" $(MAKE) -B -C $(LIBDIR) libmeasuresuite.a
	cp $(LIBDIR)/libmeasuresuite.a .

add_two_numbers.o: add_two_numbers.asm
	nasm -felf64 ${<} -o ${@}

add_two_numbers.so: add_two_numbers.o
	$(CC) -shared -fpie ${<} -o ${@}

example-c-elf: add_two_numbers.c libmeasuresuite.a add_two_numbers.o add_two_numbers.so
	$(CC) $(<) $(LDLIBS) $(CPPFLAGS) libmeasuresuite.a -I $(LIBDIR)/src/include -o  ${@}
	./${@} | $(shell which jq 2>/dev/null || echo "cat")
	rm -f libmeasuresuite.a ${@}

example-ts-elf: add_two_numbers.ts add_two_numbers.o add_two_numbers.so
	npm i 
	npm test
	rm -f add_two_numbers.js

