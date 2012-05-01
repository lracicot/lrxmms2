#ifndef __LRXMMS2_PLAYLIST_H__
#define __LRXMMS2_PLAYLIST_H__
#include "entities/playlist.h"

void get_current_playlist( gpointer connection, playlist* trackList);

void playlist_add( GtkWidget *widget,
                        gpointer   connection );
void playlist_remove( gpointer   connection, int id);

#endif