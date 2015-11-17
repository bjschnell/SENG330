all: main

main: main.cpp Machine.pb.h Machine.pb.cc
	g++ main.cpp Machine.pb.cc -o assign2 -l protobuf

Machine.pb.h:  Machine.proto
	protoc --cpp_out=. Machine.proto

Machine.pb.cc: Machine.proto
	
clean: assign2

