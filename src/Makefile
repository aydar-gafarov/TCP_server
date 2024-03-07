
all: clean
	touch log.txt
	g++ -std=c++17 server.cpp server_main.cpp -o server
	g++ -std=c++17 client.cpp client_main.cpp -o client

clean:
	rm -rf a.out log.txt server client