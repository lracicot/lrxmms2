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
#include <string.h>
#include <xmmsclient/xmmsclient.h>
#include <xmmsclient/xmmsclient-glib.h>
#include "entities/track.h"

const char *err_buf;

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

xmmsc_result_t *xmms2_playlist_current_active (xmmsc_connection_t * connection)
{
	xmmsc_result_t *result = xmmsc_playlist_current_active (connection);
	xmmsc_result_wait (result);

	return result;
}

track *get_mediainfo (xmmsc_connection_t *connection, int id)
{
	track *song;
	int i;
	char* strfound;
	song = malloc(sizeof(track));
	xmmsc_result_t *result;
	xmmsv_t *return_value;
	const char *err_buf;

	xmmsv_t *dict_entry;
	xmmsv_t *infos;
	const char *val;
	int intval;

	result = xmmsc_medialib_get_info (connection, id);

	xmmsc_result_wait (result);
	return_value = xmmsc_result_get_value (result);

	if (xmmsv_get_error (return_value, &err_buf)) {
		fprintf (stderr, "medialib get info returns error, %s\n",
		         err_buf);
		exit (EXIT_FAILURE);
	}
	
	infos = xmmsv_propdict_to_dict (return_value, NULL);

	if (!xmmsv_dict_get (infos, "artist", &dict_entry) ||
	    !xmmsv_get_string (dict_entry, &val)) {
		val = "No artist";
	}

	song->artist = val;

	if (!xmmsv_dict_get (infos, "title", &dict_entry) ||
	    !xmmsv_get_string (dict_entry, &val)) {
			if (!xmmsv_dict_get (infos, "url", &dict_entry) ||
				!xmmsv_get_string (dict_entry, &val)) {
				val = "No Title";
			}
			else
			{
				// strrpos
				/*for (i = strlen(val)-1; i>=0; i--)
				{
					if (strcmp(val[i], "/"))
					{
						strfound = i;
						break;
					}
				}*/
				strfound = strrchr(val, '/');

				//substr
				val = strfound+1;
			}
	}
	song->title = val;

	//xmmsv_unref (infos);
	//xmmsc_result_unref (result);

	return song;
}