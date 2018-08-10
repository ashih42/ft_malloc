//#include "ft_malloc.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

# define SWAP(a, b, T)		{T temp = a; a = b; b = temp;}

void	show_alloc_mem(void);
void	show_alloc_mem_ex(void);

# define ARR_SIZE 200

int			main(void)
{
	// THIS DOESN'T CRASH :(

	srand(time(NULL));
	
	char *array_tiny[ARR_SIZE];
	
	for (int i = 0; i < ARR_SIZE; i++)
	{
		size_t size = rand() % 128;
		if (size == 0) size = 1;
		array_tiny[i] = malloc(sizeof(char) * size);
		for (int j = 0; j < size; j++)
			array_tiny[i][j] = 'A';
	}

	show_alloc_mem();
	//show_alloc_mem_ex();

	//sleep(3);

	for (int i = 0; i < ARR_SIZE; i++)
	{
		int j = rand() % ARR_SIZE;
		SWAP(array_tiny[i], array_tiny[j], char *);
	}

	for (int i = 0; i < ARR_SIZE; i++)
	{
		free(array_tiny[i]);
	}
	

// printf("sizeof(t_zone) = %lu\n", sizeof(t_zone));
// printf("sizeof(t_block) = %lu\n", sizeof(t_block));
// printf("\n");

	return (0);
}

