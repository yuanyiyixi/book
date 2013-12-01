#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define   DEBUG
#define   LEN    128

int myshell(char **argu);
void free_memery(int argc, char **argu);


int main(void)
{
	int argc = 0, i;
	char *argu[16] = { NULL };
	argc = myshell(argu);
	while (argc < 3)
	{
		fprintf(stderr, "The arguments are too less, Please again!\n");
		free_memery(argc, argu);
		argc = myshell(argu);
	}
	//system();
	for (i = 0; i < argc; i++)
	{
		fprintf(stdout, "argu[%d] = %s...\n", i, argu[i]);
	}

	free_memery(argc, argu);

	return 0;
}

//free the memery from heap
void free_memery(int argc, char **argu)
{
	int i;
	for (i = 0; i < argc; i++)
	{
		free(argu[i]);
		argu[i] = NULL;
	}
}

//myshell is just very simple! You can add your function and 
//make it complex! Do it by yourself and belive yourself.
//If you have something that you don't understand, please tell
//me, Maybe I can help you solve it!
int myshell(char **argu)
{
#ifdef DEBUG
	assert(NULL != argu);
#endif
	if (NULL == argu)
	{
		return 0;
	}

	int i = 0, rtval = -1;
	char *tmp = NULL, *p = NULL, buf[LEN] = { 0 };


	fprintf(stdout, "myshell$");
	tmp = fgets(buf, LEN, stdin);
	if (0 != (rtval = strcasecmp(tmp, "quit")))
	{
		buf[strlen(tmp) - 1] = 0;

		while (NULL != (p = strsep(&tmp, " ")))
		{
			argu[i] = (char *)malloc(LEN);    //Don't forget to ask memery!
			if (NULL == argu[i])
			{
				fprintf(stderr, "malloc failed!\n");
				exit(EXIT_FAILURE);
			}
			strcpy(argu[i], p);    //Maybe here you will ask me why not use "argu[i] = p",
								   //I say what you think is wrong!
			i++;
		}
	}
	return i;
}
