FLAGS = gcc -Wall -Werror -Wextra -std=c11
TARGET = s21_matrix.a

# подбирает флаги для check в зависимости от системы (мак или линукс)
OS = $(shell uname -s)
ifeq ($(OS), Darwin)
CHECK_FLAGS = -lcheck
else ifeq ($(OS), Linux)
CHECK_FLAGS = -lcheck -lsubunit -lpthread -lrt
endif

all: clean $(TARGET) test gcov_report

$(TARGET):
	${FLAGS} -c -g s21_*.c
	ar rcs $(TARGET) s21_*.o
	ranlib $(TARGET)

clean:
	rm -rf *.o *.a *.gch *.gcno *.gcda report/ s21_test.info *.dSYM/ *.out *.log

rebuild: clean $(TARGET)

test: rebuild $(TARGET)
	$(FLAGS) -g --coverage tests.c $(TARGET) -o run_tests.out $(CHECK_FLAGS) -lm
	./run_tests.out

gcov_report:
	gcc tests.c s21_*.c -o gcov_test --coverage $(CHECK_FLAGS) -lm
	./gcov_test
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report/ s21_test.info
	open ./report/index.html
	rm -rf gcov_test

style:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c
	clang-format -n *.h
	rm -rf .clang-format

check:
	gcc -g s21*.c test.c -o test

valgrind: test
	valgrind --show-reachable=no --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --log-file=valgrind.log  ./run_tests.out

leaks: test
	leaks -atExit -- ./run_tests.o > leak_report.txt

man_test: ${TARGET}
	gcc -g man.c s21_matrix.a -o man.out
	valgrind --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --log-file=valgrind.log ./man.out
	rm -rf *.o *.a *.gch *.gcno *.gcda report/ s21_test.info *.dSYM/ *.out