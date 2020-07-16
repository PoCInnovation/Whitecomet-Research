#!/bin/sh
gcc -o PoCrypt -masm=intel src/gen_bytes.c src/main.c src/replace_bytes.c src/ELF/change_sec_perm.c src/ELF/find_section.c -I./include -lm -lkeystone