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
