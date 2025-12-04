### More about the TFMX decoder in this library

First of all, this is not an emulator. No emulation of Amiga's CPU
and custom chips is performed. Potentially, versatile music player emulators
like [UADE](https://www.exotica.org.uk/wiki/UADE), which utilize original
and/or modified machine code player object files, are a good and promising
approach to handling a multitude of music formats. However, the additional
requirements to maintain a variety of machine code player object files and
a database of which custom player to choose for which input file is a major
undertaking and error-prone, too.

Secondly, this is not a complete implementation of the API of a typical
TFMX player object file either. Features such as but not limited to sending
signals to the API caller, playing sound effects, accepting external master
volume fading commands, playing note commands from the outside are not needed
when only trying to replay a TFMX file.

This is a barebone player that implements enough track commands, pattern
commands and macro commands as needed to parse and play files in TFMX v1.x,
TFMX Pro and TFMX 7V format. Particularly it's fun to listen to those tracks
that are not available as enhanced studio rearrangements or as quality-recordings
of the original audio on Commodore Amiga.

Youtube seemingly is crammed with retro-gaming and tribute videos including
music recordings, which sound wrong in some way or another. Sometimes entire
instruments or voices are missing. The Amiga's fixed stereo output of its
four channels to Left/Right/Right/Left and the muffled sound of the low-pass
filter applied on top of that isn't to everyone's liking either. Not
surprisingly, Amiga fans have built stereo-to-mono converters, switches
to turn off the filter, and multi-format music players.

The unfinished core of this player was written from scratch in assembly
language around 1991. With the help of the autographed package, the printed
manual and files that came with the commercial TFMX-editor ``Chris Hülsbeck's
Workstation``, which I had won in a sweepstake held by Demonware. I've sold
that package to a collector of rarities on eBay years later when I also parted
with related hardware.

If memory serves correctly, the TFMX-editor had trouble parsing game soundtrack
files ripped from games. The player object file that came with the editor was
tailored to the specific TFMX version, too. TFMX as used in games changed
often and introduced modifications as well as new sound macro commands.
Also, the computer musicians I knew during the early 90s showed
more interest in using Protracker, SIDmon, FutureComposer and alike. Those
editors were freely available, easier to use and felt less like a programmer's
editor.

The following is an example of a sound definition macro from the ``Quik & Silva``
soundtrack, similar to what is shown in the editor and in the printed handbook:

```
  0000 00 010000 DMAoff+Reset (stop sample & reset all)
  0001 02 00b43c SetBegin    xxxxxx   sample-startadress
  0002 03 000700 SetLen      ..xxxx   sample-length
  0003 0d 000014 Addvol+note xx/fe/xx note/CONST./volume
  0004 08 fa0000 AddNote     xx/xxxx  note/detune
  0005 01 000000 DMAon (start sample at selected begin)
  0006 04 000000 Wait        ..xxxx   count (VBI's)
  0007 19 000000 -------Set one shot sample-------------
  0008 14 000000 Wait key up ....xx   count (VBI's)
  0009 0f 0f0108 Envelope    xx/xx/xx speed/count/endvol
  000a 04 000008 Wait        ..xxxx   count (VBI's)
  000b 0f 010200 Envelope    xx/xx/xx speed/count/endvol
  000c 04 000000 Wait        ..xxxx   count (VBI's)
  000d 07 000000 -------------STOP----------------------
```

That is a simple scripting language indeed, and some commands can loop
(un)conditionally and branch to (and return from) other macros.

### TFMX 7V

Confirmed in game magazine interviews with either Jochen or Chris, the 7V mode
in TFMX, which targets one of Amiga Paula chip's four audio output channels
with the combined input of four virtual voices in order to play samples on
7 channels, was created by Jochen for his own TFMX and contributed to Chris'
TFMX. The file formats are vastly different, though.
