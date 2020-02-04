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

  printf("\n<%s> give me a new name?",bot->name);
  memset(buf,0,256); 
  scanf("%s",buf);
  size = strlen(buf);
  strcpy(bot->name, buf);

  printf("\n<%s> change your name?", nick->name);
  memset(buf,0,256); 
  scanf("%s",buf);
  strcpy(nick->name, buf);

  printf("\nSend a message?");
  memset(buf,0,256); 
  scanf("%s",buf);
  size = strlen(buf);
  printf("\nyour message is %s", buf);
  free(bot);
  free(nick);
  return 0;
}
