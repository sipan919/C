merge_sort:
	gcc main.c msort.c common.c -g -o prog -lpthread

clean:
	rm -f prog *.txt


