#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

# define SWAP(a, b, T)		{T temp = a; a = b; b = temp;}

void	show_alloc_mem(void);
void	show_alloc_mem_ex(void);

# define ARR_SIZE 107

int			main(void)
{
	srand(time(NULL));
	
	char *a = malloc(sizeof(char));
	*a = 'a';

	int *num = malloc(sizeof(int));
	*num = 42;

	free(a);

	free(num); 


	return (0);
}

