#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>


# define SWAP(a, b, T)		{T temp = a; a = b; b = temp;}

void	show_alloc_mem(void);
void	show_alloc_mem_ex(void);

# define ARR_SIZE 10

int			main(void)
{
	srand(time(NULL));
	
	
	char *array_large[ARR_SIZE];

	for (int i = 0; i < ARR_SIZE; i++)
	{
		array_large[i] = malloc(sizeof(char) * 2000);
	}


	show_alloc_mem();
	//show_alloc_mem_ex();

	sleep(2);

	for (int i = 0; i < ARR_SIZE; i++)
	{
		int j = rand() % ARR_SIZE;
		SWAP(array_large[i], array_large[j], char *);
	}

	for (int i = 0; i < ARR_SIZE; i++)
	{
		free(array_large[i]);
	}
	
	return (0);
}

