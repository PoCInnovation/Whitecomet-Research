# WhiteComet-Research

Whitecomet-Research is a project about Polymorphic Malwares. Those can modify themselves at each execution to be undetectable by anti-virus analysis.  
Each file on your machine has a unique MD5 hash which change according to the content of the file (if you have two files with the exact same content, they’ll have the same MD5 hash signatures, you can check it on linux with `md5sum [program]`). 


## Some Basics

At first execution, the payload is not crypted, so the program just write a new binary on top of itself with it’s encrypted payload (with a XOR key which is stored in a clear and accessible zone) and then executes the payload that is still in memory (not crypted because of the first execution).  
At each new execution, it will do the same thing, expect it will grab the XOR key and decrypt itself before doing anything of what’s mentioned above. And there will be a newly randomly generated key at each execution.

For more specifics explanations we invite you to check our dedicates readme for Linux and Windows stored in the `Polymorphic` directory.

### Why there is different directory for Linux and Windows ?

It's cause for making Polymorphic malware, we have to use segments of binary files that's we create. Those segment represent different parts of a binary where codes are stored. Between Linux and Windows those utilisation are kind of different. That's why we can build the same Malware for these two OS.

### What this malware does ?

It's a basic reverse shell malware, that's mean when the Victim launch it, it will open a command interpreter on his computer and linked it on your's. So you can managed whatever you want in the limits that a shell can provide you of course.

## Polymorphism and Anti-Virus

For the majority of AV, polymorphic virus can be difficult to analyse. It's mainly cause in one hand by the encryption of the Payload so the anti-virus doesn't know what's going on in the program. And in other hand the anti-virus can't stored informations like the signature of the virus cause it haven't any.

We used [virustotal](https://www.virustotal.com) for our tests

### Results for Linux

![Linux av result](https://media.discordapp.net/attachments/553270916570939422/705782405474156624/2020-05-01-160700_1187x817_scrot.png)

### Results for Windows
![windows av result 1](https://media.discordapp.net/attachments/553270916570939422/710856571931852840/unknown.png)
![windows av result 2](https://media.discordapp.net/attachments/553270916570939422/710895246204207205/unknown.png)

### How AV can bypass Polymorphism

Some Anti-Virus uses I.A during their analyse that's allow them to spot hints that's allow them to guess the purpose of the malware and marked it as dangerous.

## What's Next

Were looking for more FUD technics, likes metamorphic malware or how to bypass Anti-Virus that's using I.A. But we also interest by making our Anti-Virus to counter those threats.# Whitecomet-Research
