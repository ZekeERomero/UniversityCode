#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 20

void producer(int produce)
{
	int i;
	for(i = 1; i <= BUFFER_SIZE; i++)
	{
		write(produce,&i,sizeof(i));
		sleep(1);
	}
	exit(0);
}

void consumer(int consume)
{
	int size, i;
	while((size = read(consume,&i,sizeof(i))) > 0)
	{
		printf("Received %d\n",i);
	}
	exit(0);
}

int main()
{
	int pipe_producer[2];
	int pipe_consumer[2];

	pid_t pid = fork();
	pid_t pid2 = fork();
	pid_t pid3 = fork();
	pid_t pid4 = fork();

	if(pid == 0 && pid2 == 0 && pid3 == 0)
	{
		close(pipe_producer[0]);
		producer(pipe_producer[1]);
	}
	if(pid > 0 && pid2 == 0 && pid3 == 0)
        {
                close(pipe_producer[1]);
                producer(pipe_producer[0]);

        }
	if(pid == 0 && pid2 > 0 && pid3 == 0)
        {
                printf("Hello");
        }
	if(pid == 0 && pid2 == 0 && pid3 > 0)
        {
                printf("Hello");
        }
	if(pid > 0 && pid2 == 1 && pid3 == 0)
        {
                printf("Hello");
        }
	if(pid == 0 && pid2 > 0 && pid3 == 1)
        {
                printf("Hello");
        }
	if(pid > 0 && pid2 == 0 && pid3 > 0)
        {
                printf("Hello");
        }
	if(pid > 0 && pid2 > 0 && pid3 > 0 && pid4 == 0)
        {
                printf("Hellooo");
        }
	if(pid > 0 && pid2 > 0 && pid3 > 0 && pid4 > 0)
        {
                printf("Hellooo");
		int status;
		wait(&status);
        }

	return 0;
}
