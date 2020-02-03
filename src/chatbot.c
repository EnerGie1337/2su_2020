#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user {
 char * name;
};

int main(int argc, char **argv){
  int run = 1;
  struct user *bot;
  bot = (struct user*)malloc(sizeof(struct user*));
  bot->name = malloc(sizeof(char)*20);
  strcpy(bot->name, "botname\0");
  struct user *nick;
  nick = (struct user*)malloc(sizeof(struct user*));
  nick->name = malloc(sizeof(char)*20);
  strcpy(nick->name, "nickname\0");
  char buf[256];
  int size;
  while(run){
    printf("\n<%s> ask me anything (? for help)\n<%s> ",bot->name, nick->name);
    memset(buf,0,256); 
    gets(buf);
    size = strlen(buf);
    if(!strcmp("?", buf)){
        printf("\nbot change botname\nnick change nickname\nquit for quitting");
    }else if(!strcmp("nick", buf)){
	printf("\nNew nickname?");
	memset(buf,0,256);
        gets(buf);
        strcpy(nick->name, buf);
    }else if(!strcmp("bot", buf)){
        printf("\nNew botname?");
	memset(buf,0,256);
        gets(buf);
        strcpy(bot->name, buf);
    }else if(!strcmp("quit", buf)){
        run = 0;
    }else{
      printf("Application in building");
    }
  }
  free(bot->name);
  free(bot);
  free(nick->name);
  free(nick);
  return 0;
}
