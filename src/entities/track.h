
#ifndef __LRXMMS2_TRACK_ENTITY_H__
#define __LRXMMS2_TRACK_ENTITY_H__

typedef struct 
{
	xmmsc_connection_t * connection;
	const char *title;
	const char *length;
	const char *artist;
	int position;
	int current;
} track;

#endif