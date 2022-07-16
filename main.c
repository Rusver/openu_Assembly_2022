#include "main.h"


int main(int argc, char *argv[])
{
    open_files(argc, argv);

    return 0;
}

free_list(char** list, int list_len)
{
	int i;
	for(i= list_len - 1; i >= 0; i--)
	{
		list[i] = NULL;
		free(list[i]);
	}
}