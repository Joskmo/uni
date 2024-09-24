compile=g++ -Wall -Werror -Wextra
build=./bins

all: 630a

630a: 630a.cpp
	$(compile) 630a.cpp -o $(build)/630a

eva: 674.cpp
	$(compile) 674.cpp -o $(build)/674

clear:
	rm -rf ./bins/* *.a

rebuild: clear all

clang: 
	clang-format -i *.cpp 