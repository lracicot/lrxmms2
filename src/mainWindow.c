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

enum
{
   TITLE_COLUMN,
   LENGTH_COLUMN,
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
    GtkWidget *box1;

	GtkTreeStore *store;
	GtkTreeViewColumn *column;
	GtkCellRenderer *renderer;

	// Create the window
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "lrxmms2");
    g_signal_connect (window, "delete-event", G_CALLBACK (delete_event), NULL);
	g_signal_connect (window, "destroy",  G_CALLBACK (destroy), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    box1 = gtk_hbox_new (FALSE, 0);

    gtk_container_add (GTK_CONTAINER (window), box1);

    // Create PLAY button
    button = gtk_button_new_with_label ("Play");
    g_signal_connect (button, "clicked", G_CALLBACK (playback_play), (gpointer) connection);
    gtk_box_pack_start (GTK_BOX(box1), button, TRUE, TRUE, 0);
    gtk_widget_show (button);
	
    // Create PAUSE button
    button = gtk_button_new_with_label ("Pause");
    g_signal_connect (button, "clicked", G_CALLBACK (playback_pause), (gpointer) connection);
    gtk_box_pack_start (GTK_BOX(box1), button, TRUE, TRUE, 0);
    gtk_widget_show (button);

    // Create STOP button
    button = gtk_button_new_with_label ("Stop");
    g_signal_connect (button, "clicked", G_CALLBACK (playback_stop), (gpointer) connection);
    gtk_box_pack_start(GTK_BOX (box1), button, TRUE, TRUE, 0);
    gtk_widget_show (button);
	
    // Create EXIT button
    button = gtk_button_new_with_label ("Exit");
	g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_box_pack_start(GTK_BOX (box1), button, TRUE, TRUE, 0);
	gtk_widget_show (button);

	// Create the playlist ListView
	store = getGtkTreeStore();
	tree = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes ("Titre",
		                                               renderer,
		                                               "text", TITLE_COLUMN,
		                                               NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);
	gtk_box_pack_start(GTK_BOX (box1), tree, TRUE, TRUE, 0);
	gtk_widget_show (tree);
	
    gtk_widget_show (box1);

	return window;
}