#include "ft_malloc.h"

# define ARR_SIZE 150

int			main(void)
{
	srand(time(NULL));
//	ft_printf("\nmain()\n");


	
	char *array[ARR_SIZE];

	for (int i = 0; i < ARR_SIZE; i++)
		array[i] = ft_malloc(sizeof(char) * 128);

	for (int i = 0; i < ARR_SIZE; i++)
	{
		int j = rand() % ARR_SIZE;
		SWAP(array[i], array[j], char *);
	}

	for (int i = 0; i < ARR_SIZE; i++)
		ft_free(array[i]);
	
//	ft_printf("\nLA FINI\n");






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







