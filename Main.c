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

#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "update_status.h"
#include "lang/lang.h"
#include "gsd.h"
#include "status.h"

#define REPLY 0
#define HOME_TIMELINE 1
#define PUBLIC_TIMELINE 2
#define FAVORITES 3

gint delete_event( GtkWidget *widget,
                   GdkEvent  *event,
                   gpointer   data )
{
    gtk_main_quit();
    return(FALSE);
}

GtkWidget *entry[4], *window, *first_window, *password_window;

char data[4][32];

GtkWidget *quit_message_entry;

void run_update_status(GtkWidget *button1, char data[4][32])
{
	update_status(quit_message_entry, data);
	gtk_widget_destroy(window);
	gtk_main_quit();
}

void send_quit()
{
	GtkWidget *table, *label1;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), MSG_7);
    	gtk_signal_connect (GTK_OBJECT (window), "delete_event",
        GTK_SIGNAL_FUNC (delete_event), NULL);
	table = gtk_table_new(3,2,FALSE);
	gtk_container_add(GTK_CONTAINER(window),table);
	label1 = gtk_label_new(MSG_8);
	gtk_table_attach_defaults(GTK_TABLE(table),label1,0,1,0,1);
	quit_message_entry = gtk_entry_new();
	gtk_table_attach_defaults(GTK_TABLE(table),quit_message_entry,1,2,0,1);
	gtk_entry_set_visibility(GTK_ENTRY(quit_message_entry),TRUE);
	GtkWidget *button1 = gtk_button_new_with_label (MSG_9);
	gtk_signal_connect (GTK_OBJECT (button1), "clicked", GTK_SIGNAL_FUNC (run_update_status), (gpointer) data);
	gtk_box_pack_start(GTK_BOX(table), button1, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table),button1,1,2,1,2);
	//g_signal_connect(G_OBJECT(entry1),"activate",G_CALLBACK(run_update_status),data);
	gtk_container_add(GTK_CONTAINER(window),table);
        gtk_widget_show_all(window);
        gtk_main();
}

void replies()
{
	char *p = gtk_entry_get_text(quit_message_entry);
	char states_to_be_load[8];
	strcpy(states_to_be_load, p);
	gtk_widget_destroy(window);
	gtk_main_quit();
	load_status(data, states_to_be_load, REPLY);
}

void execute_replies()
{
	GtkWidget *table, *label1;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), MSG_7);
    	gtk_signal_connect (GTK_OBJECT (window), "delete_event",
        GTK_SIGNAL_FUNC (delete_event), NULL);
	table = gtk_table_new(3,2,FALSE);
	gtk_container_add(GTK_CONTAINER(window),table);
	label1 = gtk_label_new(MSG_24);
	gtk_table_attach_defaults(GTK_TABLE(table),label1,0,1,0,1);
	quit_message_entry = gtk_entry_new();
	gtk_table_attach_defaults(GTK_TABLE(table),quit_message_entry,0,1,1,2);
	gtk_entry_set_visibility(GTK_ENTRY(quit_message_entry),TRUE);
	GtkWidget *button1 = gtk_button_new_with_label (MSG_23);
	gtk_signal_connect (GTK_OBJECT (button1), "clicked", GTK_SIGNAL_FUNC (replies), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(table), button1, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table),button1,1,2,1,2);
	gtk_container_add(GTK_CONTAINER(window),table);
        gtk_widget_show_all(window);
        gtk_main();
}

void home_timeline_()
{
	char *p = gtk_entry_get_text(quit_message_entry);
	char states_to_be_load[8];
	strcpy(states_to_be_load, p);
	gtk_widget_destroy(window);
	gtk_main_quit();
	load_status(data, states_to_be_load, HOME_TIMELINE);
}

void execute_ht()
{
	GtkWidget *table, *label1;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), MSG_7);
    	gtk_signal_connect (GTK_OBJECT (window), "delete_event",
        GTK_SIGNAL_FUNC (delete_event), NULL);
	table = gtk_table_new(3,2,FALSE);
	gtk_container_add(GTK_CONTAINER(window),table);
	label1 = gtk_label_new(MSG_24);
	gtk_table_attach_defaults(GTK_TABLE(table),label1,0,1,0,1);
	quit_message_entry = gtk_entry_new();
	gtk_table_attach_defaults(GTK_TABLE(table),quit_message_entry,0,1,1,2);
	gtk_entry_set_visibility(GTK_ENTRY(quit_message_entry),TRUE);
	GtkWidget *button1 = gtk_button_new_with_label (MSG_23);
	gtk_signal_connect (GTK_OBJECT (button1), "clicked", GTK_SIGNAL_FUNC (home_timeline_), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(table), button1, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table),button1,1,2,1,2);
	gtk_container_add(GTK_CONTAINER(window),table);
        gtk_widget_show_all(window);
        gtk_main();
}

void public_timeline_()
{
	char *p = gtk_entry_get_text(quit_message_entry);
	char states_to_be_load[8];
	strcpy(states_to_be_load, p);
	gtk_widget_destroy(window);
	gtk_main_quit();
	load_status(data, states_to_be_load, PUBLIC_TIMELINE);
}

void user_timeline_()
{
	char *p = gtk_entry_get_text(quit_message_entry);
	char states_to_be_load[8];
	strcpy(states_to_be_load, p);
	gtk_widget_destroy(window);
	gtk_main_quit();
	show_user_timeline(data, states_to_be_load);
}

void favorites_()
{
	char *p = gtk_entry_get_text(quit_message_entry);
	char states_to_be_load[8];
	strcpy(states_to_be_load, p);
	gtk_widget_destroy(window);
	gtk_main_quit();
	load_status(data, states_to_be_load, FAVORITES);
}

void execute_pt()
{
	GtkWidget *table, *label1;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), MSG_7);
    	gtk_signal_connect (GTK_OBJECT (window), "delete_event",
        GTK_SIGNAL_FUNC (delete_event), NULL);
	table = gtk_table_new(3,2,FALSE);
	gtk_container_add(GTK_CONTAINER(window),table);
	label1 = gtk_label_new(MSG_24);
	gtk_table_attach_defaults(GTK_TABLE(table),label1,0,1,0,1);
	quit_message_entry = gtk_entry_new();
	gtk_table_attach_defaults(GTK_TABLE(table),quit_message_entry,0,1,1,2);
	gtk_entry_set_visibility(GTK_ENTRY(quit_message_entry),TRUE);
	GtkWidget *button1 = gtk_button_new_with_label (MSG_23);
	gtk_signal_connect (GTK_OBJECT (button1), "clicked", GTK_SIGNAL_FUNC (public_timeline_), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(table), button1, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table),button1,1,2,1,2);
	gtk_container_add(GTK_CONTAINER(window),table);
        gtk_widget_show_all(window);
        gtk_main();
}

void execute_ut()
{
	GtkWidget *table, *label1;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), MSG_7);
    	gtk_signal_connect (GTK_OBJECT (window), "delete_event",
        GTK_SIGNAL_FUNC (delete_event), NULL);
	table = gtk_table_new(3,2,FALSE);
	gtk_container_add(GTK_CONTAINER(window),table);
	label1 = gtk_label_new(MSG_24);
	gtk_table_attach_defaults(GTK_TABLE(table),label1,0,1,0,1);
	quit_message_entry = gtk_entry_new();
	gtk_table_attach_defaults(GTK_TABLE(table),quit_message_entry,0,1,1,2);
	gtk_entry_set_visibility(GTK_ENTRY(quit_message_entry),TRUE);
	GtkWidget *button1 = gtk_button_new_with_label (MSG_23);
	gtk_signal_connect (GTK_OBJECT (button1), "clicked", GTK_SIGNAL_FUNC (user_timeline_), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(table), button1, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table),button1,1,2,1,2);
	gtk_container_add(GTK_CONTAINER(window),table);
        gtk_widget_show_all(window);
        gtk_main();
}

void execute_fav()
{
	GtkWidget *table, *label1;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), MSG_7);
    	gtk_signal_connect (GTK_OBJECT (window), "delete_event",
        GTK_SIGNAL_FUNC (delete_event), NULL);
	table = gtk_table_new(3,2,FALSE);
	gtk_container_add(GTK_CONTAINER(window),table);
	label1 = gtk_label_new(MSG_24);
	gtk_table_attach_defaults(GTK_TABLE(table),label1,0,1,0,1);
	quit_message_entry = gtk_entry_new();
	gtk_table_attach_defaults(GTK_TABLE(table),quit_message_entry,0,1,1,2);
	gtk_entry_set_visibility(GTK_ENTRY(quit_message_entry),TRUE);
	GtkWidget *button1 = gtk_button_new_with_label (MSG_23);
	gtk_signal_connect (GTK_OBJECT (button1), "clicked", GTK_SIGNAL_FUNC (favorites_), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(table), button1, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table),button1,1,2,1,2);
	gtk_container_add(GTK_CONTAINER(window),table);
        gtk_widget_show_all(window);
        gtk_main();
}

void about_me()
{
	GtkWidget *dialog, *label;
	GdkPixbuf *pixbuf;
	GtkWidget *picture;

	dialog = gtk_dialog_new_with_buttons (MSG_2,
		GTK_WINDOW (window),
		GTK_DIALOG_DESTROY_WITH_PARENT,
		GTK_STOCK_OK,
		GTK_RESPONSE_NONE,
		NULL);
	label = gtk_label_new (MSG_0);

	pixbuf = gdk_pixbuf_new_from_file_at_scale("logo.png",175,55,FALSE,NULL);
	picture=gtk_image_new_from_pixbuf(pixbuf);
	gtk_container_add(GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), picture);

	g_signal_connect_swapped (GTK_OBJECT (dialog),
		"response",
		G_CALLBACK (gtk_widget_destroy),
		GTK_OBJECT (dialog));
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox),
		label);
	gtk_widget_show_all (dialog);
}

void make_config()
{
	for (int i = 0; i < 4; i++) {
		char *p = gtk_entry_get_text(entry[i]);
		strcpy(data[i], p);
	}
	int fd;
	creat("gsd.config", 0600);
	if ((fd = open("gsd.config", O_WRONLY)) >= 0) {
		for (int i = 0; i < 3; i++) {
			write(fd, data[i], strlen(data[i]));
			write(fd, "\n", 1);
		}
		close(fd);
		window_message(MSG_13);
	}
	else {
		window_message(MSG_14);
	}
}

void create_account()
{
	make_config();
	gtk_widget_destroy(first_window);
	gtk_main_quit();
	get_user_info(data);
	gnusocialdesktop();
}

void delete_config()
{
	if ((unlink("gsd.config")) < 0) {
		window_message(MSG_16);
	}
	else {
		window_message(MSG_17);
	}
}

void run_find_status_by_id()
{
	find_status_by_id(data, quit_message_entry);
}

void ask_me_id()
{
	GtkWidget *table, *label1;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), MSG_25);
    	gtk_signal_connect (GTK_OBJECT (window), "delete_event",
        GTK_SIGNAL_FUNC (delete_event), NULL);
	table = gtk_table_new(3,2,FALSE);
	gtk_container_add(GTK_CONTAINER(window),table);
	label1 = gtk_label_new(MSG_26);
	gtk_table_attach_defaults(GTK_TABLE(table),label1,0,1,0,1);
	quit_message_entry = gtk_entry_new();
	gtk_table_attach_defaults(GTK_TABLE(table),quit_message_entry,1,2,0,1);
	gtk_entry_set_visibility(GTK_ENTRY(quit_message_entry),TRUE);
	GtkWidget *button1 = gtk_button_new_with_label (MSG_23);
	gtk_signal_connect (GTK_OBJECT (button1), "clicked", GTK_SIGNAL_FUNC (run_find_status_by_id), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(table), button1, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table),button1,1,2,1,2);
	gtk_container_add(GTK_CONTAINER(window),table);
        gtk_widget_show_all(window);
        gtk_main();
}

char user_info[10][100];

void my_account()
{
        /* Creo la ventana */
        GtkWidget *w = gtk_window_new(GTK_WINDOW_TOPLEVEL);

        /* Le pongo un título */
        gtk_window_set_title(GTK_WINDOW(w), MSG_37);
    	gtk_signal_connect (GTK_OBJECT (w), "delete_event",
        GTK_SIGNAL_FUNC (delete_event), NULL);
	GtkWidget *box1 = gtk_table_new(3,2,FALSE);

	GdkPixbuf *avatar_pixbuf = gdk_pixbuf_new_from_file_at_scale("temp/avatar.png",70,70,FALSE,NULL);
	GtkWidget *avatar=gtk_image_new_from_pixbuf(avatar_pixbuf);
	gtk_table_attach_defaults(GTK_TABLE(box1),avatar,0,1,0,1);

	char string[800];
	sprintf(string, "%s: %s\n%s: @%s\n%s: %s\n%s: %s\n%s: %s\n%s: %s\n%s: %s\n%s: %s\n%s: %s", MSG_38, user_info[0], MSG_39, user_info[1], MSG_40, user_info[2], MSG_41, user_info[3],
		MSG_42, user_info[6], MSG_43, user_info[9], MSG_44, user_info[8], MSG_45, user_info[7], MSG_46, user_info[5]);
	GtkWidget *label1 = gtk_label_new(string);
	gtk_table_attach_defaults(GTK_TABLE(box1),label1,0,1,1,2);

	gtk_container_add(GTK_CONTAINER(w), box1);

	gtk_widget_show(box1);
        gtk_widget_show_all(w);
        gtk_main();
}

void gnusocialdesktop()
{
	int fd;
	char raw_data[1000];
	if ((fd = open("temp/user_data.txt", O_RDONLY)) >= 0) {
		read(fd, raw_data, 1000);
		close(fd);
		int y = 0;
		for (int i = 0; i < 10; i++) {
			for (int x = 0; x < 100; x++) {
				user_info[i][x] = '\0';
			}
			for (int x = 0; raw_data[y] != '\n' && x < 100; x++) {
				user_info[i][x] = raw_data[y];
				y++;
			}
			y++;
		}
	}
	GdkPixbuf *pixbuf, *avatar_pixbuf;
	GtkWidget *picture, *avatar;
        GtkWidget *w, *box1;
	GtkWidget *button1, *button2, *button3, *button4, *button5, *button6, *button7, *button8, *button9, *button10;
	GtkWidget *label1, *label2;

        /* Creo la ventana */
        w = gtk_window_new(GTK_WINDOW_TOPLEVEL);

        /* Le pongo un título */
        gtk_window_set_title(GTK_WINDOW(w), "GnuSocialDesktop");
    	gtk_signal_connect (GTK_OBJECT (w), "delete_event",
        GTK_SIGNAL_FUNC (delete_event), NULL);
	box1 = gtk_table_new(3,2,FALSE);

	avatar_pixbuf = gdk_pixbuf_new_from_file_at_scale("temp/avatar.png",60,60,FALSE,NULL);
	avatar=gtk_image_new_from_pixbuf(avatar_pixbuf);
	gtk_table_attach_defaults(GTK_TABLE(box1),avatar,1,2,0,1);

	char string[204];
	sprintf(string, "%s → @%s", user_info[0], user_info[1]);
	label1 = gtk_label_new(string);
	gtk_table_attach_defaults(GTK_TABLE(box1),label1,1,2,1,2);

	label2 = gtk_label_new(user_info[2]);
	gtk_table_attach_defaults(GTK_TABLE(box1),label2,1,2,2,3);

        /* Cargamos el logo. */
	pixbuf = gdk_pixbuf_new_from_file_at_scale("logo.png",350,110,FALSE,NULL);
	picture=gtk_image_new_from_pixbuf(pixbuf);
	gtk_table_attach_defaults(GTK_TABLE(box1),picture,3,5,0,1);

	/* Botón 1 */
	button1 = gtk_button_new_with_label (MSG_1);
	gtk_signal_connect (GTK_OBJECT (button1), "clicked", GTK_SIGNAL_FUNC (send_quit), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(box1), button1, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(box1),button1,2,3,1,2);

	button2 = gtk_button_new_with_label (MSG_2);
	gtk_signal_connect (GTK_OBJECT (button2), "clicked", GTK_SIGNAL_FUNC (about_me), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(box1), button2, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(box1),button2,3,4,1,2);

	button3 = gtk_button_new_with_label (MSG_15);
	gtk_signal_connect (GTK_OBJECT (button3), "clicked", GTK_SIGNAL_FUNC (delete_config), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(box1), button3, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(box1),button3,2,3,2,3);

	button4 = gtk_button_new_with_label (MSG_18);
	gtk_signal_connect (GTK_OBJECT (button4), "clicked", GTK_SIGNAL_FUNC (execute_replies), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(box1), button4, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(box1),button4,3,4,2,3);

	button5 = gtk_button_new_with_label (MSG_21);
	gtk_signal_connect (GTK_OBJECT (button5), "clicked", GTK_SIGNAL_FUNC (execute_ht), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(box1), button5, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(box1),button5,4,5,1,2);

	button6 = gtk_button_new_with_label (MSG_22);
	gtk_signal_connect (GTK_OBJECT (button6), "clicked", GTK_SIGNAL_FUNC (execute_pt), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(box1), button6, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(box1),button6,4,5,2,3);

	button7 = gtk_button_new_with_label (MSG_25);
	gtk_signal_connect (GTK_OBJECT (button7), "clicked", GTK_SIGNAL_FUNC (ask_me_id), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(box1), button7, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(box1),button7,5,6,1,2);

	button8 = gtk_button_new_with_label (MSG_30);
	gtk_signal_connect (GTK_OBJECT (button8), "clicked", GTK_SIGNAL_FUNC (execute_ut), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(box1), button8, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(box1),button8,5,6,2,3);

	button9 = gtk_button_new_with_label (MSG_31);
	gtk_signal_connect (GTK_OBJECT (button9), "clicked", GTK_SIGNAL_FUNC (execute_fav), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(box1), button9, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(box1),button9,2,3,3,4);

	button10 = gtk_button_new_with_label (MSG_37);
	gtk_signal_connect (GTK_OBJECT (button10), "clicked", GTK_SIGNAL_FUNC (my_account), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(box1), button10, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(box1),button10,3,4,3,4);

	gtk_container_add(GTK_CONTAINER(w), box1);

	gtk_widget_show(box1);
        gtk_widget_show_all(w);
        /* Finalmente entramos en el bucle principal. */
        gtk_main();
}

void password_load()
{
	char *p = gtk_entry_get_text(entry[3]);
	strcpy(data[3], p);
	gtk_widget_destroy(password_window);
	gtk_main_quit();
	gnusocialdesktop();
}

int main(int argc, char **argv)
{
	int fd;
	char raw_data[150];
	if ((fd = open("gsd.config", O_RDONLY)) >= 0) {
		read(fd, raw_data, 150);
		close(fd);
		int y = 0;
		for (int i = 0; i < 3; i++) {
			for (int x = 0; x < 32; x++) {
				data[i][x] = '\0';
			}
			for (int x = 0; raw_data[y] != '\n' && x < 32; x++) {
				data[i][x] = raw_data[y];
				y++;
			}
			y++;
		}
		gtk_init(&argc, &argv);
		password_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(password_window), "Iniciando Sesión");
	    	gtk_signal_connect (GTK_OBJECT (password_window), "delete_event",
		GTK_SIGNAL_FUNC (delete_event), NULL);
		GtkWidget *box1 = gtk_table_new(3,2,FALSE);
		GtkWidget *button1 = gtk_button_new_with_label (MSG_11);
		gtk_signal_connect (GTK_OBJECT (button1), "clicked", GTK_SIGNAL_FUNC (password_load), (gpointer) "button 1");
		gtk_box_pack_start(GTK_BOX(box1), button1, TRUE, TRUE, 0);
		gtk_table_attach_defaults(GTK_TABLE(box1),button1,0,2,9,10);

		GtkWidget *label1 = gtk_label_new(MSG_6);
		gtk_table_attach_defaults(GTK_TABLE(box1),label1,0,1,2,3);
		entry[3] = gtk_entry_new();
		gtk_entry_set_visibility(GTK_ENTRY(entry[3]),FALSE);
		gtk_table_attach_defaults(GTK_TABLE(box1),entry[3],1,2,2,3);
		gtk_container_add(GTK_CONTAINER(password_window), box1);

		gtk_widget_show(box1);
		gtk_widget_show_all(password_window);
		gtk_main();
	}
	else {
		GdkPixbuf *pixbuf;
		GtkWidget *picture;
		GtkWidget *box1;
		GtkWidget *button1;
		GtkWidget *label, *label1, *label2, *label3, *label4;

		gtk_init(&argc, &argv);

		/* Creo la ventana */
		first_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

		/* Le pongo un título */
		gtk_window_set_title(GTK_WINDOW(first_window), "GSD");
	    	gtk_signal_connect (GTK_OBJECT (first_window), "delete_event",
		GTK_SIGNAL_FUNC (delete_event), NULL);
		box1 = gtk_table_new(3,2,FALSE);

		/* Cargamos el logo. */
		pixbuf = gdk_pixbuf_new_from_file_at_scale("logo.png",350,110,FALSE,NULL);
		picture=gtk_image_new_from_pixbuf(pixbuf);
		gtk_table_attach_defaults(GTK_TABLE(box1),picture,0,2,0,1);

		/* Mensaje de Bienvenida ;) */
		label = gtk_label_new(MSG_12);
		gtk_table_attach_defaults(GTK_TABLE(box1),label,0,2,1,2);

		/* Botón 1 */
		button1 = gtk_button_new_with_label (MSG_11);
		gtk_signal_connect (GTK_OBJECT (button1), "clicked", GTK_SIGNAL_FUNC (create_account), (gpointer) "button 1");
		gtk_box_pack_start(GTK_BOX(box1), button1, TRUE, TRUE, 0);
		gtk_table_attach_defaults(GTK_TABLE(box1),button1,0,2,9,10);

		label1 = gtk_label_new(MSG_3);
		gtk_table_attach_defaults(GTK_TABLE(box1),label1,0,1,2,3);
		entry[0] = gtk_entry_new();
		gtk_entry_set_visibility(GTK_ENTRY(entry[0]),TRUE);
		gtk_table_attach_defaults(GTK_TABLE(box1),entry[0],1,2,2,3);

		label2 = gtk_label_new(MSG_4);
		gtk_table_attach_defaults(GTK_TABLE(box1),label2,0,1,3,4);
		entry[1] = gtk_entry_new();
		gtk_entry_set_visibility(GTK_ENTRY(entry[1]),TRUE);
		gtk_table_attach_defaults(GTK_TABLE(box1),entry[1],1,2,3,4);

		label3 = gtk_label_new(MSG_5);
		gtk_table_attach_defaults(GTK_TABLE(box1),label3,0,1,5,6);
		entry[2] = gtk_entry_new();
		gtk_entry_set_visibility(GTK_ENTRY(entry[2]),TRUE);
		gtk_table_attach_defaults(GTK_TABLE(box1),entry[2],1,2,5,6);

		label4 = gtk_label_new(MSG_6);
		gtk_table_attach_defaults(GTK_TABLE(box1),label4,0,1,7,8);
		entry[3] = gtk_entry_new();
		gtk_entry_set_visibility(GTK_ENTRY(entry[3]),FALSE);
		gtk_table_attach_defaults(GTK_TABLE(box1),entry[3],1,2,7,8);

		gtk_container_add(GTK_CONTAINER(first_window), box1);

		gtk_widget_show(box1);
		gtk_widget_show_all(first_window);
		/* Finalmente entramos en el bucle principal. */
		gtk_main();
	}

        return 0;
}
