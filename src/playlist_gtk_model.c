#include <xmmsclient/xmmsclient.h>
#include <xmmsclient/xmmsclient-glib.h>
#include <gtk/gtk.h>

enum
{
   TITLE_COLUMN,
   LENGTH_COLUMN,
   CURRENT_COLUMN,
   N_COLUMNS
};

GtkTreeStore* getGtkTreePlaylist()
{
	GtkTreeIter   iter;
	GtkTreeStore *store;

	store = gtk_tree_store_new (N_COLUMNS,       /* Total number of columns */
		                                      G_TYPE_STRING,   /* Song name               */
		                                      G_TYPE_STRING,   /* Length                  */
		                                      G_TYPE_BOOLEAN); /* Current?                */


	gtk_tree_store_append (store, &iter, NULL);  /* Acquire an iterator */

	gtk_tree_store_set (store, &iter,
                    TITLE_COLUMN, "The Principle of Reason",
                    LENGTH_COLUMN, "Martin Heidegger",
                    CURRENT_COLUMN, FALSE,
                    -1);

	return store; 
}