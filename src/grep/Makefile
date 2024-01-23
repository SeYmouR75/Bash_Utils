CC = gcc
CFLAGS = -D_POSIX_C_SOURCE=200809L -Wall -Werror -Wextra

GREP_SRCS = grep.c

GREP_OBJS = $(GREP_SRCS:.c=.o)

GREP_EXEC = s21_grep

all: s21_grep

s21_grep: $(GREP_OBJS)
	$(CC) $(CFLAGS) $(GREP_OBJS) -o $(GREP_EXEC)
check:
	clang-format -style=Google -n *.c *.h
format:
	clang-format -style=Google -i *.c *.h
clean:
	rm *.o $(GREP_EXEC)
test:
	bash functional_test_s21_grep.sh
	python3 grep_tests.py o text1.txt
	python3 grep_tests.py o text1.txt text2.txt
	python3 grep_tests.py o text1.txt text2.txt text3.txt
	python3 grep_tests.py This text1.txt
	python3 grep_tests.py This text1.txt text2.txt
	python3 grep_tests.py This text1.txt text2.txt text3.txt
	python3 grep_tests.py -e is -e This text1.txt
	python3 grep_tests.py This text1.txt -i
	python3 grep_tests.py This text1.txt -v
	python3 grep_tests.py This text1.txt -c
	python3 grep_tests.py This text1.txt -l
	python3 grep_tests.py This text1.txt -n
	python3 grep_tests.py This text1.txt -h
	python3 grep_tests.py This text1.txt -s
	python3 grep_tests.py text1.txt -f patterns_file.txt
	python3 grep_tests.py This text1.txt -o
	python3 grep_tests.py -e is -e This text1.txt text2.txt
	python3 grep_tests.py This text1.txt text2.txt -i
	python3 grep_tests.py This text1.txt text2.txt -v
	python3 grep_tests.py This text1.txt text2.txt -c
	python3 grep_tests.py This text1.txt text2.txt -l
	python3 grep_tests.py This text1.txt text2.txt -n
	python3 grep_tests.py This text1.txt text2.txt -h
	python3 grep_tests.py This text1.txt text2.txt -s
	python3 grep_tests.py text1.txt text2.txt -f patterns_file.txt
	python3 grep_tests.py This text1.txt text2.txt -o
	python3 grep_tests.py -e is -e This text1.txt text2.txt text3.txt
	python3 grep_tests.py This text1.txt text2.txt text3.txt -i
	python3 grep_tests.py This text1.txt text2.txt text3.txt -v
	python3 grep_tests.py This text1.txt text2.txt text3.txt -c
	python3 grep_tests.py This text1.txt text2.txt text3.txt -l
	python3 grep_tests.py This text1.txt text2.txt text3.txt -n
	python3 grep_tests.py This text1.txt text2.txt text3.txt -h
	python3 grep_tests.py This text1.txt text2.txt text3.txt -s
	python3 grep_tests.py text1.txt text2.txt text3.txt -f patterns_file.txt
	python3 grep_tests.py This text1.txt text2.txt text3.txt -o
	python3 grep_tests.py -e is -e This text1.txt
	python3 grep_tests.py a text1.txt -i
	python3 grep_tests.py a text1.txt -v
	python3 grep_tests.py a text1.txt -c
	python3 grep_tests.py a text1.txt -l
	python3 grep_tests.py a text1.txt -n
	python3 grep_tests.py a text1.txt -h
	python3 grep_tests.py a text1.txt -s
	python3 grep_tests.py text1.txt -f patterns_file.txt
	python3 grep_tests.py a text1.txt -o
	python3 grep_tests.py -e is -e This text1.txt text2.txt
	python3 grep_tests.py a text1.txt text2.txt -i
	python3 grep_tests.py a text1.txt text2.txt -v
	python3 grep_tests.py a text1.txt text2.txt -c
	python3 grep_tests.py a text1.txt text2.txt -l
	python3 grep_tests.py a text1.txt text2.txt -n
	python3 grep_tests.py a text1.txt text2.txt -h
	python3 grep_tests.py a text1.txt text2.txt -s
	python3 grep_tests.py text1.txt text2.txt -f patterns_file.txt
	python3 grep_tests.py a text1.txt text2.txt -o
	python3 grep_tests.py -e is -e This text1.txt text2.txt text3.txt
	python3 grep_tests.py a text1.txt text2.txt text3.txt -i
	python3 grep_tests.py a text1.txt text2.txt text3.txt -v
	python3 grep_tests.py a text1.txt text2.txt text3.txt -c
	python3 grep_tests.py a text1.txt text2.txt text3.txt -l
	python3 grep_tests.py a text1.txt text2.txt text3.txt -n
	python3 grep_tests.py a text1.txt text2.txt text3.txt -h
	python3 grep_tests.py a text1.txt text2.txt text3.txt -s
	python3 grep_tests.py text1.txt text2.txt text3.txt -f patterns_file.txt
	python3 grep_tests.py a text1.txt text2.txt text3.txt -o
	