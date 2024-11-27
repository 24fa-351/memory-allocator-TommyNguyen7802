memtest_sys: memtest.c
	gcc -o memtest_sys memtest.c -DSYSTEM_MALLOC

memtest_user: memtest.c
	gcc -o memtest_user memtest.c my_mem.c

clean:
	rm memtest