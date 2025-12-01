EXTRA_DIST = Config.h.in

DISTCLEANFILES = Config.h

tfmxdecincludedir = $(includedir)
tfmxdecinclude_HEADERS = tfmxaudiodecoder.h

SUBDIRS = Chris Jochen

SOURCES = \
Decoder.cpp Decoder.h \
DecoderProxy.cpp DecoderProxy.h \
Config.h \
CRCLight.cpp CRCLight.h \
Dump.h Dump.cpp \
Filter.h Filter.cpp \
PaulaVoice.h PaulaVoice.cpp \
LamePaulaVoice.h LamePaulaVoice.cpp \
LamePaulaMixer.h LamePaulaMixer.cpp \
MyEndian.h \
MyTypes.h \
SmartPtr.h

lib_LTLIBRARIES = libtfmxaudiodecoder.la

libtfmxaudiodecoder_la_LIBADD = \
Chris/libtfmxch.la \
Jochen/libtfmxjh.la

libtfmxaudiodecoder_la_LDFLAGS = -version-info @LIBVERSION@ -no-undefined

libtfmxaudiodecoder_la_SOURCES = \
tfmxaudiodecoder.h \
tfmxaudiodecoder.cpp \
$(SOURCES)
