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
#include <xmmsclient/xmmsclient.h>
#include <xmmsclient/xmmsclient-glib.h>

static void playback_play( GtkWidget *widget,
                        gpointer   connection )
{
	xmmsc_result_t *result = xmms2_playback_play((xmmsc_connection_t *) connection);
	//handle result
}

static void playback_pause( GtkWidget *widget,
                        gpointer   connection )
{
	xmmsc_result_t *result = xmms2_playback_pause((xmmsc_connection_t *) connection);
	//handle result
}

static void playback_stop( GtkWidget *widget,
                        gpointer   connection )
{
	xmmsc_result_t *result = xmms2_playback_stop((xmmsc_connection_t *) connection);
	//handle result
}

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
    GtkWidget *box1;

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
	
    gtk_widget_show (box1);

	return window;
}