OUT_TEST			= matrix_test
LCOV 		= report/index.html
LIB 			= s21_matrix.a
FUNC_FILES 			= ./s21_*.c
OBJ					= s21_*.o
FUNC_TEST			= tests/test_s21_*.c
OBJ_TEST			= test_s21_*.o

UNAME_S := $(shell uname -s)

CC			= gcc
CFLAGS		= -c -std=c11 -Wall -Werror -Wextra
L_FLAGS		= -std=c11 -Wall -Werror -Wextra
COVER_FLAG  = --coverage
LIB_FLAGS 	= ar rcs

ifeq ($(UNAME_S), Linux)
	OS_SPECIFIC_FLAGS 				= -lcheck -lsubunit -lm
	OS_SPECIFIC_GCOV_REPORT 		= branch_coverage=1
	OS_SPECIFIC_GCOV_REPORT_HTML 	= genhtml_branch_coverage=1
else ifeq ($(UNAME_S), Darwin)
	OS_SPECIFIC_FLAGS 				= -lcheck
    OS_SPECIFIC_GCOV_REPORT 		= branch_coverage=1
    OS_SPECIFIC_GCOV_REPORT_HTML 	= branch_coverage=1
endif

ifeq ($(shell grep -i microsoft /proc/version),)
	OPEN_REPORT:= open
else
    OPEN_REPORT:= wslview
endif

all: s21_matrix.a

s21_matrix.a: build.o
	$(LIB_FLAGS) $(LIB) $(OBJ)
	rm -fr $(OBJ)

test: test_file
	./$(OUT_TEST)
	$(MAKE) gcov_report
	-rm -rf *.gc* *.info $(OUT_TEST) $(OBJ_TEST) $(OBJ) $(LIB)
	$(OPEN_REPORT) $(LCOV)

leaks_test: test_file
	leaks -atExit -- ./$(OUT_TEST)
	-rm -rf *.gc* *.info $(OUT_TEST) $(OBJ_TEST) $(OBJ) $(LIB)

valgrind_test: test_file
	valgrind --leak-check=yes ./$(OUT_TEST)
	-rm -rf *.gc* *.info $(OUT_TEST) $(OBJ_TEST) $(OBJ) $(LIB)

test_file: s21_matrix.a_for_test build_test.o
	$(CC) $(L_FLAGS) $(COVER_FLAG) $(OBJ_TEST) tests/tests_main.c -L. $(LIB) $(OS_SPECIFIC_FLAGS) -o $(OUT_TEST)

s21_matrix.a_for_test: build_object_for_test.o
	$(LIB_FLAGS) $(LIB) $(OBJ)
	rm -fr $(OBJ)

build.o:
	$(CC) $(CFLAGS) $(FUNC_FILES)

build_object_for_test.o:
	$(CC) $(CFLAGS) $(COVER_FLAG) $(FUNC_FILES)

build_test.o:
	$(CC) $(CFLAGS) $(FUNC_TEST)

gcov_report:
	LCOV -t "test" -o matrix.info -c -d . --rc $(OS_SPECIFIC_GCOV_REPORT)
	genhtml -o report matrix.info --rc $(OS_SPECIFIC_GCOV_REPORT_HTML)

build_o: $(FUNC_FILES)
	$(CC) $(CFLAGS) $(FUNC_FILES)

style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i $(FUNC_FILES) $(FUNC_TEST) tests/*.h tests/tests_main.c s21_matrix.h
	rm .clang-format

rebuild: clean all

clean:
	rm -rf $(OBJ) $(OUT_TEST) $(OBJ_TEST) $(LIB) $(OUT_TEST) *.gc* report/ *.info
