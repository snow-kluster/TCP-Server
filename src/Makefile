CC = g++
CXXFLAGS = -lws2_32
BUILDDIR=$(CURDIR)/../build
all: program1 program2 program3 program4

program1: multi-server.cpp
	g++ Multi-Server.cpp -lws2_32 -o $(BUILDDIR)/server.exe

program2: client.cpp
	g++ client.cpp -lws2_32 -Wzero-as-null-pointer-constant -o $(BUILDDIR)/client0.exe

program3: client.cpp
	g++ client.cpp -lws2_32 -Wzero-as-null-pointer-constant -o $(BUILDDIR)/client1.exe

program4: client.cpp
	g++ client.cpp -lws2_32 -Wzero-as-null-pointer-constant -o $(BUILDDIR)/client2.exe
