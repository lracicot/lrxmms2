#include <xmmsclient/xmmsclient.h>
#include "track.h"

#ifndef __LRXMMS2_PLAYLIST_ENTITY_H__
#define __LRXMMS2_PLAYLIST_ENTITY_H__

typedef struct
{
	int id;
	//track *tracks[];
	xmmsv_list_iter_t *tracks;
	
} playlist;

#endif