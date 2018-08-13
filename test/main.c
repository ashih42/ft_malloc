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
// printf("sizeof(t_zone) = %lu\n", sizeof(t_zone));
// printf("sizeof(t_block) = %lu\n", sizeof(t_block));
// printf("\n");

	srand(time(NULL));
	
	char *array_tiny[ARR_SIZE];
	char *array_small[ARR_SIZE];

	//for (int i = 0; i < 107; i++)
	for (int i = 0; i < ARR_SIZE; i++)
	{
		array_tiny[i] = malloc(sizeof(char) * 128);
		array_small[i] = malloc(sizeof(char) * 1024);
	}
//	char *ptr = array_tiny[0] - 1;
//	*ptr = 'a';

	
//	show_alloc_mem();
	//show_alloc_mem_ex();

	sleep(2);

	for (int i = 0; i < ARR_SIZE; i++)
	{
		int j = rand() % ARR_SIZE;
		SWAP(array_tiny[i], array_tiny[j], char *);
		SWAP(array_small[i], array_small[j], char *);
	}

	for (int i = 0; i < ARR_SIZE; i++)
	{
		free(array_tiny[i]);
		free(array_small[i]);
	}
	



	return (0);
}

