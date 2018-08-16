#include <stdlib.h>
#include <unistd.h>

int main() 
{
	write(1, "MAIN 1\n", 7);
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		i++;
	}
	write(1, "MAIN 2\n", 7);
	return (0);
}
