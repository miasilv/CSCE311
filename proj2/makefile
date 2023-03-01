text-client: client_main.o text_client.o unix_domain_sock.o
	g++ bin/client_main.o bin/text_client.o bin/unix_domain_sock.o -o text-client

client_main.o: src/client_main.cc
	g++ -c src/client_main.cc -o bin/client_main.o

text_client.o: src/text_client.cc inc/text_client.h
	g++ -c src/text_client.cc -o bin/text_client.o



text-server: server_main.o server_client.o unix_domain_sock.o
	g++ bin/server_main.o bin/text_server.o bin/unix_domain_sock.o -o text-server

server_main.o: src/server_main.cc
	g++ -c src/server_main.cc -o bin/server_main.o

server_client.o: src/text_server.cc inc/text_server.h 
	g++ -c src/text_server.cc -o bin/text_server.o
	


unix_domain_sock.o: src/unix_domain_sock.cc inc/unix_domain_sock.h
	g++ -c src/unix_domain_sock.cc -o bin/unix_domain_sock.o



clean:
	rm bin/*
	rm text-client
	rm text-server