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

#include <xmmsclient/xmmsclient.h>
#include <xmmsclient/xmmsclient-glib.h>
#include "entities/track.h"

#ifndef __LRXMMS2_XMMS_H__
#define __LRXMMS2_XMMS_H__

xmmsc_connection_t 	*get_xmms2_connection ();
xmmsc_result_t 		*xmms2_playback_play (xmmsc_connection_t * connection);
xmmsc_result_t 		*xmms2_playback_pause (xmmsc_connection_t * connection);
xmmsc_result_t 		*xmms2_playback_prev (xmmsc_connection_t * connection);
xmmsc_result_t 		*xmms2_playback_next (xmmsc_connection_t * connection);
xmmsc_result_t 		*xmms2_playback_stop (xmmsc_connection_t * connection);
xmmsc_result_t 		*xmms2_playlist_current_active (xmmsc_connection_t * connection);
xmmsc_result_t* xmms2_playlist_remove (xmmsc_connection_t *connection, int id);
track 				*get_mediainfo (xmmsc_connection_t *connection, int id);

#endif