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

GtkWidget *tree;

enum
{
   TITLE_COLUMN,
   ARTIST_COLUMN,
   ID_COLUMN,
   //LENGTH_COLUMN,
   CURRENT_COLUMN,
   N_COLUMNS
};

typedef struct
{
	gpointer* connection;
	int trackId;
	
} playlistParam;

/*typedef struct
{
	xmmsc_connection_t * connection;
	GtkWidget *container;
	GtkTreeStore *store;
	
} xmmsGtkConnector;*/

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

static void
remove_item(GtkWidget *widget, gpointer selection)
{
  GtkListStore *store;
  GtkTreeModel *model;
  GtkTreeIter  iter;


  store = GTK_LIST_STORE(gtk_tree_view_get_model(
      GTK_TREE_VIEW (widget)));
  model = gtk_tree_view_get_model (GTK_TREE_VIEW (widget));

  if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) 
      return;

  if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), 
      &model, &iter)) {
    gtk_list_store_remove(store, &iter);
  }
}

static void playlist_remove_selected(GtkWidget* widget,
                    gpointer   connection)
{
  GtkTreeSelection *selection;
  GtkTreeModel     *model;
  GtkTreeIter       iter;
  GtkListStore *store;

  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree));
  store = GTK_LIST_STORE(gtk_tree_view_get_model(
      GTK_TREE_VIEW (widget)));

  if (gtk_tree_selection_get_selected(selection, &model, &iter))
  {
    gint *id;
    gtk_tree_model_get (model, &iter, ID_COLUMN, &id, -1);

    //playlist_remove(connection, id);
	  gtk_list_store_remove(store, &iter);
	//remove_item(tree, selection);
	  
  }
  else
  {
    g_print ("no row selected.\n");
  }	
}

GtkWidget* new_mainWindow (gpointer* connection)
{
    GtkWidget *window;
	GtkWidget *button;
    GtkWidget *mainBox;
    GtkWidget *playbackControlBox;
    GtkWidget *playlistBox;
    GtkWidget *playlistControlBox;
	GtkWidget *scrolled_window;
	GtkTreeStore *store;
	GtkTreeViewColumn *column;
	GtkCellRenderer *renderer;
	playlist *trackList;
	playlistParam playlistAction;
	
	trackList = malloc(sizeof(playlist));

	
	
	store = gtk_tree_store_new (N_COLUMNS,    // Total number of columns
	                            G_TYPE_STRING,   // Song name
                             G_TYPE_STRING,   // Song name
                             G_TYPE_INT,   // Artist
                             G_TYPE_INT//,   // Artist
	                            ); 

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

	// Create the scroll for the playlist
	scrolled_window=gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_usize(scrolled_window, 250, 150);
	gtk_widget_show(scrolled_window);

    // Create PLAY button
    button = gtk_toggle_button_new_with_label ("Play");
    g_signal_connect (button, "clicked", G_CALLBACK (playback_toggleplay), (gpointer) connection);
    gtk_box_pack_start (GTK_BOX(playbackControlBox), button, TRUE, TRUE, 0);
    gtk_widget_show (button);
	
    /*// Create PAUSE button
    button = gtk_button_new_with_label ("Pause");
    g_signal_connect (button, "clicked", G_CALLBACK (playback_pause), (gpointer) connection);
    gtk_box_pack_start (GTK_BOX(playbackControlBox), button, TRUE, TRUE, 0);
    gtk_widget_show (button);*/

    // Create STOP button
    button = gtk_button_new_with_label ("Stop");
    g_signal_connect (button, "clicked", G_CALLBACK (playback_stop), (gpointer) connection);
    gtk_box_pack_start(GTK_BOX (playbackControlBox), button, TRUE, TRUE, 0);
    gtk_widget_show (button);

    // Create PREV button
    button = gtk_button_new_with_label ("<-");
    g_signal_connect (button, "clicked", G_CALLBACK (playback_prev), (gpointer) connection);
    gtk_box_pack_start(GTK_BOX (playbackControlBox), button, TRUE, TRUE, 0);
    gtk_widget_show (button);

    // Create NEXT button
    button = gtk_button_new_with_label ("->");
    g_signal_connect (button, "clicked", G_CALLBACK (playback_next), (gpointer) connection);
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
	column = gtk_tree_view_column_new_with_attributes ("Artiste",
		                                               renderer,
		                                               "text", ARTIST_COLUMN,
		                                               NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);
	g_signal_connect(tree, "row-activated", (GCallback) playback_jump, (gpointer) connection);
	gtk_scrolled_window_add_with_viewport( GTK_SCROLLED_WINDOW(scrolled_window),tree);
	
	gtk_box_pack_start(GTK_BOX (playlistBox), scrolled_window, TRUE, TRUE, 0);
	
    playlistControlBox = gtk_vbutton_box_new  ();
	gtk_box_pack_start(GTK_BOX (playlistBox), playlistControlBox, TRUE, TRUE, 0);
	
	
    // Create Add button
    button = gtk_button_new_with_label ("+");
	//g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_box_pack_start(GTK_BOX (playlistControlBox), button, TRUE, TRUE, 0);
	gtk_widget_show (button);

    /*// Create TEST button
    button = gtk_button_new_with_label ("Test");
    g_signal_connect (button, "clicked", G_CALLBACK (playback_test), (gpointer) connection);
    gtk_box_pack_start(GTK_BOX (playbackControlBox), button, TRUE, TRUE, 0);
    gtk_widget_show (button);*/
	
    // Create Remove button
    button = gtk_button_new_with_label ("-");
    g_signal_connect (button, "clicked", G_CALLBACK (playlist_remove_selected), (gpointer) connection);
    gtk_box_pack_start(GTK_BOX (playlistControlBox), button, TRUE, TRUE, 0);
	gtk_widget_show (button);

	// Show everything
	gtk_widget_show (tree);
    gtk_widget_show (playbackControlBox);
    gtk_widget_show (playlistControlBox);
    gtk_widget_show (playlistBox);
    gtk_widget_show (mainBox);

	return window;
}