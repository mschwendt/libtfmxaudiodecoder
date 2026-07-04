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

### Rundown of TFMX macro commands

```
#   Name             v1.5   v2.2    Pro
-----------------------------------------
00  DMAoff+Reset       X      X      X
01  DMAon              X      X      X
02  SetBegin           X      X      X
03  SetLen             X      X      X
04  Wait               X      X      X
05  Loop               X      X      X
06  Cont               X      X      X
07  Stop               X      X      X
08  AddNote            X      X      X
09  SetNote            X      X      X
0A  Reset              X      X      X
0B  Portamento         X      X      X
0C  Vibrato            X      X      X
0D  AddVolume          X
0D  Addvol+note               X      X     (!)
0E  SetVolume          X      X      X
0F  Envelope           X      X      X
10  LoopKeyUp          X      X      X
11  AddBegin           X      X
11  AddBegin+count                   X     (!)
12  AddLen             X      X      X
13  DMAoff no clear    X      X      X
14  WaitKeyUp          X      X      X
15  Goto               X      X      X
16  Return             X      X      X
17  SetPeriod          X      X      X
18  SampleLoop         X      X      X
19  OneShotSample      X      X      X
1A  WaitOnDMA                 X      X
1B  RandomPlay                X      X
1C  SplitKey                  X      X
1D  SplitVolume               X      X
1E  Addvol+note               X            (!)
1E  RandomMask                       X
1F  SetPrevNote                      X
1F  AddChannel         -      -      -
20  SubChannel         -      -      -
20  Signal             -      -      -
21  PlayMacro                        X
22  SID setbeg                       X
23  SID setlen                       X
24  SID op3 ofs                      X
25  SID op3 frq                      X
26  SID op2 ofs                      X
27  SID op2 frq                      X
28  SID op1                          X
29  SID stop                         X
30  BranchIfSame                     X
31  Key up                           X
```

For consistency, the names of macros 0x22 to 0x29 have been copied from
player object files that have been created for a heavily modified
TFMX-editor v1.6. Those macros have not been available in v2.2.

The names of macros 0x30 and 0x31 have been made up for this library and
its debug output.

It could be said that Turrican soundtrack is closest to TFMX v2, but yet
incompatible with TFMX Pro because it requires v1/v2 non-scaled vibrato/portamento.

The family of player variants known as TFMX Pro is incompatible with v1/v2 because
of various implementation details that differ.
