#include <xmmsclient/xmmsclient.h>
#include <xmmsclient/xmmsclient-glib.h>
#include <gtk/gtk.h>

enum
{
   TITLE_COLUMN,
   ARTIST_COLUMN,
   ID_COLUMN,
   //LENGTH_COLUMN,
   CURRENT_COLUMN,
   N_COLUMNS
};

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

void playback_toggleplay( GtkWidget *widget,
                        gpointer   connection )
{
	if (gtk_toggle_button_get_active (widget))
	{
		playback_play( widget, connection );
	}
	else
	{
		playback_pause( widget, connection );
	}
}

void playback_stop( GtkWidget *widget,
                        gpointer   connection )
{
	xmmsc_result_t *result = xmms2_playback_stop((xmmsc_connection_t *) connection);
	//handle result
	xmmsc_result_unref (result);
}

void playback_prev( GtkWidget *widget,
                        gpointer   connection )
{
	xmmsc_result_t *result = xmms2_playback_prev((xmmsc_connection_t *) connection);
	//handle result
	xmmsc_result_unref (result);
}

void playback_next( GtkWidget *widget,
                        gpointer   connection )
{
	xmmsc_result_t *result = xmms2_playback_next((xmmsc_connection_t *) connection);
	//handle result
	xmmsc_result_unref (result);
}



void
  playback_jump (GtkTreeView        *list,
                       GtkTreePath        *path,
                       GtkTreeViewColumn  *col,
                       gpointer   connection)
  {
	xmmsc_result_t *res;
	GtkTreeSelection *selection;
	GtkTreeModel     *model;
	GtkTreeIter       iter;

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		gint *id;

		gtk_tree_model_get (model, &iter, 1, &id, -1);

		res = xmmsc_playlist_set_next (connection, id);
		xmmsc_result_wait (res); 
		res = xmmsc_playback_tickle (connection);
        xmmsc_result_wait (res);
		xmmsc_result_unref (res);

		playback_play( list, connection );
	}
  }