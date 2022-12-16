## Copyright 2022 University of Adelaide

## Licensed under the Apache License, Version 2.0 (the "License");
## you may not use this file except in compliance with the License.
## You may obtain a copy of the License at

##    http://www.apache.org/licenses/LICENSE-2.0

## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.

# Files / Directories
SRCS        = $(shell find ./src/lib -type f -name '*.c')
UTEST_SRCS  = $(wildcard ./test/utest_*.c) # unit tests
ITEST_SRCS  = $(wildcard ./test/itest_*.c) # integration tests (i.e. using public api only )
TEST_SRCS   = $(UTEST_SRCS) $(ITEST_SRCS)
TESTS      ?= $(TEST_SRCS:.c=.test)
TEST_DATA   = $(addprefix test/test_data/add_two_numbers., so bin o)
C_COV_DIR   = coverage-c

CFLAGS     ?= -O2 -Wall -Wextra -Werror
CPPFLAGS   += -I. -I./src/lib/ -I./src/include
LDLIBS     += -ldl

# to exclude Assemblyline, use `make NO_AL=1`
ifndef NO_AL
CPPFLAGS   += $(shell pkg-config --cflags assemblyline) -DUSE_ASSEMBLYLINE
LDLIBS     += $(shell pkg-config --libs assemblyline)
endif


.PHONY: all check test report clean deepclean install-uiCA

.PRECIOUS: libmeasuresuite.a libmeasuresuite.so

all: libmeasuresuite.so libmeasuresuite.a
check: test report

test: cleantest
test: CFLAGS = -g -Wall -Wextra -Werror --coverage
test: LDLIBS+= -L. -lmeasuresuite
test: test/liball_fiat.so test/liball_lib.so $(TEST_DATA) $(TESTS) Makefile 
test/test_data/add_two_numbers.o: test/test_data/add_two_numbers.asm
	nasm -felf64 $(<) -o $(@)
test/test_data/add_two_numbers.bin: test/test_data/add_two_numbers.asm
	asmline $(<) -P $(@)
test/test_data/add_two_numbers.so: test/test_data/add_two_numbers.o
	$(CC) -shared -fPIC -fpie $(<) -o $(@)


report:
	@mkdir -p $(C_COV_DIR)
	@lcov --capture --output-file $(C_COV_DIR)/app.info --directory ./src 
	@lcov_cobertura $(C_COV_DIR)/app.info -o $(C_COV_DIR)/coverage.xml
	@genhtml -o $(C_COV_DIR) $(C_COV_DIR)/app.info

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(CPPFLAGS) -fPIC -c $(<) -o $(@)  

libmeasuresuite.a: $(SRCS:c=o)
	$(AR) rcs $(@) $(^)

libmeasuresuite.so: $(SRCS:c=o)
	$(CC) $(CFLAGS) $(^) $(LDLIBS) -shared -fpie -o $(@)

test/liball_%.so: test/all_%.c
	$(CC) $(CFLAGS) $(<) -shared -fPIC  -o $(@)


test/%.test: test/%.c Makefile test/helper.o libmeasuresuite.so
	@$(CC) $(CFLAGS) $(<) $(CPPFLAGS) test/helper.o $(LDLIBS) -o $(@)
	@./test/wrapper.sh $(@)
	@rm $(@)

clean: cleantest
	rm -rf build dist coverage $(C_COV_DIR) test/.deps 
	find . -type f -not -path "./uiCA/*" \( -name "*.gcda" -o -name "*.gcno" -o -name "*.a" -o -name "*.o" -o -name "*.so" -o -name "*.html" \) -delete

cleantest:
	rm -f $(TESTS)


deepclean: clean
	rm -rf package-lock.json node_modules libmeasuresuite.a libmeasuresuite.so

install-uiCA: uiCA/setup.sh
	cd uiCA && git apply ../uiCA.patch
	cd uiCA && (test -d instrData || ./setup.sh)

uiCA/setup.sh:
	git submodule update --init

