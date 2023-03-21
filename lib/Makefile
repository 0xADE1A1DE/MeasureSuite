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

# Files / Directories
SRCS        = $(shell find ./src -type f -name '*.c')
UTEST_SRCS  = $(wildcard ./test/unit/*.c)
ITEST_SRCS  = $(wildcard ./test/integration/*.c) # (i.e. using public api only )
TEST_SRCS   = $(UTEST_SRCS) $(ITEST_SRCS)
TESTS      ?= $(TEST_SRCS:.c=.tst)
C_COV_DIR   = coverage

CFLAGS     ?= -O2 -Wall -Wextra -Werror -std=c17
CPPFLAGS   += -I./src/ -I./src/include
LDLIBS     += -ldl

# compile with assemblyline if possible (or use make LIBS_AL=0 to manually disable compilation with LIBS_AL)
LIBS_AL     ?= $(shell which pkg-config >/dev/null && pkg-config --exists assemblyline >/dev/null && echo 1 || echo 0)
ifeq ($(LIBS_AL), 1)
LDLIBS     += $(shell pkg-config --libs assemblyline)
CPPFLAGS   += $(shell pkg-config --cflags assemblyline) -DUSE_ASSEMBLYLINE
endif



.PHONY: all check test report clean deepclean install-uiCA

.PRECIOUS: libmeasuresuite.so libmeasuresuite.a

all: libmeasuresuite.so libmeasuresuite.a
check: test report

test: cleantest test_data
test: CFLAGS+= -g -Wall -Wextra -Werror --coverage 
test: LDLIBS+= -L. -lmeasuresuite
test: $(TESTS) Makefile

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

test/%.tst: test/%.c Makefile test/helper.o libmeasuresuite.so
	@$(CC) $(CFLAGS) -Wno-unused-const-variable -Wno-unused-function $(<) $(CPPFLAGS) test/helper.o $(LDLIBS) -I./test -o $(@)
	@./test/wrapper.sh $(@)
	@rm $(@)

clean: cleantest
	rm -rf $(C_COV_DIR)
	find . -type f -not -path "./uiCA/*" \( -name "*.gcda" -o -name "*.gcno" -o -name "*.a" -o -name "*.o" -o -name "*.so" -o -name "*.html" \) -delete

test_data:
	$(MAKE) -C ./test/test_data

cleantest:
	rm -f $(TESTS)


deepclean: clean
	rm -rf libmeasuresuite.a libmeasuresuite.so

install-uiCA: uiCA/setup.sh
	cd uiCA && git apply ../uiCA.patch
	cd uiCA && (test -d instrData || ./setup.sh)

uiCA/setup.sh:
	git submodule update --init

