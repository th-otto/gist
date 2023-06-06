# What is this?

These are (reconstructed) sources of the GISTDRVR.PRG found on
the orginal G.I.S.T (GI sound tool) disk, with the intention to
make them easier usable from C. Object files for older compilers
like Alcyon or Megamax-C are provided on the disk, but no sources,
and the object files are not easily usable (if at all) by modern
compilers like Pure-C or GCC.

All the contents are uploaded with permission of the author of G.I.S.T.


# Directory Structure

- orig:  
  The original sources of the driver.

- src:  
  The new version of the driver, along with a sample application
  (sndboard).

- gfa:  
  Same sample application as above, for GFA.

- disk:  
  Contents of the original G.I.S.T disk.

- bin/linux:  
  Prebuild binaries of tools used in the build process. These are
  essentially identical to the ones from the developer kit. They are
  only needed to verify compiling the original sources (in the orig/ folder)
  to an identical version of the driver.  
  Only tools for linux are provided here, if you need them for other
  systems, have a look at the bin folder of [tos1x](https://github.com/th-otto/tos1x).


# How to use it

For C, there are now essential 3 possibilities:

- Load the driver as external program. 
  This is accomplished by using the gistlib.c from the source directory,
  and setting EMBEDDED to 0.

- Compiled the driver into the executable.
  This is accomplished by using the gistlib.c from the source directory,
  and setting EMBEDDED to 1.

- Directly link the routines in your application.
  This is accomplished by compiling and linking sndsubs.c and sndint.S,
  and linking them to your executable.

The GFA version can currently only use the first method of the above
(however you could maybe adopt it to use something similar as method 2
by placing the driver into an inline).


# Notes

Some memebers of the sound structure currently have some cryptic names.
If you find out about the meaning of some of those, please let me know!
