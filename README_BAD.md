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
 58c5a79885c1068e3e11e077491f0b1c  SOG.WingsOfDeathST intro - repaired
```
TODO: Get the repaired file published somewhere.

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
 3e44767bb77e309a328edcb482ee51b2  SOG.GrandSlamMonsterST_repaired
```
TODO: Get the repaired file published somewhere.
