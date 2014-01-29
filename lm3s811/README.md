lm3s811
=======

Linux build and programming environment for the Stellaris LM3S811 evaluation
board

Setup
-----

1) Download and extract the GNU toolchain to the current directory (if you
   download a different version, you need to adjust the build.env file
   accordingly):
   $ wget https://launchpad.net/gcc-arm-embedded/4.8/4.8-2013-q4-major/+download/gcc-arm-none-eabi-4_8-2013q4-20131204-linux.tar.bz2
   $ tar xjvf gcc-arm-none-eabi-4_8-2013q4-20131204-linux.tar.bz2

2) Install openocd. For Ubuntu/Debian, it's:
   $ apt-get install openocd

3) Source the build.env file:
   $ . build.env


Stellaris Examples
----------------------------

1) Build the Stellaris examples:
   $ make -C stellaris

2) Flash the eval board with one of the examples:
   $ IMAGE=$(readlink -e stellaris/boards/ek-lm3s811/hello/gcc/hello.bin)
   $ openocd -f /usr/share/openocd/scripts/board/ek-lm3s811.cfg \
         -f build/lm3s811_flash.cfg -c "lm3s811_flash $IMAGE"
