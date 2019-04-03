#include <stdio.h>

int main(int argc, char **argv){
	int i=0;
	argc--;
	*argv++;

	printf("argc: addr=%x val=%d\n", &argc, argc);
	printf("argv: addr=%x val=%x\n\n", &argv, argv);
	while (*argv){
		printf("arg%d: argv=%x [ *argv=%x: &(**argv)=%x ] **argv=%x **argv=%c *argv=%s\n", i++, argv, *argv, &(**argv), **argv, **argv, *argv);
		argv++;
	}
	printf("argv=%x [*argv=%x == &(**argv)=%x ]\n", argv, *argv, &(**argv));
}
