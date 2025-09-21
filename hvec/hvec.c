#include "hvec.h"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void *hvec_with_size(size_t n, size_t size)
{
	const size_t byte_size = n*size;
	void *ret = malloc(byte_size + sizeof(struct hvec_header));

	struct hvec_header *header_ptr = ret;
	header_ptr->n = n; // set n in units of 'size' bytes (n*size is total size in bytes)
	header_ptr->capacity = n; // set capacity in uints of 'size' bytes
	header_ptr->size = size; // set element size in bytes

	memset(ret, 0, byte_size);

	return (void *) (header_ptr+1);
}

int32_t hvec_resize(void **hvec, size_t capacity)
{
	const struct hvec_header header = *_hv_header(*hvec);
	
	void *new_ptr = realloc(_hv_header(*hvec), capacity * hv_elem_size(*hvec));
	if (new_ptr == NULL)
		return 0;

	struct hvec_header *header_ptr = new_ptr;
	header_ptr->capacity = capacity;

	*hvec = (void *)(header_ptr + 1);

	return 1;
}

void *hv_copy_at(void *hvec, size_t start, void *source, size_t n)
{
	if (source == NULL || n == 0)
		return NULL;

	if (start+n > hv_max(hvec))
		hvec_resize(&hvec, start+n);
	else if (start+n > hv_n(hvec))
		hv_n(hvec) = start+n;

	return memcpy(hvec, source, n*hv_n(hvec));
}
