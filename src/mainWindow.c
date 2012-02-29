/*
 * mainWindow.c
 *
 * Copyright (C) 2012 - Louis Racicot <info@louisracicot.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <gtk/gtk.h>
#include "playback.h"
#include "playlist.h"
#include "playlist_gtk_model.h"
#include "entities/playlist.h"

enum
{
   TITLE_COLUMN,
   ARTIST_COLUMN,
   CURRENT_COLUMN,
   N_COLUMNS
};

static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    gtk_main_quit ();
    return FALSE;
}

// Close the program
static void destroy(GtkWidget* widget,
                    gpointer   data)
{
	gtk_main_quit ();
}

GtkWidget* new_mainWindow (gpointer* connection)
{
    GtkWidget *window;
	GtkWidget *button;
	GtkWidget *tree;
    GtkWidget *mainBox;
    GtkWidget *playbackControlBox;
    GtkWidget *playlistBox;
    GtkWidget *playlistControlBox;
	GtkWidget *scrolled_window;

	GtkTreeStore *store;
	GtkTreeViewColumn *column;
	GtkCellRenderer *renderer;
	playlist *trackList;
	trackList = malloc(sizeof(playlist));

	
	
	store = gtk_tree_store_new (N_COLUMNS,    // Total number of columns
                             G_TYPE_STRING,   // Song name
                             G_TYPE_STRING,   // Artist
                             G_TYPE_BOOLEAN); // Current?

	// Create the window
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "lrxmms2");
    g_signal_connect (window, "delete-event", G_CALLBACK (delete_event), NULL);
	g_signal_connect (window, "destroy",  G_CALLBACK(destroy), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    mainBox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), mainBox);
	
    playbackControlBox = gtk_hbutton_box_new  ();
	gtk_box_pack_start(GTK_BOX (mainBox), playbackControlBox, TRUE, TRUE, 0);
	
    playlistBox = gtk_hbox_new  (FALSE, 0);
	gtk_box_pack_start(GTK_BOX (mainBox), playlistBox, TRUE, TRUE, 0);
	
    playlistControlBox = gtk_vbutton_box_new  ();
	gtk_box_pack_start(GTK_BOX (playlistBox), playlistControlBox, TRUE, TRUE, 0);

	// Create the scroll for the playlist
	scrolled_window=gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_usize(scrolled_window, 250, 150);
	gtk_widget_show(scrolled_window);

    // Create PLAY button
    button = gtk_button_new_with_label ("Play");
    g_signal_connect (button, "clicked", G_CALLBACK (playback_play), (gpointer) connection);
    gtk_box_pack_start (GTK_BOX(playbackControlBox), button, TRUE, TRUE, 0);
    gtk_widget_show (button);
	
    // Create PAUSE button
    button = gtk_button_new_with_label ("Pause");
    g_signal_connect (button, "clicked", G_CALLBACK (playback_pause), (gpointer) connection);
    gtk_box_pack_start (GTK_BOX(playbackControlBox), button, TRUE, TRUE, 0);
    gtk_widget_show (button);

    // Create STOP button
    button = gtk_button_new_with_label ("Stop");
    g_signal_connect (button, "clicked", G_CALLBACK (playback_stop), (gpointer) connection);
    gtk_box_pack_start(GTK_BOX (playbackControlBox), button, TRUE, TRUE, 0);
    gtk_widget_show (button);
	
    // Create EXIT button
    button = gtk_button_new_with_label ("Exit");
	g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_box_pack_start(GTK_BOX (playbackControlBox), button, TRUE, TRUE, 0);
	gtk_widget_show (button);

	// Create the playlist ListView
	get_current_playlist(connection, trackList);

	getGtkTreePlaylist(connection, trackList, store);
	tree = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes ("Titre",
		                                               renderer,
		                                               "text", TITLE_COLUMN,
		                                               NULL);	
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);
	column = gtk_tree_view_column_new_with_attributes ("Durée",
		                                               renderer,
		                                               "text", ARTIST_COLUMN,
		                                               NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);
	gtk_scrolled_window_add_with_viewport( GTK_SCROLLED_WINDOW(scrolled_window),tree);
	
	gtk_box_pack_start(GTK_BOX (playlistBox), scrolled_window, TRUE, TRUE, 0);

	// Show everything
	gtk_widget_show (tree);
    gtk_widget_show (playbackControlBox);
    gtk_widget_show (playlistBox);
    gtk_widget_show (mainBox);

	return window;
}