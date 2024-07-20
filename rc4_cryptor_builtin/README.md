# rc4_cryptor_builtin

Uses the classic `VirtualAlloc`, `VirtualProtect` pattern to load encrypted shellcode and execute it.
- This pops a calc, encrypted with the password `CreateThread`.
- Here, the shellcode is encrypted with RC4 using Windows' builtin undocumented RC4 encryption function `System032`.