### More about file naming schemes

In short, it's a mess!

Since the Commodore Amiga didn't enforce file name extensions most of the time,
its users could name files more freely. Copying or downloading a file
from Amiga to a modern PC can confuse the Windows-style assignment of
file name extensions to file types. It can also affect audio players, which
assign specific plugins only to files with specific file name extensions.

Furthermore, some of the music comes as a pair of files (a music data file
plus a separate samples file), if it has not been converted into a single-file
format, e.g.:

    foo.mdat + foo.smpl
    bar.tfx + bar.sam

In case it is the original file naming style from Commodore Amiga, where
the file type name extension was a prefix,

    mdat.foo + smpl.foo
    MDAT.bar + SMPL.bar

it is strongly recommended to rename your files and give them Windows PC-style
extensions instead. For example, ``.tfx`` and ``.sam`` is a good compromise
for TFMX ``mdat.`` and ``smpl.`` files. An audio player supporting TFMX
should be able to load ``.tfx`` files.

#### Extensions & prefixes

There is some overlap/redundancy. These file naming schemes are about the same file types:

 - ``SOG.``,  ``HIP.``, ``.hip``, ``.sog`` --> Hippel TFMX
 - ``SOC.``,``HIPC.``, ``.hipc``, ``.soc`` --> compressed Hippel TFMX
 - ``S7G.``, ``HIP7.`` --> 7-voices Hippel TFMX
 - ``MDAT.``, ``.mdat``, ``.tfx`` --> Huelsbeck TFMX music data
 - ``.tfm``, ``.tfmx`` --> Huelsbeck TFMX single-file formats
 - ``SMPL.``, ``.smpl``, ``.sam`` --> Huelsbeck TFMX sample data

And for Future Composer, it can be literally anything not limited to:

 - ``.fc``, ``.FC14``, ``.fc4``, ``.fc13``, ``.smod``

It is highly recommended to prefer ``.fc`` for all FC files.

Last but not least,

 - ``DNS.``, ``dns.`` --> Dynamic Synthesizer music data
 - ``SMP.``, ``smp.`` --> Dynamic Synthesizer sample data

shows how inconsistent these naming schemes are.
