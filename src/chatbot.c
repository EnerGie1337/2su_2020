#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user {
 char * name;
};

int main(int argc, char **argv){

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

  //printf("0x%08x\n", printf);

  printf("Change botname?\n");
  memset(buf,0,256); 
  scanf("%s",buf);
  size = strlen(buf);
  strcpy(bot->name, buf);

  printf("Change nickname?\n");
  memset(buf,0,256); 
  scanf("%s",buf);
  strcpy(nick->name, buf);

  printf("Your message?\n");
  memset(buf,0,256); 
  scanf("%s",buf);
  size = strlen(buf);
  free(bot);
  //free(nick);
  printf("Message sent\n");
  return 0;
}
