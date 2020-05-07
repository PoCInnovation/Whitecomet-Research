# PoCrypt

Whitecomet-Research is a project about Polymorphic Malwares. Those can modify themselves at each execution to be undetectable by anti-virus analysis.
Each file on your machine has a unique MD5 hash which change according to the content of the file (if you have two files with the exact same content, they'll have the same MD5 hash signatures, you can check it on linux with ```md5sum [program]```).
At first execution, the payload is not crypted, so the program just write a new binary ontop of itself with it's payload crypted (with a XOR key which is stored in a clear and accessible zone) and then executes the payload that is still in memory (not crypted because of the first execution). 
At each new execution, it will do the same thing, expect it will grab the XOR key and decrypt itself before doing anything of what's mentioned above. And there will be a newly randomly generated key at each execution.

To know what to crypt or where to find the key for instance, we used [sections (ELF)](https://fr.wikipedia.org/wiki/Executable_and_Linkable_Format), which you can see like drawers for your binary content. The key is stocked in `.PoC_Key`, the payload function in `.unix`, and a boolean to know wether we are running it for the first time or not `.unix_b`.

> *Payload : 
> Component of a computer virus that runs the malicious commands.*

# How to use :


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

**The Cryptor \(Not Crypted) **
The function that is called first when launching the binary. It takes the Key in it's segment and use it with XOR to crypt the Payload segment for being readable and launch it. When it's done the Cryptor re encrypt the Payload with a new key.

**The Key \(Not Crypted) **
A random key regenerate at each execution of the program, uses for decrypt the Payload. It does the same size of the Payload for an **One Time Pad encryption**.

**The Payload \(Crypted) **
It's a basic reverse shell, but it is encrypted.


## Does it work ? :

Yeah, pretty much indeed ;p
At the moment only two anti-virus detect it as a threat on https://www.virustotal.com
(Note that this is an ELF binary, and ELF are a lot less thoroughly analyzed).
PE : Windows binary format
ELF : Usually Linux binary format

## What's next ? :

We're actually thiking of making this programs runnable on Windows, and also adding more FUD technics, aswell as looking into making it's own antivirus! 
