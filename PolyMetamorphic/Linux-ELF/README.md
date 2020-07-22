# PolyMetamorphism for Linux

`!! Made with x86-64 !!`

This part is dedicated to Linux users, if you need a refresh of what a metamorphic/polymorphic program is just click [here](https://github.com/PoCFrance/Whitecomet-Research/tree/master).
We're now going to merge both idea and crypt a segment aswell as change ASM instructions all over the binary. This'll be easier than expected.

# How to use (Kind of the same as the polymorphic one):

The CRYPTED_FUNC_SIZE must be the exact size of your new section ! You can use `size -d -A binaryname` to get it. You'll need to reference port and IP the same way you did with the polymorphic bin (`nc -l`, etc...).

     git clone https://github.com/PoCFrance/Whitecomet-Research.git
     cd PolyMetamorphic
     ./build.sh
     ./PoCrypt

Even though there is still a Makefile in the folder, we recommand not use it. It doesn't seems to work the way we want with `make` but works perfectly with a simple `gcc` line.


# How it works :

Our polymorphic binary process is as follows :

1. Open bin
2. Generate/Store new key
3. Decrypt section (memory and as string)
4. Crypt string and write as new binary
5. Exec. payload
6. Exit

Between step 3 and 4 we have clear data and can find and replace the according patterns. So we just call our metamorphic replacing string function as step 3.5.