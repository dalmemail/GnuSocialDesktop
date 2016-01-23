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
