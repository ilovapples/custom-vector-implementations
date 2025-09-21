#include "hvec.h"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void *hv_new(size_t n, size_t size)
{
	const size_t byte_size = n*size;
	void *ret = malloc(byte_size + sizeof(struct hvec_header));

	struct hvec_header *header_ptr = ret;
	header_ptr->n = n; // set n in units of 'size' bytes (n*size is total size in bytes)
	header_ptr->capacity = n; // set capacity in uints of 'size' bytes
	header_ptr->size = size; // set element size in bytes

	memset(header_ptr+1, 0, byte_size);

	return (void *) (header_ptr+1);
}

int32_t hv_resize(void **hvec, size_t capacity)
{
	if (capacity <= hv_max(*hvec))
	{
		if (capacity <= hv_n(*hvec))
			return 0;
		hv_n(*hvec) = capacity;
		return 1;
	}

	void *new_ptr = realloc(_hv_header(*hvec), capacity * hv_elem_size(*hvec));
	if (new_ptr == NULL)
		return 0;

	struct hvec_header *header_ptr = new_ptr;
	header_ptr->capacity = capacity;

	*hvec = (void *)(header_ptr + 1);

	return 1;
}

void *hv_copy_at(void **hvec, size_t start, void *source, size_t n)
{
	if (source == NULL || n == 0)
		return NULL;

	hv_resize(*hvec, start+n);

	return memcpy(
			(uint8_t *)*hvec + start*hv_elem_size(*hvec),
			source,
			n*hv_elem_size(*hvec));
}
