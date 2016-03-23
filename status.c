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
#include <stdlib.h>
#include <curl/curl.h>
#include <gtk/gtk.h>
#include "lang/spanish.h"
#include "status.h"
#include "gsd.h"
#include "parser/parser.h"

#define REPLY 0
#define HOME_TIMELINE 1
#define PUBLIC_TIMELINE 2

int number_of_replies = 0;

char user_data[4][32];

void print_reply(char *buffer)
{
	char reply[1][5][300];
	char tofind[5][32] = {"<text>", "<name>", "<screen_name>", "<in_reply_to_screen_name>", "<id>"};
	for (int i = 0; i < 1; i++) {
		for (int x = 0; x < 5; x++) {
		  int pos = 0;
		  int start_pos;
		  for (start_pos = 0; start_pos < strlen(buffer) && pos < strlen(tofind[x]); start_pos++) {
		    if (buffer[start_pos] == tofind[x][pos]) {
		      pos++;
		    }
		    else {
		      pos = 0;
		    }
		  }
		  if (pos == strlen(tofind[x])) {
		    int final_pos = start_pos-1;
			while (buffer[final_pos+1] != '<' || buffer[final_pos+2] != '/') {
				final_pos++;
			}
		    char message[(final_pos-start_pos)+1];
		    for (int y = 0; y < (final_pos-start_pos)+1; y++) {
		      message[y] = buffer[start_pos+y];
			if (y == (final_pos-start_pos)) {
				strcpy(reply[i][x], message);
				reply[i][x][y+1] = '\0';
			}
		    }
		  }
		}
	}
	for (int i = 0; i < 5; i++) {
		printf("%s\n", reply[0][i]);
	}
	status_navigator(reply, number_of_replies, 0);
}

char nid[7];

GtkWidget *window, *quit_message_entry;

void check_data(char *buffer)
{
	printf("%s", buffer);
	if ((GSDParser("error", buffer)) == 0) {
	  window_message("Mensaje Publicado Correctamente");
	}
}

void answer_(GtkEntry *entry1, char data[4][32], char *id)
{
	char *protocol = data[0];
	char *user = data[1];
	char *server = data[2];
	char *password = data[3];
	const char *msg = gtk_entry_get_text(entry1);
	char url[100];
	strcpy(url, protocol);
	strcat(url, "://");
	strcat(url, server);
	strcat(url, "/api/statuses/update.xml");

	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, check_data);
	curl_easy_setopt(curl, CURLOPT_URL, url);

	curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
	curl_easy_setopt(curl, CURLOPT_USERNAME, user);
	curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
	char buffer[60+strlen(msg)];
	strcpy(buffer, "in_reply_to_status_id=");
	strcat(buffer, id);
	strcat(buffer, "&");
	strcat(buffer, "source=GnuSocialDesktop&status=");
	strcat(buffer, msg);

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buffer);
	curl_easy_perform(curl);

	curl_easy_cleanup(curl);
	printf("\n\n%s\n\n%d", buffer, id);
}

void run_answer_reply()
{
	answer_(quit_message_entry, user_data, nid);
	gtk_widget_destroy(window);
	gtk_main_quit();
}

void answer_reply(char *id)
{
	strcpy(nid, id);
	GtkWidget *table, *label1;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), MSG_7);
    	gtk_signal_connect (GTK_OBJECT (window), "gtk_main_quit",
        GTK_SIGNAL_FUNC (gtk_main_quit), NULL);
	table = gtk_table_new(3,2,FALSE);
	gtk_container_add(GTK_CONTAINER(window),table);
	label1 = gtk_label_new(MSG_8);
	gtk_table_attach_defaults(GTK_TABLE(table),label1,0,1,0,1);
	quit_message_entry = gtk_entry_new();
	gtk_table_attach_defaults(GTK_TABLE(table),quit_message_entry,1,2,0,1);
	gtk_entry_set_visibility(GTK_ENTRY(quit_message_entry),TRUE);
	GtkWidget *button1 = gtk_button_new_with_label (MSG_9);
	gtk_signal_connect (GTK_OBJECT (button1), "clicked", GTK_SIGNAL_FUNC (run_answer_reply), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(table), button1, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table),button1,1,2,1,2);
	gtk_container_add(GTK_CONTAINER(window),table);
        gtk_widget_show_all(window);
        gtk_main();
}

void load_status(char data[4][32], char *n, int mode)
{
	for (int i = 0; i < 4; i++) {
		strcpy(user_data[i], data[i]);
	}
	number_of_replies = atoi(n);
	char *protocol = data[0];
	char *user = data[1];
	char *server = data[2];
	char *password = data[3];
	char url[100];
	strcpy(url, protocol);
	strcat(url, "://");
	strcat(url, server);
	strcat(url, "/api/statuses/");
	switch (mode) {
		case REPLY:
			strcat(url, "mentions.xml");
			break;
		case HOME_TIMELINE:
			strcat(url, "home_timeline.xml");
			break;
		case PUBLIC_TIMELINE:
			strcat(url, "public_timeline.xml");
			break;
	}
	char to_read[16];
	strcpy(to_read, "count=");
	strcat(to_read, n);
	CURL *curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERPWD, user);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, to_read);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, print_reply);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
}
