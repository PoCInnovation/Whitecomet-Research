# Whitecomet-Research

## Disclaimer

This project was realized for research and educational purpose ***only***. The PoC organization and its developers are not responsible of what you do with this project.

## Introduction

Whitecomet-Research is a project about Malwares made by PoC Innovation. The goal of this project is to study various types of techniques to bypass Antivirus, like polymorphic and metamorphic programs.

## - Polymorphism / Metamorphism

Polymorphic programs can modify themselves at each execution to be undetectable by anti-virus analysis. Each file on your machine has a unique signature (a hash) which change according to the content of the file (if you have two files with the exact same content, they will have the same MD5 hash signatures for example. You can check it on linux with `md5sum [file]`).
Metamorphism will be the same but the part that change in the binary with polymorphism is just encryption, with meta. it'll be the ASM instructions that'll be modified (without altering the original behavior).

#### Some Basics

- Polymorphism

At first execution, the payload is not encrypted, so the program just write a new binary on top of itself with it’s encrypted payload (with a key stored in a clear and accessible zone) and then executes the payload that is still in memory (not encrypted because of the first execution).
At each new execution, it will do the same thing, expect it will grab the XOR key and decrypt itself before doing anything of what’s mentioned above. And there will be a newly randomly generated key at each execution. The encryption process we chose is a one time pad xor.

For more specifics explanations we invite you to check our dedicated readme for Linux and Windows stored in the `Polymorphic` directory.

- Metamorphism

We're working with ASM instructions, there are many possible architectures but for the sake of the repo, we're going to go with x86-64-only. It is technically possible to code something that would adapt to the arch..
To understand where and how we change instructions, we invite you to check the dedicated readme Stored in the `Metamorphic` directory.

#### Why are the Linux and Windows directories separated ?

In order to create Polymorphic malwares, we have to use segments of binary files. Those segments represent different parts of the binary where code is stored. Linux and Windows do not use the same binary file format (ELF for Linux and PE for Windows) thus those segments are used differently. That's why we can build the same Malware for these two OS, but we won't have the exact same code.

The compilation and coding (ex: libraries) in both program will be different too, so that's why both are separated.

#### What does the payload/malware do ?

It's a basic reverse shell malware, that means when the Victim launches it, it will open a hidden command interpreter on his computer and link it on yours. So you can manage whatever you want in the limits that a shell can provide you of course.

#### Polymorphism and Anti-Virus

For a lot of AVs, polymorphic viruses can be difficult to analyze. First, because the malicious code is encrypted and second because the signature changes at every launch, so the AV can't just compare the program's hash with malicious hashes databases.

We used [virustotal](https://www.virustotal.com) for our tests.
<details>
  <summary>Linux results</summary>
<details>
  <summary>Polymorphism</summary> 
Virustotal
  
![Linux virustotal poly](https://cdn.discordapp.com/attachments/553270916570939422/750859939697655858/onvaimpressionnerlesreaders_1_virustotal.png)
OPSWAT

![Linux opswat poly](https://cdn.discordapp.com/attachments/553270916570939422/750863524783325184/renderimpressioner_metadef_1.png)
Falcon CrowdStrike

![Linux crowdstrike poly](https://media.discordapp.net/attachments/553270916570939422/750863527983710269/readerimpressioner_crowdstrike_1.png)
</details>
<details>
  <summary>Polymetamorphism</summary>

![Linux virustotal polymeta](https://cdn.discordapp.com/attachments/553270916570939422/752598644875591745/polymeta.png)
</details>
<details>
  <summary>Metamorphism</summary>

No metamorphic test because there are no payload in it. But surprisingly enough, you'll get 0 threats aswell.
</details>
</details>

<details>
  <summary>Windows results - Polymorhic only</summary>
<details>
  <summary>With VM/AV basic check</summary>

VirusTotal

![windows av result 1](https://cdn.discordapp.com/attachments/553270916570939422/752290069267611648/unknown.png)
AntiscanMe

![windows av result 2](https://cdn.discordapp.com/attachments/553270916570939422/752290793535832117/02rkSqjRN12d.png)
We can see that the most used/popular AVs (Avast, Kaspersky, AVG, Avira, BitDefender, W10 Defender,...) are not detecting the binary as a threat.
</details>
<details>
  <summary>Without VM/AV basic check</summary>
VirusTotal
  
![windows av result 1](https://cdn.discordapp.com/attachments/553270916570939422/752292342404481134/unknown.png)
AntiscanMe

![windows av result 2](https://cdn.discordapp.com/attachments/553270916570939422/752291918368473128/uSNbvs4vqIvj.png)
Even though there are less AVs that detect it, the major ones are triggered.
</details>
</details>

#### How AV can bypass Polymorphism

Some Anti-Virus uses AI during their analysis which allows them to spot hints and to guess the purpose of the malware and mark it as dangerous.
Dynamic analysis can counter those types of AV bypass.

## What's Next

We're looking for more FUD technics or how to bypass Anti-Virus that is using AI. We are also interested in making our own Anti-Virus to counter those threats (We have a tiny polymorphic checker in `./WC-AV`).
