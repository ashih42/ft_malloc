#include "ft_malloc.h"

# define ARR_SIZE 150

int			main(void)
{
	srand(time(NULL));
	
	char *array_tiny[ARR_SIZE];
	char *array_small[ARR_SIZE];

	for (int i = 0; i < ARR_SIZE; i++)
	{
		array_tiny[i] = ft_malloc(sizeof(char) * 128);
		array_small[i] = ft_malloc(sizeof(char) * 1024);
	}

	// array_tiny[0][0] = 'A';
	// array_tiny[0][1] = 'B';
	// array_tiny[0][2] = '1';
	// array_tiny[0][3] = '2';
	// array_tiny[0][4] = 'z';
	
	show_alloc_mem();
	//show_alloc_mem_ex();

	sleep(3);

	for (int i = 0; i < ARR_SIZE; i++)
	{
		int j = rand() % ARR_SIZE;
		SWAP(array_tiny[i], array_tiny[j], char *);
		SWAP(array_small[i], array_small[j], char *);
	}

	for (int i = 0; i < ARR_SIZE; i++)
	{
		ft_free(array_tiny[i]);
		ft_free(array_small[i]);
	}
	







// printf("sizeof(t_zone) = %lu\n", sizeof(t_zone));
// printf("sizeof(t_block) = %lu\n", sizeof(t_block));
// printf("\n");


/*

	int		*a;
	int		*b;
	int		*c;
	// int		*d;

	print_alloc();

	ft_printf("MALLOCING...\n");
	a = malloc(sizeof(int));
	if (a == NULL)
		ft_printf("FUCK IT'S NULL\n");
	*a = 1;
	print_alloc();
	b = malloc(sizeof(int));
	*b = 2;
	print_alloc();
	c = malloc(sizeof(int));
	*c = 3;
	print_alloc();
	// d = malloc(0);
	// print_alloc();

	ft_printf("FREEING...\n");

	free(c);
	print_alloc();
	free(b);
	print_alloc();
	free(a);
	print_alloc();

	// ft_printf("MALLOCING...\n");
	// a = malloc(sizeof(int));
	// *a = 1;
	// print_alloc();
	// b = malloc(sizeof(int));
	// *b = 2;
	// print_alloc();
	// c = malloc(sizeof(int));
	// *c = 3;
	// print_alloc();
	// malloc(sizeof(long long));
	// print_alloc();

*/	



	return (0);
}







