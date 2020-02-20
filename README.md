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
