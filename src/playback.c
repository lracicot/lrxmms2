#include <xmmsclient/xmmsclient.h>
#include <xmmsclient/xmmsclient-glib.h>
#include <gtk/gtk.h>

void playback_play( GtkWidget *widget,
                        gpointer   connection )
{
	xmmsc_result_t *result = xmms2_playback_play((xmmsc_connection_t *) connection);
	//handle result
	xmmsc_result_unref (result);
}

void playback_pause( GtkWidget *widget,
                        gpointer   connection )
{
	xmmsc_result_t *result = xmms2_playback_pause((xmmsc_connection_t *) connection);
	//handle result
	xmmsc_result_unref (result);
}

void playback_stop( GtkWidget *widget,
                        gpointer   connection )
{
	xmmsc_result_t *result = xmms2_playback_stop((xmmsc_connection_t *) connection);
	//handle result
	xmmsc_result_unref (result);
}