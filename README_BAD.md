# Faulty/damaged files (MD5 hash and filename)


#### The Adventures of Quik & Silva

Music data file (size 7875) is one byte too short (missing a 0x9C at the end) and thus is corrupting the
last sound macro offset. As a result, an instrument is not played. Only obvious,
if you know these ingame tunes.

```
 efe7ca7a7598aa80c5fc5342c8f16908  Q&S-INGA.TFX
 010c7c61d537d4d3b961bf288c307f82  Q&S-INGA.SAM

 efe7ca7a7598aa80c5fc5342c8f16908  Quik And Silva - Ingame.tfx
 a7e3a6836311bdc97428672c2ca8222a  Quik And Silva - Ingame.sam

 efe7ca7a7598aa80c5fc5342c8f16908  mdat.Quik_And_Silva-Ingame
 a7e3a6836311bdc97428672c2ca8222a  smpl.Quik_And_Silva-Ingame
```

---

#### Apidya loader

Header has been invalidated with a flood of 0x0d values, which breaks
all TFMX players that expect the space character after the "TFMX-SONG" tag.
The structure's two fields about compression have become invalid, too.
The sample data possibly are shifted by four bytes, which causes clearly
audible clicks:

```
 f46a01e4eae101d79af636a5b9015684  Apidya - Load.tfx
 ac09636d5b7ee6814b47d7e0eaa05417  Apidya - Load.sam
```

---

#### Wings of Death ST

The Atari ST to Amiga conversion of ``Wings of Death`` as found on the
Wanted Team page of example files raises doubts. It is prepended with
the original machine code player from Wings of Death on Amiga, which is
not the right one to replay it, because higher Amiga Paula frequencies are
needed than what is supported by the array of periods within that player.
Furthermore, compared with the original Atari ST music data, the
sequencer's track table has been modified to transpose some patters by
three octaves, which sounds bad:

```
 0a2da84b25a5fd128f50f773a0739378  SOG.WingsOfDeathST intro
 SOG_WingsOfDeathST.lzx (218914 bytes) - all modules from the game "Wings Of Death" (Atari ST version).
```

While looking into it and discussing it, the author of that file suddenly
reverted the transposition. The resulting file is exactly the Atari ST music
data except for sample data converted from unsigned to signed. There is special
support for the repaired file in libtfmxaudiodecoder **newer than 1.0.1** to
play it without sounding bad. The repaired file's MD5 fingerprint is:

```
 58c5a79885c1068e3e11e077491f0b1c  SOG.WingsOfDeathST intro_repaired
```

---

#### Grand Monster Slam ST

The Atari ST to Amiga conversion of ``Grand Monster Slam`` as found on the
Wanted Team page of example files plays one PING sound in a loop, which
leads to a few erratic sounds during playback, and which is wrong compared
with Chris Hülsbeck's original melody. Examining the Atari ST data, actually
three samples with length null are meant to be played in one-shot mode.

```
 5051058f1d0d77db04bf86d65ebf738b  SOG.GrandSlamMonsterST
```

There is special support for that file in libtfmxaudiodecoder **newer than 1.0.1**,
which fixes the PING and the two other sounds on-the-fly while loading the music file. If
reparing the file, its MD5 fingerprint becomes:

```
 3e44767bb77e309a328edcb482ee51b2  SOG.GrandMonsterSlamST_repaired
```

---

#### R-Type

This file in the Chris Huelsbeck folder on Modland has been bad until
2026-06-04, because the sample data are not correct (the first 192 bytes
are missing).

```
818990ee9936728321ed334654136d68  smpl.r-type
```

A good rip of the music is provided by the Wanted Team, for example.
On Modland, the file has been replaced, too, so redownload it if your
copy is older.

---

#### Turrican III

A truncated rip of ``Turrican III - level 5`` (aka world 5) is offered for download
in some places with varying file names, possibly as a copy from the so-called
Sloppy collection. Several offsets to instrument macro scripts are missing, and
while that isn't anything that crashes the decoder, those files are bad.

```
357dc0be804c7e97f35f2c1a0d24a821  mdat.t3-lvl5
357dc0be804c7e97f35f2c1a0d24a821  T3-LVL5.TFX
```

Good rips of that are available on e.g. Modland, ExoticA, Wanted Team's page.

---

#### MDAT.Factor5 / Turrican III

Unmodified, it is not a valid TFMX song. Offset to patterns and offset to macros are the same, which makes no sense:

```
000001d0  00 00 02 18 00 00 04 20  00 00 04 20 00 00 00 00  |....... ... ....|
                            ^^ ^^        ^^ ^^
```

Track table at 0x218 is empty:

```
00000218  ff 00 ff 00 ff 00 ff 00  ff 00 ff 00 ff 00 ff 00  |................|
```

There are some unreferenced bytes at 0x200-0x218, which may have been part
of some pattern at some point, but it's not a complete pattern anymore. And
instrument number 0x10 exceeds the total number of 8 macro scripts in the file.
Conclusively, it is likely that external code run by the game while
displaying the Factor 5 intro screen uses this pair of MDAT+SMPL to
trigger SFX.

---

#### Blade of Destiny - title (7ch)

This file in the Rudolf Stember folder on Modland is invalid, because it's damaged
beyond repair.

```
7e833022c3aa3c8072a9d930008b3558  mdat.blade of destiny - titel (7ch)
```

---

#### Hanse

This file in the Rudolf Stember folder on Modland is invalid, because it's truncated and doesn't make any sense.

```
0346dbc2b5aef88598adca25c31b5c5c  mdat.hanse-ascon
```

Offsets to track table at 0x200, pattern offsets at 0x218 and macro offsets at 0x21c:

```
000001d0  00 00 02 00 00 00 02 18  00 00 02 1c 00 00 00 00  |................|
                ^^ ^^       ^^ ^^        ^^ ^^
```

Yet the file is just 540 bytes short (= 0x21c), so the macro offsets at 0x21c
are missing, and no macro scripts exist within the file. Furthermore,
the track table points at a default TFMX **empty pattern** only:

```
Track step #0:
00000200  00 00 ff 00 ff 00 ff 00  ff 00 ff 00 ff 00 ff 00  |................|
          ^^

Pattern #0:
00000210  f4 00 00 00 f0 00 00 00  00 00 02 10              |............|
          ^^ ^^ ^^ ^^ ^^ ^^ ^^ ^^
```

---

#### Future Composer modules

 * The soundtrack modules from the game ``Chambers of Shaolin`` as included
with Future Composer v1.2 and v1.3 in SMOD format are broken (since their
conversion from TFMX has introduced mistakes), but have been copied into
many module collections. Repaired files have been merged at [Modland](https://modland.com/pub/modules/Future%20Composer%201.3/Jochen%20Hippel/).
Alternatively prefer the original soundtrack in Hippel's TFMX format.

 * ``wassermu.hipc`` (short for Wassermusik) in compressed TFMX format
raises doubts. It is Chambers of Shaolin "ingame 1" aka "Test of Balance",
but with some added/restored patterns playing on voice 4. Strangely, one
of the instruments is broken compared with the original TFMX version (and
also the FC conversion).

 * ``Dreamcave.hipc`` with missing sample data in some module collections
is a duplicate of ``Amberstar (12).hipc``. Sometimes the samples are found
in a separate file named "hipc.samp", in other cases the separate file is
named "smp.set" but is stored in a different path. Searching for it and
loading it would not be worthwhile. Especially not since it is a duplicate.

---

#### Hollywood Poker Pro

Samples 2 and 15 of the title theme by mistake define repeat length in number
of bytes instead of number of words, advancing into the next sample area
and causing minor but audible artefacts. If loading the title theme into
libtfmxaudiodecoder **newer than 1.0.9** those two sample definitions are
fixed on-the-fly. Alternatively, a bsdiff file is provided in the source
repository's music folder.
