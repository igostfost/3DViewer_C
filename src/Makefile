CC=gcc
COMLFAGS=-Wall -Werror -Wextra -std=c11 -pedantic 
TFLAGS=-o testing -lcheck --coverage 

ifeq ($(shell uname), Linux)
	TFLAGS += -lm -lsubunit
endif

ifeq ($(shell uname), Darwin)
 TFLAGS += -fprofile-arcs -ftest-coverage
endif

all: test gcov_report dist install dvi start 

.PHONY: all clean build format test gcov_report

rebuild: clean clean_dist uninstall format all

build:
	$(CC) $(COMLFAGS) -c *.c
	ar -rc lib3D.a *.o


install:
	@echo "Installing 3DViewer..."
#	@cp -R ./3dViewer_1_school ./3dViewer_release
	@mkdir -p release
	@cd 3dViewer_1_school && qmake && make && make clean && rm -rf Makefile && mv 3dViewer_1_school.app ../release/3dViewer_1_school.app
	@cp -R release/3dViewer_1_school.app ~/Desktop/3dViewer_1_school.app
	@echo "┏=========================================┓"
	@echo "┃    The installation was successful.     ┃"
	@echo "┃    The project is located in the        ┃"
	@echo "┃    release folder and                   ┃"
	@echo "┃    on the desktop.                      ┃"
	@echo "┗=========================================┛"

	

uninstall:
	@echo "Removing 3DViewer..."
	@rm -rf ~/Desktop/3dViewer_1_school.app release
	@echo "┏=========================================┓"
	@echo "┃     Uninstall completed successfully    ┃"
	@echo "┗=========================================┛"

start:
	open ~/Desktop/3dViewer_1_school.app

dvi:
	open -o "Google Chrome" ./documentation/index.html
	

dist:
	@echo "┏=========================================┓"
	@echo "┃     Generating your dist ...            ┃"
	@echo "┗=========================================┛"
	@mkdir -p 3DViewer_v1.0/src/
	@cp -r Makefile transformations.c vert.c viewer.h test.check documentation 3dViewer_1_school 3DViewer_v1.0/src/
	@tar cvzf 3DViewer_v1.0.tgz 3DViewer_v1.0/
	@if [ ! -d ./3DViewer_dist ] ; then mkdir ./3DViewer_dist ; fi
	@mv 3DViewer_v1.0.tgz ./3DViewer_dist/
	@rm -rf 3DViewer_v1.0
	@echo "┏=============================================┓"
	@echo "┃     Your dist in 3DViewer_dist folder       ┃"
	@echo "┗=============================================┛"

clean_dist:
	@rm -rf 3DViewer_dist


tests: build
	checkmk clean_mode=1  test.check > testing.c
	$(CC) *.c lib3D.a $(TFLAGS)
	./testing

gcov_report:
	@echo "┏=========================================┓"
	@echo "┃     Generating your html report ...     ┃"
	@echo "┗=========================================┛"
	@gcov -b *.c 
	@lcov -d . -c -o coverage.info
	@genhtml -o html_report coverage.info
	@open html_report/index.html

clean:
	@-rm *.o testing.c testing *.a *.gcno *.gcda *.gcov *.info
	@-rm -rf html_report

clean_all:
	@make clean
	@make clean_dist
	make uninstall


format:
	@echo "┏=========================================┓"
	@echo "┃  Formatting your code for Google Style  ┃"
	@echo "┗=========================================┛"
	@find . -type f -name "*.c" -exec clang-format --style=Google -i {} \;
	@find . -type f -name "*.h" -exec clang-format --style=Google -i {} \;

format_check:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@find . -type f -name "*.c" -exec clang-format --style=Google -n {} \;
	@find . -type f -name "*.h" -exec clang-format --style=Google -n {} \;
	