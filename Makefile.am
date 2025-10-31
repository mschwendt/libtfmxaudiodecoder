AUTOMAKE_OPTIONS = foreign

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = m4 images

SUBDIRS = src

dist-hook:
		@RM@ -f $(distdir)/src/Config.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libtfmxaudiodecoder.pc
