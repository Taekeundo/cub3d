#include "cub3d.h"

void print_char_array(char **array)
{
	int count_h;

	count_h = 0;
	while(array[count_h])
	{
		printf("|%s|    Line %i\n", array[count_h], count_h);
		count_h++;
	}
	printf("\n\n\n");
}