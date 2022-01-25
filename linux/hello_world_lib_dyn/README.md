# Runtime linking in Linux

` man dlopen / dlsym

Dynamic linking library. If delete libHello we get error message.

` rm libHello.so

Check dependensyse form libHello.so

` ldd hello

Utility ldd - https://linux-faq.ru/page/komanda-ldd

Result for hello

    linux-vdso.so.1 (0x00007ffebc177000)
    libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007fe2152a5000)
    libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fe214eb4000)
    /lib64/ld-linux-x86-64.so.2 (0x00007fe2156ab000)