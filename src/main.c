#include <gtk/gtk.h>
#include <xmmsclient/xmmsclient.h>
#include <xmmsclient/xmmsclient-glib.h>
#include <stdlib.h>

/* Our new improved callback.  The data passed to this function
 * is printed to stdout. */
static void callback( GtkWidget *widget,
                      gpointer   data )
{
    g_print ("Hello again - %s was pressed\n", (gchar *) data);
}


static void playback_play( GtkWidget *widget,
                        gpointer   connection )
{
	xmmsc_result_t *result;
	result = xmmsc_playback_start ((xmmsc_connection_t *) connection);
	xmmsc_result_wait (result);
}

static void playback_pause( GtkWidget *widget,
                        gpointer   connection )
{
	xmmsc_result_t *result;
	result = xmmsc_playback_pause ((xmmsc_connection_t *) connection);
	xmmsc_result_wait (result);
}

static void playback_stop( GtkWidget *widget,
                        gpointer   connection )
{
	xmmsc_result_t *result;
	result = xmmsc_playback_stop ((xmmsc_connection_t *) connection);
	xmmsc_result_wait (result);
}

/* another callback */
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    gtk_main_quit ();
    return FALSE;
}

// Close the program
static void destroy(GtkWidget *widget,
                    gpointer   data)
{
	gtk_main_quit ();
}

int main( int   argc,
          char *argv[] )
{
	/* The mainloop we should use later */
	GMainLoop *ml;

	
	xmmsc_connection_t *connection;

	/*
	 * In an async client we still connect as
	 * normal. Read up on this in earlier
	 * tutorials if you need.
	 */
	connection = xmmsc_init ("tutorial6");
	if (!connection) {
		fprintf (stderr, "OOM!\n");
		exit (EXIT_FAILURE);
	}

	if (!xmmsc_connect (connection, getenv ("XMMS_PATH"))) {
		fprintf (stderr, "Connection failed: %s\n",
		         xmmsc_get_last_error (connection));

		exit (EXIT_FAILURE);
	}
	
    /* GtkWidget is the storage type for widgets */
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box1;

    /* This is called in all GTK applications. Arguments are parsed
     * from the command line and are returned to the application. */
    gtk_init (&argc, &argv);

    /* Create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /* This is a new call, which just sets the title of our
     * new window to "Hello Buttons!" */
    gtk_window_set_title (GTK_WINDOW (window), "lrxmms2");

    /* Here we just set a handler for delete_event that immediately
     * exits GTK. */
    g_signal_connect (window, "delete-event",
		      G_CALLBACK (delete_event), NULL);

	g_signal_connect (window, "destroy",
                      G_CALLBACK (destroy), NULL);

    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    /* We create a box to pack widgets into.  This is described in detail
     * in the "packing" section. The box is not really visible, it
     * is just used as a tool to arrange widgets. */
    box1 = gtk_hbox_new (FALSE, 0);

    /* Put the box into the main window. */
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

    gtk_widget_show (window);

	
	/*
	 * We are now all set to go. Just run the main loop and watch the magic.
	 */

	ml = g_main_loop_new (NULL, FALSE);
	g_main_loop_run (ml);
    /* Rest in gtk_main and wait for the fun to begin! */
    //gtk_main ();

    return 0;
}