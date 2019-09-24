# md-pong
A simple example Mega Drive game (pong) built using SGDK

## Build instructions

After setting up a local toolchain and SDK, simply reference the Makefile provided by gendev:

```
    $ git clone https://github.com/dgrubb/md-pong && cd md-pong
    $ make -f $GENDEV/sgdk/mkfiles/makefile.gen clean all

```

## Build environment

Putting in place a suitable SDK and toolchain has a few nuances. The following 
steps are those I used on Arch to utilise [SGDK (Sega Genesis Development Kit)](https://github.com/Stephane-D/SGDK) and
 the [gendev toolchain builder](https://github.com/kubilus1/gendev). While my test distro was Arch these steps should 
also be roughly applicable to other distributions such as Debian/Ubuntu.

1. Install the pre-requisite packages: git build-essential texinfo curl wget unzip openjdk-8-jdk
2. Checkout *gendev* (SGDK will be automatically checked out later in the process), assuming a "Projects" directory exists:

```
    $ git clone https://github.com/kubilus1/gendev ~/Projects
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
