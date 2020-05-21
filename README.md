# WhiteComet-Research

Whitecomet-Research is a project about Polymorphic Malwares. Those can modify themselves at each execution to be undetectable by anti-virus analysis.  
Each file on your machine has a unique MD5 hash which change according to the content of the file (if you have two files with the exact same content, they’ll have the same MD5 hash signatures, you can check it on linux with `md5sum [program]`). 


## Some Basics

At first execution, the payload is not crypted, so the program just write a new binary on top of itself with it’s encrypted payload (with a XOR key which is stored in a clear and accessible zone) and then executes the payload that is still in memory (not crypted because of the first execution).  
At each new execution, it will do the same thing, expect it will grab the XOR key and decrypt itself before doing anything of what’s mentioned above. And there will be a newly randomly generated key at each execution.

For more specifics explanations we invite you to check our dedicated readme for Linux and Windows stored in the `Polymorphic` directory.

### Why are the Linux and Windows directories separated ?

It's cause in order to create Polymorphic malwares, we have to use segments of binary files. Those segments represent different parts of the binary where code is stored.
Between Linux and Windows those segments are kind of different. That's why we can build the same Malware for these two OS, but we won't have the exact same code.

### What does this malware do ?

It's a basic reverse shell malware, that means when the Victim launches it, it will open a hidden command interpreter on his computer and link it on yours. So you can manage whatever you want in the limits that a shell can provide you of course.

## Polymorphism and Anti-Virus

For the majority of AV, polymorphic virus can be difficult to analyse. It's mainly cause first, the malware code is encrypted and second, the signature changes at every launch, so the AV can't just compare the MD5 hash with a MD5 malicious database.

We used [virustotal](https://www.virustotal.com) for our tests

### Results for Linux
VirusTotal
![Linux av result](https://media.discordapp.net/attachments/553270916570939422/705782405474156624/2020-05-01-160700_1187x817_scrot.png)

### Results for Windows
VirusTotal
![windows av result 1](https://media.discordapp.net/attachments/553270916570939422/710856571931852840/unknown.png)
Other virus scanner
![windows av result 2](https://media.discordapp.net/attachments/553270916570939422/710895246204207205/unknown.png)

### How AV can bypass Polymorphism

Some Anti-Virus uses I.A during their analysis that allows them to spot hints and to guess the purpose of the malware and mark it as dangerous.

## What's Next

We're looking for more FUD technics, like metamorphic malware or how to bypass Anti-Virus that's using I.A. But we also interest by making our Anti-Virus to counter those threats.# Whitecomet-Research
