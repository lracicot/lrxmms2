#include <xmmsclient/xmmsclient.h>
#include <xmmsclient/xmmsclient-glib.h>
#include <gtk/gtk.h>

const char *err_buf;

const char get_current_playlist( gpointer   connection )
{
	xmmsv_t *value;
	xmmsc_result_t *result = xmms2_playlist_current_active((xmmsc_connection_t *) connection);

	xmmsc_result_wait (result);
	value = xmmsc_result_get_value (result);

	if (xmmsv_is_error (value) &&
	    xmmsv_get_error (value, &err_buf)) {
		fprintf (stderr, "playback start returned error, %s",
		         err_buf);
	}

	xmmsc_result_unref (result);

	return value;
}

void playlist_add( GtkWidget *widget,
                        gpointer   connection )
{
	
}