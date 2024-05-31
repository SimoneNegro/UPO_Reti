all: server client

# esempio port: 3000
server: server.c
	gcc server.c -o server

# esempio server port: 0 3000
client: client.c
	gcc client.c -o client

clean:
	rm -f server client
