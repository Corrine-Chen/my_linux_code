client_=client
server_=server
cc=gcc

Clisrc=client.c comm.c
Sersrc=server.c comm.c


.PHONY:all
all: $(client_) $(server_)

$(client_):$(Clisrc)
	$(cc) -o $@ $^
$(server_):$(Sersrc)
	$(cc) -o $@ $^

.PHONY:clean
clean:
	rm -f $(server_) $(client_)




