# Makefile:
# 2/10/15 by RD

all: client server client2 server2

clean:
	rm -rf client server client2 server2

test:
	@echo "To run the examples, first start the server in one terminal,"
	@echo "then start the client in another."
	@echo
	@echo "For example:"
	@echo "crystalcove# server 10000"
	@echo "crystalcove# client crystalcove 10000"
	@echo
	@echo "Different servers may be used as well:"
	@echo "crystalcove# server2 10000"
	@echo "zuma# client crystalcove 10000"


client: client.c
	gcc client.c -g -o client

server: server.c
	gcc server.c -g -o server

client2: client2.c
	gcc client2.c -Wall -ansi -g -o client2

server2: server2.c
	gcc server2.c -Wall -ansi -g -o server2

# EOF
