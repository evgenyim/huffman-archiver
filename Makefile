huffman: bin/main.o bin/huffman.o bin/huffman_archiver.o
	g++ bin/main.o bin/huffman.o bin/huffman_archiver.o  -o huffman
bin/main.o: src/main.cpp include/huffman.h include/huffman_archiver.h
	g++ -c src/main.cpp -I include -o bin/main.o
bin/huffman.o: src/huffman.cpp include/huffman.h
	g++ -c src/huffman.cpp -I include -o bin/huffman.o
bin/huffman_archiver.o: src/huffman_archiver.cpp include/huffman_archiver.h include/huffman.h
	g++ -c src/huffman_archiver.cpp -I include -o bin/huffman_archiver.o
test: bin/test.o bin/autotest.o bin/huffman_test.o bin/huffman.o
	g++ bin/test.o bin/autotest.o bin/huffman_test.o bin/huffman.o -o test
bin/test.o: include/huffman_test.h Test/test.cpp
	g++ -c Test/test.cpp -I include -o bin/test.o
bin/autotest.o: Test/autotest.cpp include/autotest.h
	g++ -c Test/autotest.cpp -I include -o bin/autotest.o
bin/huffman_test.o: include/huffman.h include/huffman_test.h Test/huffman_test.cpp
	g++ -c Test/huffman_test.cpp -I include -o bin/huffman_test.o

clean:
	rm bin/* huffman test
