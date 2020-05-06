# Whitecomet-Research

Whitecomet-Research is a project about an Polymorphic Malware. These kind of malwares are specials, cause they modified them self at each execution for being undetectable by anti-virus analysis. 


# How to use :


     git clone https://github.com/PoCFrance/Whitecomet-Research.git
     cd PoCrypt
	 ./build.sh

Now you get a binary named "**Pocrypt**" this is the malware.
On your device use `nc -l [port]` for waiting the reverse shell connexion.
Exec the binary on a computer that you want to infect.
Congratulation you're connected !

## How it work :

There's three main parts in the malware : Payload, Key and Cryptor.
We're using binary's segment for each parts.

The Payload :
It's a basic reverse shell, but it is encrypted.

The Key :
A random key regenerate at each execution of the program, uses for decrypt the Payload. It does the same size of the Payload for an **One Time Pad encryption**.

The Cryptor :
The function that's call in first when you launch the binary. It take the Key in it segment and use it with a XOR in the Payload segment for being readable and launch it. When it's done the Cryptor re encrypt the Payload with a new key.

## Does that's work :

Yeah, pretty much indeed ;p
At the moment only two anti-virus detect it as a threat on https://www.virustotal.com

## What's now :

We're actually looking on making this programs runnable on Windows, and also adding more FUD stuffs and technics.
