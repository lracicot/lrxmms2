/*
 * main.c
 * lrxmms2
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
#include <stdlib.h>
#include "xmms2.h"
#include "mainWindow.h"
#include "mainTest.h"

int main( int argc, char* argv[] )
{
	//GMainLoop* ml;
	GtkWidget* window;
	xmmsc_connection_t *connection;

	system("xmms2-launcher");
	
	connection = get_xmms2_connection();
	
    gtk_init (&argc, &argv);
    window = new_mainWindow((gpointer) connection);
	
    gtk_widget_show_all(window);
	gtk_main ();
	
	//ml = g_main_loop_new (NULL, FALSE);
	//g_main_loop_run (ml);

    return 0;
}