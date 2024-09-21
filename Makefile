compile=g++ -Wall -Werror -Wextra
build=./bins

all: 630a

630a: 630a.cpp
	$(compile) 630a.cpp -o $(build)/630a

clear:
	rm -rf ./bins/* *.a

rebuild: clear all

clang: 
	clang-format -i *.cpp 