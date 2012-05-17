compile:
	gcc myshell.c parse_args.c  -g -o myshell
test:
	gcc -DMEMWATCH -DMW_STDIO myshell.c parse_args.c -g

clean:
	rm -rf myshell a.out parse_args getline
