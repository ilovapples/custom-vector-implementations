#ifndef HVEC_H
#define HVEC_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

struct hvec_header {
	size_t n;
	size_t capacity;
	size_t size;
};

#define _hv_header(hv) ((struct hvec_header *)(hv)-1)

#define hv_n(hv) (_hv_header(hv)->n)
#define hv_max(hv) (_hv_header(hv)->capacity)
#define hv_elem_size(hv) (_hv_header(hv)->size)

#define hv_destroy(hv) (free(_hv_header(hv)))

#define hv_push(hv, v) ( \
	hv_resize(hv, hv_n(hv)+1), \
	hv[hv_n(hv)-1] = v)

#define hv_pop(hv) ( \
	hv_resize(hv, hv_n(hv)-1), \
	hv[hv_n(hv)-1])

#define hv_peek(hv) (&hv[hv_n(hv)-1])

/* any function that returns an error code returns non-zero if it succeeds */

void *hv_new(size_t n, size_t size);
int32_t hv_resize(void **hvec, size_t capacity);
void *hv_copy_at(void **hvec, size_t start, void *source, size_t n);
#define hv_copy_at_m(hv, i, src, n) \
	(((src) == NULL || (n) == 0) ? 0 \
	: (hv_resize((void **)&(hv), (i)+(n)), \
		memcpy((hv)+(i), (src), (n)*hv_elem_size(hv)), \
		hv_n(hv)=hv_max(hv), 1))

#endif /* HVEC_H */
