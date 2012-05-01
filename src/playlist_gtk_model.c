#include <xmmsclient/xmmsclient.h>
#include <xmmsclient/xmmsclient-glib.h>
#include <gtk/gtk.h>
#include "entities/playlist.h"
#include "entities/track.h"
#include "xmms2.h"

enum
{
   TITLE_COLUMN,
   ARTIST_COLUMN,
   ID_COLUMN,
  // LENGTH_COLUMN,
   CURRENT_COLUMN,
   N_COLUMNS
};

void getGtkTreePlaylist(xmmsc_connection_t *connection, playlist *trackList, GtkTreeStore *store)
{
	GtkTreeIter   iter;
	track *trackInfo;
	
	int id;
	int i = 0;
	xmmsv_t *list_entry;
	
	for (; xmmsv_list_iter_valid (trackList->tracks); xmmsv_list_iter_next (trackList->tracks))
	{
		if (!xmmsv_list_iter_entry (trackList->tracks, &list_entry)) {
			fprintf (stderr, "Couldn't get entry from list\n");
		}

		if (!xmmsv_get_int (list_entry, &id)) {
			fprintf (stderr, "Couldn't get int from list entry\n");
		}

		trackInfo = get_mediainfo (connection, id);

		gtk_tree_store_append (store, &iter, NULL);  // Acquire an iterator
		g_print("test2");

/*		gtk_tree_store_set (store, &iter,
		                TITLE_COLUMN, trackInfo->title,
		                LENGTH_COLUMN, trackInfo->length,
		                CURRENT_COLUMN, trackInfo->current);*/
		gtk_tree_store_set (store, &iter,
		                TITLE_COLUMN, trackInfo->title,
		                ARTIST_COLUMN, trackInfo->artist,
		                ID_COLUMN, i++,
		               // LENGTH_COLUMN, trackInfo->length,
		                CURRENT_COLUMN, 0
		                    );
		                    
	}
}