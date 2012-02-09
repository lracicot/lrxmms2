/*
 * xmms2.h
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

#include <stdlib.h>
#include <stdio.h>
#include <xmmsclient/xmmsclient.h>
#include <xmmsclient/xmmsclient-glib.h>

xmmsc_connection_t *get_xmms2_connection()
{
	xmmsc_connection_t *connection;
	
	connection = xmmsc_init ("lrxmms2");
	if (!connection) {
		fprintf (stderr, "OOM!\n");
		exit (EXIT_FAILURE);
	}

	if (!xmmsc_connect (connection, getenv ("XMMS_PATH"))) {
		fprintf (stderr, "Connection failed: %s\n",
		         xmmsc_get_last_error (connection));

		exit (EXIT_FAILURE);
	}

	//xmmsc_mainloop_gmain_init (connection);

	return connection;
}

xmmsc_result_t *xmms2_playback_play (xmmsc_connection_t * connection)
{
	xmmsc_result_t *result = xmmsc_playback_start (connection);
	xmmsc_result_wait (result);

	return result;
}

xmmsc_result_t *xmms2_playback_pause (xmmsc_connection_t * connection)
{
	xmmsc_result_t *result = xmmsc_playback_pause (connection);
	xmmsc_result_wait (result);

	return result;
}

xmmsc_result_t *xmms2_playback_stop (xmmsc_connection_t * connection)
{
	xmmsc_result_t *result = xmmsc_playback_stop (connection);
	xmmsc_result_wait (result);

	return result;
}