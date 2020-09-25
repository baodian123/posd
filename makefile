.PHONY: dirs clean stat

CC=g++
CFLAG=-std=c++11 -Wfatal-errors
all: dirs bin/ut_all bin/ui_folder_tree

# bin/ut_all: test/ut_main.cpp obj/flattened_set_visitor.o test/ut_fs.h src/set.h src/integer.h src/element.h src/visitor.h src/flattened_set_visitor.h
# 	$(CC) $(CFLAG) -o $@ $< obj/flattened_set_visitor.o -lgtest -lpthread

bin/ut_all: test/ut_main.cpp obj/filesystem_builder.o test/ut_fs.h src/file.h src/folder.h src/iterator.h src/link.h src/null_iterator.h src/node.h src/visitor.h
	$(CC) $(CFLAG) -o $@ $< obj/filesystem_builder.o -lgtest -lpthread

obj/filesystem_builder.o: src/filesystem_builder.cpp src/filesystem_builder.h
	$(CC) $(CFLAG) -c $< -o $@

bin/ui_folder_tree: src/ui_folder_tree.cpp src/ui_folder_tree.h src/tree_frame.h
		g++ $< `wx-config --libs` `wx-config --cxxflags` -o $@

# obj/flattened_set_visitor.o: src/flattened_set_visitor.cpp src/flattened_set_visitor.h
# 	$(CC) $(CFLAG) -c $< -o $@

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*
	rm -f obj/*

stat:
	wc -l src/* test/*.h test/*.cpp
