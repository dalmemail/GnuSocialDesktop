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
#include "lang/spanish.h"

void window_message(char *msg)
{
	GtkWidget *dialog, *label, *window;

        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

        gtk_window_set_title(GTK_WINDOW(window), MSG_10);
	gtk_signal_connect (GTK_OBJECT (window), "delete_event",
        GTK_SIGNAL_FUNC (gtk_main_quit), NULL);

	dialog = gtk_dialog_new_with_buttons (MSG_10,
		GTK_WINDOW (window),
		GTK_DIALOG_DESTROY_WITH_PARENT,
		GTK_STOCK_OK,
		GTK_RESPONSE_NONE,
		NULL);
	label = gtk_label_new (msg);

	g_signal_connect_swapped (GTK_OBJECT (dialog),
		"response",
		G_CALLBACK (gtk_widget_destroy),
		GTK_OBJECT (dialog));
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox),
		label);
	gtk_widget_show_all (dialog);
}

#include "status.h"

char id[7];

void run_answer_reply_()
{
	answer_reply(id);
}

GtkWidget *window;

void exit_navigator()
{
	gtk_widget_destroy(window);
	gtk_main_quit();
}

void status_navigator(char status_data[5][300])
{
	int status_size = 0;
	for (int i = 0; i < 4; i++) {
		status_size += strlen(status_data[i]);
	}
	char status_label[status_size+7];
	strcpy(id, status_data[2]);
	sprintf(status_label, "%s @%s\n%s\n%s", status_data[3], status_data[4], status_data[0], status_data[1]);
	GtkWidget *table, *label1;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), MSG_19);
    	gtk_signal_connect (GTK_OBJECT (window), "gtk_main_quit",
        GTK_SIGNAL_FUNC (gtk_main_quit), NULL);
	table = gtk_table_new(3,2,FALSE);
	gtk_container_add(GTK_CONTAINER(window),table);
	label1 = gtk_label_new(status_label);
	gtk_table_attach_defaults(GTK_TABLE(table),label1,0,1,0,1);
	GtkWidget *button1 = gtk_button_new_with_label (MSG_20);
	gtk_signal_connect (GTK_OBJECT (button1), "clicked", GTK_SIGNAL_FUNC (run_answer_reply_), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(table), button1, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table),button1,0,2,1,2);
	GtkWidget *button2 = gtk_button_new_with_label (MSG_23);
	gtk_signal_connect (GTK_OBJECT (button2), "clicked", GTK_SIGNAL_FUNC (exit_navigator), (gpointer) NULL);
	gtk_box_pack_start(GTK_BOX(table), button2, TRUE, TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table),button2,0,2,2,3);
	gtk_container_add(GTK_CONTAINER(window),table);
        gtk_widget_show_all(window);
        gtk_main();
}
