# Polymorphism for Windows

This part is dedicated for Windows's users, if you need a refresh of what is a polymorphic program just click [here](https://github.com/PoCFrance/Whitecomet-Research/tree/master). Or if you looking for a Linux version click [here](https://github.com/PoCFrance/Whitecomet-Research/tree/master/Polymorphic/Linux-ELF) (we recommand you check this one out before trying to understand what's going on here).

To know what to crypt or where to find the key for instance, we used [sections (PE)](https://en.wikipedia.org/wiki/Portable_Executable#Layout), which you can see like drawers for your binary content (in the idea, it's pretty similar to the linux version). 
The key(s) are stored in `.data` (which is a real native section), the payload function and some utils functions in `.code` (This section doesn't exist, we can create/alter an already existing sections with `__attribute__((section(x)))` ([variable](http://www.keil.com/support/man/docs/armcc/armcc_chr1359124977848.htm), [function](http://www.keil.com/support/man/docs/armclang_ref/armclang_ref_chr1384876160481.htm), [`#pragma`](https://docs.microsoft.com/fr-fr/cpp/preprocessor/section?view=vs-2019)).
In this version we're going to use 3 more (fake) keys to slow down reverse eng., each one of the four keys are going to be changed at each execution.

> *Payload :
> Component of a computer virus that runs the malicious commands.*

# How to use :

First of all, you need to refer your IP and a Port to use, in `src/main.c` line 22 and 24.
In order to use it over the internet, use your public IP and forward the associated port.
The size of the payload (important for encryption) is in `include/PE.h` as `KEY_SIZE`, change it accordingly.

     git clone https://github.com/PoCFrance/Whitecomet-Research.git
     cd Polymorphic/Windows-PE
     build_cmake_mingw.bat 

Now you get a binary named "**PEFile_tests.exe**" this is the malware.
On your device use `nc -l [port]` to wait the reverse shell connexion.
Then, the binary must be executed on the victim's machine in order to work.
Congratulation you're connected !

## How it works (Almost the same as the Linux one):

There are three main parts in the malware : the Payload, Key and Cryptor. This is the exact same process on paper, we invite you to check our [Linux polymorphic binary]((https://github.com/PoCFrance/Whitecomet-Research/tree/master/Polymorphic/Linux-ELF)) to understand how everything works. Again, this part explain the process on paper, when coding, at lot of things are going to be different since we are on Windows. 
This is the only modification we did to the process :

#### The Keys - Not Crypted
A random key regenerates at each execution of the program, used to decrypt the Payload. The key and the payload must have the same length in order to have an **One Time Pad encryption**([\*](https://en.wikipedia.org/wiki/One-time_pad)).
Here, we use 4 keys and rewrite on top of each one of them a new random one. We don't move the var. in other sections, because an initialized static global variable automatically goes to `.data`. The formula to get a specific key in `.data` just by it's index is in `PE.h`.

# Differences with the Linux version :
- In order to change page permissions (`change_section_permission.c`) we needed to change the functions called to some equivalent.
- We don't use a bool to know wether it's the first time the program is running, we just strcmp one of the keys with a determined value.
- Now we can get the base memory address from the binary itself (generally 0x400000). But it can change with different systems.
- We don't read(argv[0]) but GetModuleHandle(NULL)
- AntiViruses don't really care about Linux, so Windows protection is a lot better and harder to bypass : 
  - We added two techniques : Allocating too much memory, to not run the program on simulated environements aswell as checking the name of the binary (if it's PEFile_tests.exe), cause if it isn't, it means we're probably in an AV system.
  - On Windows, a process can't delete a file that is already running, which is a problem for a program that rewrites itself. So we create some temporary files which we rename during execution, which is not the best solution but works for our proof of concept.
