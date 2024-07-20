# rc4-crypter

Uses the classic `VirtualAlloc`, `VirtualProtect` pattern to load encrypted shellcode and execute it.
- This pops a calc, encrypted with the password `CreateThread`.
- Here, the shellcode is encrypted with RC4 instead.