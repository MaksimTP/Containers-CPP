CXX = g++ -std=c++17

all: clean test

test: clean
	$(CXX) TEST/*.cc -o TEST/testing -lgtest -pthread
	./TEST/testing

clang-check:
	cp ../materials/linters/.clang-format .
	clang-format -n Set/*.h Multiset/*.h Array/*.h List/*.h Queue/*.h Vector/*.h Stack/*.h Map/*.h TEST/*.cc
	rm ./.clang-format

clang-formatting:
	cp ../materials/linters/.clang-format .
	clang-format -i Set/*.h Multiset/*.h Array/*.h List/*.h Queue/*.h Vector/*.h Stack/*.h Map/*.h TEST/*.cc
	rm ./.clang-format

gcov_report: clean
	$(CXX) TEST/*.cc -o TEST/testing -lgtest -pthread --coverage
	./TEST/testing
	lcov -d ./ --capture --output-file s21_container.info --ignore-errors mismatch --ignore-errors inconsistent
	genhtml s21_container.info --output-directory report
	open report/index.html

clean:
	rm -rf TEST/testing TEST/*.gcda TEST/*.gcno s21_container.info report

rebuild:
	clean | make
