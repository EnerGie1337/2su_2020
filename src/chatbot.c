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
  printf("<");
  write(1, bot->name, 8);
  printf("> give me a new name?\n");
  memset(buf,0,256); 
  scanf("%s",buf);
  size = strlen(buf);
  strcpy(bot->name, buf);

  printf("<");
  write(1, nick->name, 256);
  printf("> change your name?\n");
  memset(buf,0,256); 
  scanf("%s",buf);
  strcpy(nick->name, buf);

  printf("Send a message?\n");
  memset(buf,0,256); 
  scanf("%s",buf);
  size = strlen(buf);
  printf("your message is %s\n", buf);
  free(bot);
  free(nick);
  return 0;
}
