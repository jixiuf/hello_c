compile:
	gcc myshell.c parse_args.c memwatch.c -g -o myshell
test:
	gcc -DMEMWATCH -DMW_STDIO myshell.c parse_args.c memwatch.c -g

clean:
	rm -rf myshell a.out parse_args getline
