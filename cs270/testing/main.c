#include <stdio.h>
#include <stdlib.h> //getenv


int main( int argc, char *argv[], char *envp[])
{
	int i;
	
	printf("\n");
	for (i = 0; i < argc; i++)
	{
		printf("envp[%d]: %s\n",i,envp[i]);
	}
	putenv("NEW_PATH","/usr/bin"); //creates an environment, or replaces an existing one
	setenv("NEW_PATH","value",0); //sets the environment to equal a value
	unsetenv("NEW_PATH"); //removes an environment
	if (getenv("/bin/bash") != NULL)
	{
		//success
		printf("exists");
	}
	if (setenv("bin/bash","5",0) == 0)
	{
		//success
	}
}
