#ifndef HVEC_H
#define HVEC_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/* any function that returns an error code returns non-zero if it succeeds */

void *hvec_with_size(size_t n, size_t size);
int32_t hvec_resize(void **hvec, size_t capacity);
void *hv_copy_at(void *hvec, size_t start, void *source, size_t n);


struct hvec_header {
	size_t n;
	size_t capacity;
	size_t size;
};

#define _hv_header(hv) ((struct hvec_header *)(hv)-1)

#define hv_n(hv) (_hv_header(hv)->n)
#define hv_max(hv) (_hv_header(hv)->capacity)
#define hv_elem_size(hv) (_hv_header(hv)->size)

#define hv_push(hv) \
	

#endif /* HVEC_H */
