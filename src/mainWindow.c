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
	ID_COLUMN,
	N_COLUMNS,
	ARTIST_COLUMN,
	CURRENT_COLUMN
};

GtkWidget *window;
GtkWidget *list;
GtkWidget *play;

static void playback_jump_and_toggle (GtkTreeView        *list,
                       GtkTreePath        *path,
                       GtkTreeViewColumn  *col,
                       gpointer   connection)
{
	gtk_toggle_button_set_active(play, TRUE);
	playback_jump(list, path, col, connection);
}

static void remove_item(GtkWidget *widget, gpointer selection)
{
  GtkListStore *store;
  GtkTreeModel *model;
  GtkTreeIter  iter;


  store = GTK_LIST_STORE(gtk_tree_view_get_model(
      GTK_TREE_VIEW (list)));
  model = gtk_tree_view_get_model (GTK_TREE_VIEW (list));

  if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) 
      return;

  if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), 
      &model, &iter)) {
    gtk_list_store_remove(store, &iter);
  }
}

static void append_item(GtkListStore *store, track* trackInfo, int id)
{
  GtkTreeIter  iter;

  gtk_list_store_append(store, &iter);
  gtk_list_store_set(store, &iter,
                     ID_COLUMN, id, TITLE_COLUMN, trackInfo->title, -1);
}

static void init_list(GtkWidget *list, gpointer* connection)
{

  GtkCellRenderer    *renderer;
  GtkTreeViewColumn  *column;
  GtkListStore       *store;
  playlist 			 *trackList;
  trackList = malloc(sizeof(playlist));

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes("List Item",
          renderer, "text", TITLE_COLUMN, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW (list), column);

  store = gtk_list_store_new (N_COLUMNS, G_TYPE_STRING, G_TYPE_INT);

	// Create the playlist ListView
  get_current_playlist(connection, trackList);

  getGtkTreePlaylist((xmmsc_connection_t*)connection, trackList, store);
  gtk_tree_view_set_model(GTK_TREE_VIEW (list), 
      GTK_TREE_MODEL(store));
	
	g_signal_connect(list, "row-activated", (GCallback) playback_jump_and_toggle, (gpointer) connection);

  g_object_unref(store);
}

static void playlist_remove_selected(GtkWidget* widget,
                    gpointer   connection)
{
	GtkTreeSelection *selection;
  GtkTreeModel     *model;
  GtkTreeIter       iter;

  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
  if (gtk_tree_selection_get_selected(selection, &model, &iter))
  {
    gint *id;

    gtk_tree_model_get (model, &iter, 1, &id, -1);

    playlist_remove(connection, id);
	remove_item(list, selection);
  }
  else
  {
    g_print ("no row selected.\n");
  }
}

static void playlist_add_selected(GtkWidget* widget,
                    gpointer   connection)
{
	GtkWidget *dialog;
	
	dialog = gtk_file_chooser_dialog_new ("Open File",
						  window,
						  GTK_FILE_CHOOSER_ACTION_OPEN,
						  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
						  GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
						  NULL);
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
	  {
		char* filename;
		char* protocol = "file://";
		char* path = NULL;
		  
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));

		path = malloc((strlen(filename)+strlen(protocol)) * sizeof(char));
		path[0] = NULL;
		strcat(path, protocol);
		strcat(path, filename);
		  
		xmmsc_result_t *result = xmmsc_playlist_add_url(connection, NULL, path);
		xmmsc_result_wait (result);
		free (path);
		  
		  init_list(list, connection);
	  }
	gtk_widget_destroy (dialog);
}

GtkWidget* new_mainWindow (gpointer* connection)
{
	GtkWidget *sw;

	GtkWidget *stop;
	GtkWidget *previous;
	GtkWidget *next;
	GtkWidget *add;
	GtkWidget *remove;

    GtkWidget *mainBox;
    GtkWidget *playbackControlBox;
    GtkWidget *playlistBox;
    GtkWidget *playlistControlBox;

    mainBox = gtk_vbox_new (FALSE, 0);
    playbackControlBox = gtk_hbutton_box_new  ();
    playlistBox = gtk_hbox_new  (FALSE, 0);
    playlistControlBox = gtk_vbutton_box_new  ();

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	sw = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_usize(sw, 250, 150);
	list = gtk_tree_view_new();

	gtk_window_set_title (GTK_WINDOW (window), "lrxmms2");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	gtk_widget_set_size_request (window, 370, 270);

	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(sw),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW(sw),
		GTK_SHADOW_ETCHED_IN);

	gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (list), FALSE);

	play = gtk_toggle_button_new_with_label("Play");
	stop = gtk_button_new_with_label("Stop");
	previous = gtk_button_new_with_label("Previous");
	next = gtk_button_new_with_label("Next");
	add = gtk_button_new_with_label("+");
	remove = gtk_button_new_with_label("-");

	gtk_box_pack_start(GTK_BOX(playbackControlBox), play, FALSE, TRUE, 3);
	gtk_box_pack_start(GTK_BOX(playbackControlBox), stop, FALSE, TRUE, 3);
	gtk_box_pack_start(GTK_BOX(playbackControlBox), previous, FALSE, TRUE, 3);
	gtk_box_pack_start(GTK_BOX(playbackControlBox), next, FALSE, TRUE, 3);

	gtk_box_pack_start(GTK_BOX(playlistBox), sw, TRUE, TRUE, 5);
	
	gtk_box_pack_start(GTK_BOX(playlistControlBox), add, FALSE, TRUE, 3);
	gtk_box_pack_start(GTK_BOX(playlistControlBox), remove, FALSE, TRUE, 3);

	gtk_container_add(GTK_CONTAINER (sw), list);
    gtk_container_add (GTK_CONTAINER (window), mainBox);
	gtk_box_pack_start(GTK_BOX (mainBox), playbackControlBox, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX (mainBox), playlistBox, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX (playlistBox), playlistControlBox, TRUE, TRUE, 0);

	init_list(list, connection);

	g_signal_connect(G_OBJECT(add), "clicked",
	  G_CALLBACK(playlist_add_selected), connection);

	g_signal_connect(G_OBJECT(remove), "clicked",
	  G_CALLBACK(playlist_remove_selected), connection);

	g_signal_connect (G_OBJECT(play), "clicked", 
	  G_CALLBACK (playback_toggleplay), (gpointer) connection);

    g_signal_connect (G_OBJECT(stop), "clicked",
      G_CALLBACK (playback_stop), (gpointer) connection);
	
    g_signal_connect (G_OBJECT(next), "clicked",
      G_CALLBACK (playback_next), (gpointer) connection);
		
    g_signal_connect (G_OBJECT(previous), "clicked",
      G_CALLBACK (playback_prev), (gpointer) connection);

	g_signal_connect (G_OBJECT (window), "destroy",
	  G_CALLBACK(gtk_main_quit), NULL);

	return window;
}