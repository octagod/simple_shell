#include "main.h"

/**
 * cpy_info - copies information between void pointers.
 * @newptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 *
 * Return: no return.
 */
void cpy_info(void *newptr, const void *ptr, unsigned int size)
{
	char *charcter_pointer = (char *)ptr;
	char *new_charcter_pointer = (char *)newptr;
	unsigned int a = 0;

	while (a < size)
	{
		new_charcter_pointer[a] = charcter_pointer[a];
		a++;
	}
}

/**
 * _reallocate - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_reallocate(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		cpy_info(newptr, ptr, new_size);
	else
		cpy_info(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _reallocatedp - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_reallocatedp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int a;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (a = 0; a < old_size; a++)
		newptr[a] = ptr[a];

	free(ptr);

	return (newptr);
}
