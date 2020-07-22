# Metamorphism for Linux

`!! Made with x86-64 !!`

This part is dedicated to Linux users, if you need a refresh of what a metamorphic program is just click [here](https://github.com/PoCFrance/Whitecomet-Research/tree/master).
To know what to change in the binary, we're going to look only at the ASM instructions.
The way we chose to do it on this repo is to randomly put a pattern in the ASM instructions that we can recognize and change.
The goal is : at the end of exec, the ASM content won't be the same, but the behavior/result of the program'll be the same.

# How to use :

Here, we only showcase how you can do metamorphism with no payload. There will be no option or pre-requirements to do here.
Just compile and start the program, at each execution you'll have different ASM content aswell as a new hash signature.

     make
     # md5sum PoCrypt >> hashes
     # objdump -d ./PoCrypt > dump0
     ./PoCrypt
     # objdump -d ./PoCrypt > dump1
     # diff dump0 dump1
     # md5sum PoCrypt >> hashes && cat hashes

# How it works :

We create a pattern (which can be seen in `include/meta.h`), with a shell: in our case the first and last 3 bytes of the pattern (we won't touch the shell).
So each time we execute the binary, it'll change it's instructions between those 6 bytes of each pattern.
The original pattern will of course do nothing, here we push [RFLAGS](https://en.wikipedia.org/wiki/FLAGS_register) aswell as RAX and RBX. Every action that changes the flags or RAX/RBX won't do anything drastic ("dead" instructions).

#### Pattern Parser
We injected patterns into our code, we need to find them again to change them.
In the source code there's `strstr_asm` (checks pattern's first 3 bytes and moves ptr) and `valid_pattern` (last 3 bytes) that complete each other.
We now know when to change the "dead" instructions.

#### ASM NoOp Generator (gen_bytes.c)
Generate code that does nothing, (shift bytes 0 to the left, inc + dec, etc...) according to a given size.

### Once you have the pattern and the correct new instructions, you replace them.

#### The forgotten ones : Random - File managing
Very basic file handling (but we overwrite the original binary) and randomness.
