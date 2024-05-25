CC=gcc
TEST=calc_test
CFLAGS=-Wall -Werror -Wextra -std=c11
PROJECTNAME = calculator
SRC = smartcalc.c test.c
GCOV=--coverage
OPEN_CMD=xdg-open
UNAME = $(shell uname -s)

ifeq ($(UNAME),Linux)
	LDFLAGS=-lcheck -lsubunit -lrt -lpthread
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS=-lcheck
	OPEN_CM=open
endif

all : clean install dvi

test : $(SRC)
	$(CC) $(CFLAGS) $(GCOV) $(SRC) $(LDFLAGS) -o $(TEST) -lm
	./$(TEST)

gcov_report: test
	lcov -o report.info -c -d .
	genhtml -o report report.info
	$(OPEN_CM) ./report/index.html	

install:
	@mkdir -p ../build
	@cd calculator && qmake6 && make && make clean && rm -rf Makefile && mv $(PROJECTNAME) ../../build/$(PROJECTNAME).app
	@cp -R ../build/$(PROJECTNAME).app ~/Desktop/$(PROJECTNAME).app
	@echo "Install completed"

uninstall:
	@rm -rf ~/Desktop/$(PROJECTNAME).app ../build
	@echo "Uninstall completed"

dvi:
	@open calculator.html

dist:
	@mkdir -p ../dist
	@cp -R ../build/$(PROJECTNAME).app ../dist
	@cp ../README_RUS.md ../dist && cp ../README.md ../dist
	@cd ../dist && tar cvzf $(PROJECTNAME).tgz *
	@cd ../dist && rm -rf $(PROJECTNAME).app README.md README_RUS.md
	@echo "The build was successfully archived"

format:
	clang-format -i -style=Google *.c *.h

# Проверка памяти для Linux
valgrind: clean test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./calc_test

clean: 
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./calc_test && rm -rf ./gcov_report
	-rm -rf ./report/

 # Перечисление целей, которые не являются названиями файлов
.PHONY: all style valgrind install unistall dvi dist test gcov_report clean
