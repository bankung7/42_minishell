// // // #include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

int	main()
{
	int	pipefd[2];
	char *wc[] = {"/bin/wc", NULL};
	char *ls[] = {"/bin/ls", NULL};
	// char s[100];

	pipe(pipefd);
	int process1 = fork();
	if (process1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve(ls[0], ls, NULL);
		// execlp("ls", "ls", NULL);
		// exit(0);
	}
	else
	{
		int process2 = fork();
		if (process2 == 0)
		{
			// wait(NULL);
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			execve(wc[0], wc, NULL);
			// execlp("wc", "wc", NULL);
			// int process2 = fork();
			// if (process2 == 0)
			// {
				// exit(0);
			// }
		}
	}
	close(pipefd[0]);
	close(pipefd[1]);

}
// // // #include "libft.h"

// // #define NPROC	3
// // // int	main(int ac, char **av)
// // int	main()
// // {
// // 	int	pid[NPROC];
// // 	char	cwd[100];
// // 	// int pipes[ac - 4][2]; //3
// // 	int	i;
// // 	// char **argv;

// // 	// for (i = 0; i < ac - 4; i++) //3
// // 	// 	pipe(pipes[i]);

// // 	for (i = 0; i < NPROC; i++)
// // 	{
// // 		pid[i] = fork();
// // 		if (pid[i] == 0)
// // 		{
// // 			// Child process
// // 			// printf("(%d) return : %d\n", i, sleep(3 - i));
// // 			if (chdir("srcs/") == -1)
// // 				printf("Error\n");
// // 			else{
// // 				printf("cwd: %s\n", getcwd(cwd, 100));
// // 			}
// // 			return (0);
// // 		}
// // 	}
// // 	// Main process
// // 	while (wait(NULL) != -1 || errno != ECHILD) ;
// // 	return (0);
// // }

// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>
// #include <stdlib.h>
// #include <sys/wait.h>

// #define MAX_LINE_LENGTH 1024

// int main() {
//   char line[MAX_LINE_LENGTH];
//   char *argv[MAX_LINE_LENGTH / 2 + 1];  // command line arguments

//   while (1) {
//     // print the command prompt
//     printf("$ ");
//     fflush(stdout);

//     // read the command line
//     fgets(line, MAX_LINE_LENGTH, stdin);

//     // parse the command line into argv
//     char *p = line;
//     int argc = 0;
//     while (*p != '\0' && *p != '\n') {
//       while (*p == ' ' || *p == '\t') {
//         *p++ = '\0';
//       }
//       if (*p != '\0' && *p != '\n') {
//         argv[argc++] = p;
//       }
//       while (*p != '\0' && *p != '\n' && *p != ' ' && *p != '\t') {
//         p++;
//       }
//     }
//     *p = '\0';
//     argv[argc] = NULL;

//     // exit the shell if the command is "exit"
//     if (strcmp(argv[0], "exit") == 0) {
//       break;
//     }

//     // change the current working directory if the command is "cd"
//     if (strcmp(argv[0], "cd") == 0) {
//       if (argv[1] == NULL) {
//         // if no directory is specified, go to home directory
//         char *home_dir = getenv("HOME");
//         if (home_dir != NULL) {
//           chdir(home_dir);
//         } else {
//           printf("Error: HOME environment variable not set\n");
//         }
//       } else {
//         if (chdir(argv[1]) != 0) {
//           printf("Error: Could not change to directory %s\n", argv[1]);
//         }
//       }
//       continue;  // go to next iteration of the loop
//     }

//     // check for piping
//     int pipe_index = -1;
//     for (int i = 0; i < argc; i++) {
//       if (strcmp(argv[i], "|") == 0) {
//         pipe_index = i;
//         argv[i] = NULL;  // replace the pipe symbol with NULL
//         break;
//       }
//     }

//     if (pipe_index != -1) {
//       // piping is used, create two processes
//       int pipefd[2];
//       if (pipe(pipefd) != 0) {
//         printf("Error: Could not create pipe\n");
//         continue;
//       }

//       // create first child process
//       int child_pid1 = fork();
//       if (child_pid1 == 0) {
//         // first child process
//         dup2(pipefd[1], STDOUT_FILENO);  // redirect stdout to write end of pipe
//         close(pipefd[0]);  // close unused read end of pipe
//         execvp(argv[0], argv);  // execute command
//         printf("Command not found: %s\n", argv[0]);
//         exit(1);
//       } else {
//         // create second child process
//         int child_pid2 = fork();
//         if (child_pid2 == 0) {
//           // second child process
//           dup2(pipefd[0], STDIN_FILENO);  // redirect stdin to read end of pipe
//           close(pipefd[1]);  // close unused write end of pipe
//           execvp(argv[pipe_index + 1], &argv[pipe_index + 1]);  // execute command
//           printf("Command not found: %s\n", argv[pipe_index + 1]);
//           exit(1);
//         } else {
//           // parent process
//           close(pipefd[0]);  // close unused read end of pipe
//           close(pipefd[1]);  // close unused write end of pipe
//           wait(NULL);  // wait for first child process to finish
//           wait(NULL);  // wait for second child process to finish
//         }
//       }
//     } else {
//       // no piping, create a single process
//       int child_pid = fork();
//       if (child_pid == 0) {
//         // child process
//         execvp(argv[0], argv);
//         printf("Command not found: %s\n", argv[0]);
//         exit(1);
//       } else {
//         // parent process
//         wait(NULL);  // wait for child process to finish
//       }
//     }
//   }

//   return 0;
// }
