# Polymorphism for Linux

This part is dedicated for linux's users, if you need a refresh of what is a polymorphic program just clic here. Or if you looking for a windows version clic here

To know what to crypt or where to find the key for instance, we used [sections (ELF)](https://fr.wikipedia.org/wiki/Executable_and_Linkable_Format), which you can see like drawers for your binary content. The key is stocked in `.PoC_Key`, the payload function in `.unix`, and a boolean to know wether we are running it for the first time or not `.unixb`. (Those sections doesn't exist, we can create/alter an already existing sections with `__attribute__((section(x)))` ([variable](http://www.keil.com/support/man/docs/armcc/armcc_chr1359124977848.htm), [function](http://www.keil.com/support/man/docs/armclang_ref/armclang_ref_chr1384876160481.htm), [`#pragma`](https://docs.microsoft.com/fr-fr/cpp/preprocessor/section?view=vs-2019)).

> *Payload :
> Component of a computer virus that runs the malicious commands.*

# How to use :

First one, you need to refer your IP and a Port to use, in `src/main.c` line 74 and 68.
For use it over internet, use your public IP and make a port forward on your local computer's IP with the associate Port.

     git clone https://github.com/PoCFrance/Whitecomet-Research.git
     cd PoCrypt
	 make re

Now you get a binary named "**Pocrypt**" this is the malware.
On your device use `nc -l [port]` for waiting the reverse shell connexion.
Then, the binary must be executed on the victim's machine in order for it to connect.
Congratulation you're connected !

## How it works :

There are three main parts in the malware : the Payload, Key and Cryptor.
We're using binary's segments for each parts.

#### The Cryptor - Not Crypted
The first function called when launching the binary. It finds the Key and use it with the [XOR operation](https://en.wikipedia.org/wiki/XOR_cipher) in order to decrypt (on the currently running binary) the Payload segment. When it's done the Cryptor re encrypt the Payload with a new key.

#### The Key - Not Crypted
A random key regenerates at each execution of the program, used to decrypt the Payload. The key and the payload must have the same length in order to have an **One Time Pad encryption**([\*](https://en.wikipedia.org/wiki/One-time_pad)).

#### The Payload - Crypted
Basic reverse shell, the victim execute the program that then opens a server on it's machine on which you can connect and run commands.


##### The forgotten one : Saving - Not Crypted
Very basic file writing with the exception of deleting itself before doing so.

