#include <stdio.h>

#include "hvec.h"

int32_t main(void)
{
/*	int *vec = hv_new(5, sizeof(int));
	printf("n = %zu\n", hv_n(vec));
	int init[3] = { 151, 9, 50 };
	hv_copy_at_m(vec, 0, init, 3);
	printf("vec = { %d, %d, %d, %d, %d }\n", 
			vec[0], vec[1], vec[2], vec[3], vec[4]);
	
	printf("n = %zu\n", hv_n(vec));

	hv_destroy(vec);*/

	char *str = hv_new(1, sizeof(char));
	hv_copy_at_m(str, 0, "hello, world!\n", sizeof("hello, world!\n"));
	for (char *c = str; c - str < hv_n(str); ++c)
	{
		printf("<%02x> %c\n", *c, *c);
	}
	//printf("'%s'\n", str);
	printf("new size = %zu\n", hv_n(str));
	
	hv_destroy(str);

	return 0;
}
