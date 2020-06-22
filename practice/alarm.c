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
      sleep(seconds);
      printf("(%d) %s\n", seconds, message);
    }
    free(line);
  }
  return (0);
}
  
  


