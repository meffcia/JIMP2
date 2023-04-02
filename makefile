code: makeTree.c readTree.c main2.c compress.c 
	cc main2.c makeTree.c compress.c  readTree.c -o code

decode: main3.c decompress.c readTree.c
	cc main3.c decompress.c readTree.c -o decode


