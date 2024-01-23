CC = gcc
CFLAGS = -D_POSIX_C_SOURCE=200809L -Wall -Werror -Wextra

CAT_SRCS = cat.c 

CAT_OBJS = $(CAT_SRCS:.c=.o)

CAT_EXEC = s21_cat

all: s21_cat

s21_cat: $(CAT_OBJS)
	$(CC) $(CFLAGS) $(CAT_OBJS) -o $(CAT_EXEC)
check:
	clang-format -style=Google -n *.c *.h
format:
	clang-format -style=Google -i *.c *.h
clean:
	rm *.o $(CAT_EXEC)
test:
	python3 cat_tests.py -b text1.txt text2.txt text3.txt ascii_symbols.txt
	python3 cat_tests.py -e text1.txt text2.txt text3.txt ascii_symbols.txt
	python3 cat_tests.py -n text1.txt text2.txt text3.txt ascii_symbols.txt
	python3 cat_tests.py -s text1.txt text2.txt text3.txt ascii_symbols.txt
	python3 cat_tests.py -t text1.txt text2.txt text3.txt ascii_symbols.txt
	python3 cat_tests.py -benstv text1.txt text2.txt text3.txt
	python3 cat_tests.py -benstvAET text1.txt text2.txt text3.txt
	python3 cat_tests.py -T text1.txt text2.txt text3.txt 
	python3 cat_tests.py -E text1.txt text2.txt text3.txt
	python3 cat_tests.py -v text1.txt text2.txt text3.txt
	python3 cat_tests.py --number text1.txt text2.txt text3.txt
	python3 cat_tests.py --number-nonblank text1.txt text2.txt text3.txt
	python3 cat_tests.py --squeeze-blank text1.txt text2.txt text3.txt
	python3 cat_tests.py text1.txt text2.txt text3.txt