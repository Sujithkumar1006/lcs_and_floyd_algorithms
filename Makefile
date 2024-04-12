all: lcs floyd

lcs: lcs.c
	gcc -o lcs lcs.c
floyd: floyd.c
	gcc -o floyd floyd.c

clean:
	rm -rf lcs
	rm -rf floyd
	rm -rf output.txt