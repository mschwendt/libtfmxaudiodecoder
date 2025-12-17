### Faulty/damaged files (MD5 hash and filename)

Music data file (size 7875) is one byte too short (missing a 0x9C at the end) and thus is corrupting the
last sound macro offset. As a result, an instrument is not played. Only obvious,
if you know these ingame tunes from ``The Adventures of Quik & Silva``.

```
 efe7ca7a7598aa80c5fc5342c8f16908  Q&S-INGA.TFX
 010c7c61d537d4d3b961bf288c307f82  Q&S-INGA.SAM

 efe7ca7a7598aa80c5fc5342c8f16908  Quik And Silva - Ingame.tfx
 a7e3a6836311bdc97428672c2ca8222a  Quik And Silva - Ingame.sam

 efe7ca7a7598aa80c5fc5342c8f16908  mdat.Quik_And_Silva-Ingame
 a7e3a6836311bdc97428672c2ca8222a  smpl.Quik_And_Silva-Ingame
```


Header has been invalidated with a flood of 0x0d values, which breaks
all TFMX players that expect the space character after the "TFMX-SONG" tag.
The structure's two fields about compression have become invalid, too.
The sample data possibly are shifted by four bytes, which causes clearly
audible clicks:

```
 f46a01e4eae101d79af636a5b9015684  Apidya - Load.tfx
 ac09636d5b7ee6814b47d7e0eaa05417  Apidya - Load.sam
```
