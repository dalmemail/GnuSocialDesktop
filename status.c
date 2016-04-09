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
#include <fcntl.h>
#include "lang/lang.h"
#include "status.h"
#include "gsd.h"
#include "parser/parser.h"

#define REPLY 0
#define HOME_TIMELINE 1
#define PUBLIC_TIMELINE 2
#define FAVORITES 3

#define CREATE 0
#define DELETE 1

int number_of_replies = 0;

char user_data[4][32];

void print_reply(char *buffer)
{
	char reply[number_of_replies][6][300];
	char tofind[6][32] = {"<text>", "<created_at>", "<id>", "<name>", "<screen_name>", "<favorited>"};
	int pos = 0;
	int act_pos = 0;
	int start_pos = 0;
	for (int i = 0; i < number_of_replies; i++) {
		for (int x = 0; x < 5; x++) {
			for (int y = 0; y < 300; y++) {
				reply[i][x][y] = '\0';
			}
			act_pos = 0;
			for (int y = pos; act_pos != strlen(tofind[x]); y++) {
				if (tofind[x][act_pos] == buffer[y]) {
					act_pos++;
					if (act_pos == strlen(tofind[x])) {
						pos = y;
					}
				}
				else {
					act_pos = 0;
				}
			}
			start_pos = pos+1;
			for (int y = 0; buffer[start_pos+y] != '<' ||buffer[start_pos+y+1] != '/'; y++) {
				reply[i][x][y] = buffer[start_pos+y];
			}
		}
	}
	for (int i = 0; i < number_of_replies; i++) {
		status_navigator(reply[i]);
	}
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

/* the source code of save_xml() is from gitn (http://linuxinthenight.com) */
size_t save_xml(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
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
	strcat(url, "/api/");
	switch (mode) {
		case REPLY:
			strcat(url, "statuses/mentions.xml");
			break;
		case HOME_TIMELINE:
			strcat(url, "statuses/home_timeline.xml");
			break;
		case PUBLIC_TIMELINE:
			strcat(url, "statuses/public_timeline.xml");
			break;
		case FAVORITES:
			strcat(url, "favorites.xml");
			break;
	}
	char to_read[16];
	strcpy(to_read, "count=");
	strcat(to_read, n);
	FILE *xml = fopen("temp/file.xml", "wb");
	CURL *curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERPWD, user);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, to_read);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_xml);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, xml);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
	fclose(xml);
	xml = fopen("temp/file.xml", "r");
	fseek(xml, 0L, SEEK_END);
	int filesize = ftell(xml);
	rewind(xml);
	char xml_data[filesize];
	fread(xml_data, filesize, filesize, xml);
	fclose(xml);
	print_reply(xml_data);
}

void find_status_by_id(char data[4][32], GtkEntry *gtk_id)
{
	for (int i = 0; i < 4; i++) {
		strcpy(user_data[i], data[i]);
	}
	number_of_replies = 1;
	char *id = gtk_entry_get_text(gtk_id);
	char *protocol = data[0];
	char *user = data[1];
	char *server = data[2];
	char *password = data[3];
	char url[100];
	strcpy(url, protocol);
	strcat(url, "://");
	strcat(url, server);
	strcat(url, "/api/statuses/show.xml&id=");
	strcat(url, id);
	FILE *xml = fopen("temp/file.xml", "wb");
	CURL *curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERPWD, user);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_xml);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, xml);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
	fclose(xml);
	xml = fopen("temp/file.xml", "r");
	fseek(xml, 0L, SEEK_END);
	int filesize = ftell(xml);
	rewind(xml);
	if (filesize > 0) {
		char xml_data[filesize];
		fread(xml_data, filesize, filesize, xml);
		fclose(xml);
		printf("%s", xml_data);
		if ((GSDParser("<error>", xml_data)) == 0) {
			print_reply(xml_data);
		}
	}
	else {
		window_message(MSG_27);
	}
}

void delete_status_by_id(char *id)
{
	char *protocol = user_data[0];
	char *user = user_data[1];
	char *server = user_data[2];
	char *password = user_data[3];
	char url[100];
	strcpy(url, protocol);
	strcat(url, "://");
	strcat(url, server);
	strcat(url, "/api/statuses/destroy.xml");

	FILE *xml = fopen("temp/file.xml", "wb");
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_xml);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, xml);
	curl_easy_setopt(curl, CURLOPT_URL, url);

	curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
	curl_easy_setopt(curl, CURLOPT_USERNAME, user);
	curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
	char buffer[3+strlen(id)];
	strcpy(buffer, "id=");
	strcat(buffer, id);

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buffer);
	curl_easy_perform(curl);

	curl_easy_cleanup(curl);
	fclose(xml);
	xml = fopen("temp/file.xml", "r");
	fseek(xml, 0L, SEEK_END);
	int filesize = ftell(xml);
	rewind(xml);
	char xml_data[filesize];
	fread(xml_data, filesize, filesize, xml);
	fclose(xml);
	printf("%s", xml_data);
	if ((GSDParser("<error>", xml_data)) == 0) {
		window_message(MSG_29);
	}
}

void show_user_timeline(char data[4][32], char *n)
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
	strcat(url, "/api/statuses/user_timeline.xml&count=");
	strcat(url, n);
	FILE *xml = fopen("temp/file.xml", "wb");
	CURL *curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERPWD, user);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_xml);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, xml);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
	fclose(xml);
	xml = fopen("temp/file.xml", "r");
	fseek(xml, 0L, SEEK_END);
	int filesize = ftell(xml);
	rewind(xml);
	char xml_data[filesize];
	fread(xml_data, filesize, filesize, xml);
	fclose(xml);
	printf("%s", xml_data);
	if ((GSDParser("<error>", xml_data)) == 0) {
		print_reply(xml_data);
	}
}

void favorites(char *id, int mode)
{
	char *protocol = user_data[0];
	char *user = user_data[1];
	char *server = user_data[2];
	char *password = user_data[3];
	char url[100];
	char buffer[3+strlen(id)];
	strcpy(url, protocol);
	strcat(url, "://");
	strcat(url, server);
	strcat(url, "/api/favorites/");
	if (mode == CREATE) {
		strcat(url, "create.xml");
	}
	else {
		strcat(url, "destroy.xml");
	}
	strcpy(buffer, "id=");
	strcat(buffer, id);
	FILE *xml = fopen("temp/file.xml", "wb");
	CURL *curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERPWD, user);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_xml);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, xml);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buffer);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
	fclose(xml);
	xml = fopen("temp/file.xml", "r");
	fseek(xml, 0L, SEEK_END);
	int filesize = ftell(xml);
	rewind(xml);
	if (filesize > 0) {
		char xml_data[filesize];
		fread(xml_data, filesize, filesize, xml);
		fclose(xml);
		printf("%s", xml_data);
		if ((GSDParser("<error>", xml_data)) == 0) {
			if (mode == CREATE) {
				window_message(MSG_34);
			}
			else {
				window_message(MSG_35);
			}
		}
	}
	else {
		window_message(MSG_27);
	}
}

void write_user_info(char *xml_data)
{
	char reply[10][300];
	char tofind[10][32] = {"<name>", "<screen_name>", "<location>", "<description>", "<profile_image_url>", "<groups_count>", "<url>", "<followers_count>", "<friends_count>", "<statuses_count>"};
	int pos = 0;
	int act_pos = 0;
	int start_pos = 0;
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 300; y++) {
			reply[x][y] = '\0';
		}
		act_pos = 0;
		for (int y = pos; act_pos != strlen(tofind[x]); y++) {
			if (tofind[x][act_pos] == xml_data[y]) {
				act_pos++;
				if (act_pos == strlen(tofind[x])) {
					pos = y;
				}
			}
			else {
				act_pos = 0;
			}
		}
		start_pos = pos+1;
		for (int y = 0; xml_data[start_pos+y] != '<' ||xml_data[start_pos+y+1] != '/'; y++) {
			reply[x][y] = xml_data[start_pos+y];
		}
	}
	int fd;
	creat("temp/user_data.txt", 0600);
	if ((fd = open("temp/user_data.txt", O_WRONLY)) >= 0) {
		for (int i = 0; i < 10; i++) {
			write(fd, reply[i], strlen(reply[i]));
			write(fd, ";", 1);
		}
		close(fd);
		char command[strlen(reply[4])+24];
		strcpy(command, "wget -O temp/avatar.png ");
		strcat(command, reply[4]);
		printf("%s\n", command);
		system(command);
	}
	else {
		window_message(MSG_36);
	}
}

void get_user_info(char data[4][32])
{
	char *protocol = data[0];
	char *user = data[1];
	char *server = data[2];
	char *password = data[3];
	char url[100];
	strcpy(url, protocol);
	strcat(url, "://");
	strcat(url, server);
	strcat(url, "/api/users/show.xml");
	FILE *xml = fopen("temp/file.xml", "wb");
	CURL *curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERPWD, user);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_xml);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, xml);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
	fclose(xml);
	xml = fopen("temp/file.xml", "r");
	fseek(xml, 0L, SEEK_END);
	int filesize = ftell(xml);
	rewind(xml);
	char xml_data[filesize];
	fread(xml_data, filesize, filesize, xml);
	fclose(xml);
	printf("%s", xml_data);
	write_user_info(xml_data);
}
