CFLAGS     ?= -O2 -Wall -Wextra -Werror
INCLUDE_AL  = $(shell pkg-config --cflags assemblyline)
INCLUDES    = -I. -I./src/lib/ -I./src/include $(INCLUDE_AL)

SRCS        = $(wildcard ./src/lib/*.c)
TEST_SRCS   = $(wildcard ./test/test_*.c)
TESTS       = $(TEST_SRCS:.c=.test)

LIB_AL      = $(shell pkg-config --libs assemblyline)
LIB_MS      = -L. -lmeasuresuite 

C_COV_DIR   = coverage-c


.PHONY: all check test report clean deepclean install-uiCA

.PRECIOUS: libmeasuresuite.a libmeasuresuite.so

all: libmeasuresuite.so libmeasuresuite.a
check: test report

test: CFLAGS=-g -Wextra -fprofile-arcs -ftest-coverage
test: test/liball_fiat.so test/liball_lib.so $(TESTS) Makefile 

report:
	@mkdir -p $(C_COV_DIR)
	@lcov --capture --output-file $(C_COV_DIR)/app.info --directory ./src 
	@lcov_cobertura $(C_COV_DIR)/app.info -o $(C_COV_DIR)/coverage.xml
	@genhtml -o $(C_COV_DIR) $(C_COV_DIR)/app.info

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(<) $(INCLUDES) -c -o $(@)  

libmeasuresuite.a: $(SRCS:c=o)
	$(AR) rcs $(@) $(^)

libmeasuresuite.so: $(SRCS:c=o)
	$(CC) $(CFLAGS) $(^) $(LIB_AL) -lm -ldl -shared -fPIC -fpie -o $(@)

test/liball_%.so: test/all_%.c
	$(CC) $(CFLAGS) $(<) -shared -fPIC -fpie -o $(@)


test/%.test:test/%.c Makefile test/helper.o libmeasuresuite.so
	@$(CC) $(CFLAGS) $(<) $(INCLUDES) $(LIB_AL) $(LIB_MS) test/helper.o -o $(@)
	@./test/wrapper.sh $(@)

clean:
	rm -rf build dist coverage $(C_COV_DIR) test/.deps 
	find . -type f -not -path "./uiCA/*" \( -name "*.gcda" -o -name "*.gcno" -o -name "*.o" -o -name "*.so" -o -name "*.html" \) -delete
	rm -f $(TESTS)

deepclean: clean
	rm -rf package-lock.json node_modules libmeasuresuite.a libmeasuresuite.so

install-uiCA: uiCA/setup.sh
	git apply uiCA.patch
	cd uiCA && (test -d instrData || ./setup.sh)

uiCA/setup.sh:
	git submodule update --init

