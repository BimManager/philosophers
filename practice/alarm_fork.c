// Author: kkozlov

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFSIZE	64

int	main(void)
{
  char		*line;
  size_t	n;
  size_t	linecapp;
  int		seconds;
  char		message[BUFFSIZE];
  pid_t		pid;

  while (42)
  {
    linecapp = 0;
    line = NULL;
    printf("Alarm> ");  
    if (1 == (n = getline(&line, &linecapp, stdin)))
      return (0);
    if (2 > sscanf(line, "%d %64[^\n]", &seconds, message))
      printf("Bad command\n");
    else
    {
      if ((pid_t)-1 == (pid = fork()))
        printf("The creation of a child process has failed\n");
      else if ((pid_t)0 == pid)
      {
       sleep(seconds);
       printf("(%d) %s\n", seconds, message);
       exit(0);
      }
      else
        while ((pid_t)0 != (pid = waitpid((pid_t)-1, NULL, WNOHANG)))
          if ((pid_t)-1 ==pid)
            exit(2);
    }
    free(line);
  }
  return (0);
}
  
  


