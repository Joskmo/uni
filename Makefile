compile=g++ -Wall -Werror -Wextra
build=./bins

all: 17

17: 17_bin
	bins/17_bin
	rm bins/17_bin

17_bin: 17.cpp
	$(compile) 17.cpp -o bins/17_bin

630a: 630a.cpp
	$(compile) 630a.cpp -o $(build)/630a

clear:
	find ./bins -type f ! -name 'folder_for_bins.txt' -exec rm -f {} +

run: 630a
	$(build)/630a rand

test: bin
	bins/bin
	rm bins/bin

bin: test.cpp
	g++ test.cpp -o bins/bin

rebuild: clear all

clang:
	clang-format -i *.cpp 