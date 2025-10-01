#include <stdint.h>
#include <stdio.h>

#include "dvec.h"

enum val_type {
	VAL_INT_TYPE,
	VAL_DEC_TYPE,
	VAL_STR_TYPE,
};

typedef struct string {
	char *ptr;
	size_t len; // w/o null terminator
} string;

typedef struct value {
	enum val_type type;
	union {
		int32_t i;
		float d;
		/* string */
	};
} value;

int32_t main(void)
{
	dvec_t(float) fv = DVEC_INIT;
	float a[] = { 9, 2, 1 };
	dv_copy_to(fv, 0, a, (sizeof a / sizeof a[0]));
	float *k;
	dv_foreach(fv, k)
		printf("%.6f\n", *k);


	dv_destroy(fv);
}
