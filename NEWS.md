Trimmed release notes that mention specific soundtracks:

- Implement the very rare macro command $31 for ``Turrican III``.

- Implement the very rare macro command $30 for ``Gem'Z``.

- Fix for ``Turrican II loader`` jingle. Curiously, there are two versions of it in music collections. The original data, sometimes called **unfixed**. And a sometimes so-called **fixed** version where two macro scripts have been modified, possibly as to make them compatible with some TFMX Pro player. We now support both versions of that loading music.

- Bonus fix for ``A Prehistoric Tale (music4)``. Where the original soundtrack glitches because its player applies pattern transpose immediately and thus prematurely (in corner-cases), we fix that on-the-fly.

- Support loading ``Einmal Kanzler sein`` and its single "smpl.set" file. Also look for "SMPL.set" since that naming scheme is found in documentation.

- ``Sledge Hammer One`` (aka ``Hammer One``) by Ern0 once more: Eliminate subsong at step 0, which isn't inactive but doesn't play anything either. Song table is wrecked!

- ``Bundesliga Manager HATTRICK`` (aka ``BMHattrick``)  features only a single title theme using 7V mode. Invalidate the second song, since as a fragment of the title theme it is missing the track commands to initialize 7V mode.

- Fix ``Z-Out`` ingame level 2 on-the-fly. Only the original version is affected (some edited/repaired versions are not). Also mark the entire soundtrack as a special variant of TFMX with some features newer than v2.2 (e.g. scaled vibrato/portamento) but strictly requiring the older channel on/off implementation for some of the instrument macro scripts.

- Flag as TFMX v1 some more modules after skimming over their player machine code: ``Grand Monster Slam``, ``Oxxonian``, ``X-Out``, ``Circus Attractions``, ``Gordian Tomb``. Whether a module requires old-style features like non-scaled vibrato/portamento cannot be detected, because there is no hint about it in the music data.

- Fix ``Hollywood Poker Pro`` title theme on-the-fly. Two instruments by mistake specify sample repeat length as number of bytes instead of number of words.  ([More...](README_BAD.md))

- Add a ``Dynamic Synthesizer`` decoder, although only three soundtracks have been created with it before the first music made in TFMX format: Hollywood Poker Pro, Starball and PTC ([More...](src/Chris/DNS/README.md))

- Blacklist ``R-Type`` title theme, if its sample file doesn't pass a basic check.  If your private collection is affected, fetch a repaired copy from e.g. Modland.

- Fix bad clicks in ``Danubius Replay`` (aka ``Gitar``) by Ern0 on-the-fly  by centering over 80% of the sample data properly around signed zero. An unusual fix for sure, but the original sample data are messed up.

- Click removal for ``Turrican II level 4`` via updates to the play loop plus changes to macro commands. These clicks also exist in recordings made with DeliTracker and Eagleplayer.

- Flag ``Turrican`` soundtrack as a TFMX v1 variant.

- Fix a long standing glitch that caused sporadic gaps of 20 ms with some ``Masterblazer`` tracks.

- Fix a typo in TFMX v1 portamento. Affects ``R-Type``, for example! 

- Flag ``R-Type title`` as a TFMX v1 variant.

- Flag ``Rock'n'Roll`` intro theme as TFMX v1.

- Flag several music files by Ern0 as a TFMX v1 variant.

- Fix ``Sledge Hammer One`` by Ern0 on-the-fly. Song table is wrecked.

- Fix ``Puzzy`` by Ern0 on-the-fly as to enable both songs.

- Blacklist ``mdat.blade of destiny - titel (7ch)`` because it is **fubar**.

- Refactor the main player loop as to support different execution order. Flag ``Turrican II`` and ``Quik'n'Silva`` soundtracks accordingly.

- Fix vibrato strength for the Hippel TFMX player variant that can toggle vibrato half-speed mode via the vibrato speed parameter. Curiously, affected is the original ingame soundtrack from ``Wings of Death``, which requires a player with TFMX vibrato instead of COSO vibrato. Potentially affecting some other files, too!

- Fix ``astaroth4.hipc`` and ``shaolin ingame 5.hipc`` which have slipped under the radar (since version 1.0.0 actually, which is quite embarrasing, isn't it?). They are in TFMX COSO format but use TFMX portamento, not COSO portamento. The code to handle them has been there all the time but wasn't active. The converted files in Future Composer format were not affected because of using FC's different portamento parameters.

- Disable Track Mute for ``Software Manager - Titel`` and ``BiFi Adventure 2 - Ongame``. Track Mute can't be    disabled by default, because ``Logical`` ingame songs require it (or an alternative implementation) as to turn off track 8.
- Improve detection of valid songs. ``Oxygen`` and ``Flying world`` by Erno work now.

- Fix playback of ``Hard'n'Heavy`` title theme. Specifically the drum roll  that is played also at the start of subsong 2.

  * It has been reported that in many if not most of the Amiga game soundtrack videos on Youtube it doesn't sound correct, and thus they are misleading. Unless the recording of the music was done by running the game. In other cases possibly a wrong TFMX music player was used either on Amiga or in an emulator. The sound module strictly requires old TFMX v1 features.
   
- Support ``Tony & Friends in Kellogg's Land`` (PC), which incorrectly/accidentally has converted three 32-bit offsets from big-endian to little-endian encoding while all other values remain big-endian

- Special support for Atari ST to Amiga converted Hippel TFMX files / needed for ``Wings of Death`` (ST) and ``Grand Monster Slam`` (ST) as released by the Wanted Team / also see file [README_BAD.md](README_BAD.md#wings-of-death-st)
