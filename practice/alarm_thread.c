// Author: kkozlov

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define BUFFSIZE	64

typedef struct	s_alarm
{
  int			seconds;
  char			message[BUFFSIZE];
}				t_alarm;

static void	*alarm_thread(void *arg)
{
  t_alarm	*alarm;
  int		status;

  alarm = (t_alarm *)arg;
  status = pthread_detach(pthread_self());
  if (0 != status)
  {
    printf("pthread_detach error\n");
    exit(1);
  }
  sleep(alarm->seconds);
  printf("(%d) %s\n", alarm->seconds, alarm->message);
  free(alarm);
  return (NULL);
}

int	main(void)
{
  char		*line;
  size_t	n;
  size_t	linecapp;
  pthread_t	thread;
  int		status;
  t_alarm	*alarm;
  
  while (42)
  {
    linecapp = 0;
    line = NULL;
    printf("Alarm> ");  
    if (1 == (n = getline(&line, &linecapp, stdin)))
      return (0);
    alarm = malloc(sizeof(t_alarm));
    if (2 > sscanf(line, "%d %64[^\n]", &alarm->seconds, alarm->message))
      printf("Bad command\n");
    else
    {
      status = pthread_create(&thread, NULL, &alarm_thread, alarm);
      if (0 != status)
      {
        printf("pthread_create has failed\n");
        return (1);
      }
    }
    free(line);
  }
  return (0);
}
  
  


