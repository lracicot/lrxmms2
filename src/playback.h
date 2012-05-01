#ifndef __LRXMMS2_PLAYBACK_H__
#define __LRXMMS2_PLAYBACK_H__

void playback_play( GtkWidget *widget,
                        gpointer   connection );

void playback_pause( GtkWidget *widget,
                        gpointer   connection );

void playback_toggleplay( GtkWidget *widget,
                          gpointer connection );

void playback_stop( GtkWidget *widget,
                        gpointer   connection );

void playback_prev( GtkWidget *widget,
                        gpointer   connection );

void playback_next( GtkWidget *widget,
                        gpointer   connection );

void playback_jump( GtkTreeView        *treeview,
                       GtkTreePath        *path,
                       GtkTreeViewColumn  *col,
                       gpointer   connection);
#endif