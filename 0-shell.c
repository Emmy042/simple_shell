#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - executes "ls -l /tmp" in 5 child processes sequentially
 *
 * Return: 0 on success, -1 on failure
 */
int main(void)
{
	pid_t pid;
	int i;
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};

	for (i = 0; i < 5; i++)
	{
		pid = fork();

		if (pid < 0)
		{
			perror("Fork failed");
			return (-1);
		}
		else if (pid == 0)
		{
			/* Child executes command */
			printf("Child %d running `ls -l /tmp`:\n", i + 1);
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("execve failed");
				return (-1);
			}
		}
		else
		{
			/* Parent waits for current child to finish before continuing */
			wait(NULL);
		}
	}

	return (0);
}
