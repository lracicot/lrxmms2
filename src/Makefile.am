## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(xmms2-client_CFLAGS) \
	$(XMMS2_CLIENT_CFLAGS) \
	$(XMMS2_CFLAGS) \
	$(GTK2_CFLAGS) 

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = lrxmms2

lrxmms2_SOURCES = \
	main.c \
	xmms2.c \
	xmms2.h \
	mainWindow.c \
	mainWindow.h \
	playback.c \
	playback.h \
	playlist.c \
	playlist.h \
	playlist_gtk_model.c \
	playlist_gtk_model.h \
	song.h

lrxmms2_LDFLAGS = 

lrxmms2_LDADD =  \
	$(xmms2-client_LIBS) \
	$(XMMS2_CLIENT_LIBS) \
	$(XMMS2_LIBS) \
	$(GTK2_LIBS)

