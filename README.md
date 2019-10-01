# md-pong
A simple example Mega Drive game (pong) built using SGDK

## Build instructions

After setting up a local toolchain and SDK, simply reference the Makefile provided by gendev:

```
    $ git clone https://github.com/dgrubb/md-pong && cd md-pong
    $ make -f $GENDEV/sgdk/mkfiles/makefile.gen clean all

```

The result will be a binary ROM image suitable for loading directly into an emulator:

```
    $ gens out/rom.bin
```

## Image resources

The Mega Drive colour palette is a little limited: nine colours per palette, with up to four palettes. 
The rescomp tool, which is part of SGDK, can convert oridinary PNGs to title data but has some strict 
requirements reflecting the restrictions of the Mega Drive VDP. I've had reasonable success with rescomp 
by first pre-processing PNGs to a suitable palette and bit-depth (requires ImageMagick installed):

```
    $ convert input_image.png -alpha off -type palette -colors 9 PNG8:output_image.png
```

## Build environment

Putting in place a suitable SDK and toolchain has a few nuances. The following 
steps are those I used on Arch to utilise [SGDK (Sega Genesis Development Kit)](https://github.com/Stephane-D/SGDK) and
 the [gendev toolchain builder](https://github.com/kubilus1/gendev). While my test distro was Arch these steps should 
also be roughly applicable to other distributions such as Debian/Ubuntu.

1. Install the pre-requisite packages: git build-essential texinfo curl wget unzip openjdk-8-jdk
2. Checkout *gendev* (SGDK will be automatically checked out later in the process), assuming a "Projects" directory exists:

```
    $ cd ~/Projects
    $ git clone https://github.com/kubilus1/gendev
```
3. Build the mk68 toolchain and binutils:

```
    $ cd ~/Projects/gendev && make
```

4. Create an installation location for the toolchain. Typically, this is /opt/gendev:

```
    $ cd /opt
    $ sudo mkdir gendev && sudo chown $USER:$USER gendev
```
5. Export the install location to your local environment and install. This step consists of copying 
the compiled objects to /opt/gendev and writing to your local environment scripts to ensure $GENDEV is 
always in your path:

```
    $ cd ~/Projects/gendev
    $ GENDEV=/opt/gendev make install
```

6. Profit.
