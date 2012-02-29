#include <xmmsclient/xmmsclient.h>
#include <xmmsclient/xmmsclient-glib.h>
#include <gtk/gtk.h>
#include "entities/playlist.h"
#include "xmms2.h"
#include "entities/track.h"
#include <stdio.h>
#include <stdlib.h>

const char *err_buf;

void get_current_playlist( gpointer connection, playlist* trackList )
{
	xmmsv_t *playlistId;
	
	xmmsv_t *return_value;
	xmmsv_list_iter_t* it;
	xmmsc_result_t *result;

	result = xmms2_playlist_current_active((xmmsc_connection_t *) connection);
	xmmsc_result_wait (result);
	playlistId = xmmsc_result_get_value (result);

	if (xmmsv_is_error (playlistId) &&
	    xmmsv_get_error (playlistId, &err_buf)) {
		fprintf (stderr, "playback start returned error, %s",
		         err_buf);
	}
	else
	{
		result = xmmsc_playlist_list_entries (connection, NULL);
		xmmsc_result_wait (result);
		return_value = xmmsc_result_get_value (result);

		if (xmmsv_get_error (return_value, &err_buf)) {
			fprintf (stderr, "error when asking for the playlist, %s\n",
				     err_buf);
		}

		if (!xmmsv_get_list_iter (return_value, &it)) {
			fprintf (stderr, "xmmsc_playlist_list_entries didn't "
				     "return a list as expected\n");
		}

		trackList->id = 5;
		trackList->tracks = it;
	}

	//xmmsc_result_unref (result);
}

void playlist_add( GtkWidget *widget,
                        gpointer   connection )
{
	
}