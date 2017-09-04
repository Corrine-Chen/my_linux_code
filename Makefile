funtest:funtest.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -f funtest
