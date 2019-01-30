bin=HttpdServer
cc=g++
order=-lpthread
HttpdServer:HttpdServer.cc
	$(cc) -o $@ $^ $(order)

.PHONY:clean
clean:
	rm -f $(bin)
