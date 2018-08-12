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
	write(1, "\tWRAPPER START\n", 15);
	
	system("export MALLOC_VERBOSE=1; ./run.sh ./test0");

	write(1, "\tWRAPPER END\n", 13);


	return (0);
}

