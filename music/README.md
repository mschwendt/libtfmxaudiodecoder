This is just a dumping ground for modules that have been repaired.  
More details in [README_BAD.md](../README_BAD.md) and within the library's source code.

---

Instructions to repair these:

#### Wings of Death (ST)

```
$ md5sum SOG_WingsOfDeathST.lzx
885722b641ec55ecd9b27e0b007c98bb  SOG_WingsOfDeathST.lzx
$ unlzx SOG_WingsOfDeathST.lzx
Extracting "SOG.WingsOfDeathST outro"... crc good
Extracting "SOG.WingsOfDeathST intro"... crc good
$ md5sum SOG.WingsOfDeathST\ intro
0a2da84b25a5fd128f50f773a0739378  SOG.WingsOfDeathST intro
$ bspatch SOG.WingsOfDeathST\ intro SOG.WingsOfDeathST\ intro_repaired SOG.WingsOfDeathST\ intro.bsdiff
$ md5sum SOG.WingsOfDeathST\ intro_repaired 
58c5a79885c1068e3e11e077491f0b1c  SOG.WingsOfDeathST intro_repaired
```

#### Grand Monster Slam (ST)

```
$ md5sum SOG_GrandMonsterSlamST.lzx 
c5574e1d01d22b1dc78779448dfcc010  SOG_GrandMonsterSlamST.lzx
$ unlzx SOG_GrandMonsterSlamST.lzx 
Extracting "SOG.GrandSlamMonsterST"... crc good
$ md5sum SOG.GrandSlamMonsterST
5051058f1d0d77db04bf86d65ebf738b  SOG.GrandSlamMonsterST
$ bspatch SOG.GrandSlamMonsterST SOG.GrandMonsterSlamST_repaired SOG.GrandSlamMonsterST.bsdiff
$ md5sum SOG.GrandMonsterSlamST_repaired 
3e44767bb77e309a328edcb482ee51b2  SOG.GrandMonsterSlamST_repaired
```

#### Hollywood Poker Pro

```
$ md5sum DNS_HollywoodPoker.lzx
d46a10746a5b14e5f0a98812834f472d  DNS_HollywoodPoker.lzx
...
(run unlzx, unar or any tool to uncompress the .lzx archive)
...
$ bspatch DNS.HollywoodPokerPro\ title DNS.HollywoodPokerPro\ title_repaired DNS.HollywoodPokerPro\ title.bsdiff
$ md5sum 'DNS.HollywoodPokerPro title_repaired'
610c74d10a0a10029f281f03486516d2  DNS.HollywoodPokerPro title_repaired
```

#### Z-Out (level 2)

There are different rips of this with different file names, so this applies
only to an MDAT file with the same MD5 checksum:

```
37b406445ed1eb805f152b8a690092c1  mdat.z-out level 2
37b406445ed1eb805f152b8a690092c1  MDAT.Z-Out 5
```

After applying the bsdiff, the checksum of the repaired MDAT becomes:

```
64252c913897f0128806a7abc52b0ce5  mdat.z-out level 2_repaired
```
