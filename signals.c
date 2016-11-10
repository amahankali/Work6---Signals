#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>


static void sighandler(int signo)
{
	if(signo == SIGINT)
	{
		////////
		umask(0);
		int fd = open("ansfile.txt", O_CREAT | O_WRONLY | O_APPEND, 0666);
		char* message = (char *) malloc(40);
		sprintf(message, "PID %d exited due to SIGINT\n", getpid());
		write(fd, message, strlen(message));
		close(fd);
		free(message);
		exit(0);

	}
	if(signo == SIGUSR1)
	{
		printf("PID of parent process: %d\n", getppid());
	}
}

int main () {

	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);

	while(1)
	{
		printf("Process id: %d\n", getpid());
		sleep(1);
	}

}