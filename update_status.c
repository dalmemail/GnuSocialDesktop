/*
 * Copyright (C) 2016 Dan Rulos.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <curl/curl.h>
#include "update_status.h"

void update_status(GtkEntry *entry1, char data[5][32])
{
	char *protocol = data[0];
	char *user = data[1];
	char *server = data[2];
	char *password = data[3];
	const gchar *gchar_msg = gtk_entry_get_text(entry1);
	char *msg = gchar_msg;
	char url[100];
	strcpy(url, protocol);
	strcat(url, "://");
	strcat(url, server);
	strcat(url, "/api/statuses/update.xml");

	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url);

	curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
	curl_easy_setopt(curl, CURLOPT_USERNAME, user);
	curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
	char buffer[7+strlen(msg)];
	strcpy(buffer, "status=");
	strcat(buffer, msg);

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buffer);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
}
