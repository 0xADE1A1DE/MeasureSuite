CFLAGS    = -Wall -Wextra -fprofile-arcs -ftest-coverage
INCLUDES  = -I. -I./src/lib/ -I./src/include $(shell pkg-config --cflags assemblyline)

SRCS      = $(wildcard ./src/lib/*.c)
TEST_SRCS = $(wildcard ./test/test_*.c)
TESTS     = $(TEST_SRCS:.c=.test)

LIB_AL    = $(shell pkg-config --libs assemblyline)
LIB_MS    = -L. -lmeasuresuite 

C_COV_DIR=coverage-c


.PHONY: all check test report clean deepclean install-uiCA

.PRECIOUS: libmeasuresuite.so

all: libmeasuresuite.so

check: test report

test: test/liball_fiat.so test/liball_lib.so $(TESTS) Makefile 

report:
	@mkdir -p $(C_COV_DIR)
	@lcov --capture --output-file $(C_COV_DIR)/app.info --directory ./src 
	@lcov_cobertura $(C_COV_DIR)/app.info -o $(C_COV_DIR)/coverage.xml

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(<) $(INCLUDES) -c -o $(@)  

libmeasuresuite.so: $(SRCS:c=o)
	$(CC) $(CFLAGS) $(^) $(LIB_AL) -lm -ldl -shared -fPIC -fpie -o $(@)

test/liball_%.so: test/all_%.c
	$(CC) $(CFLAGS) $(<) -shared -fPIC -fpie -o $(@)


test/%.test:test/%.c Makefile test/helper.o libmeasuresuite.so
	@$(CC) $(CFLAGS) $(<) $(INCLUDES) $(LIB_AL) $(LIB_MS) test/helper.o -o $(@)
	@./test/wrapper.sh $(@)

clean:
	rm -rf build dist coverage $(C_COV_DIR) test/.deps 
	find . -type f \( -name "*.gcda" -o -name "*.gcno" -o -name "*.o" -o -name "*.so" -o -name "*.html" \) -exec rm {} \;
	rm -f $(TESTS)


deepclean: clean
	rm -rf package-lock.json node_modules

install-uiCA: uiCA/setup.sh
	cd uiCA && (test -d instrData || ./setup.sh)

uiCA/setup.sh:
	git submodule update --init
