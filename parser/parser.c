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

#include "../gsd.h"
#include <string.h>

int GSDParser(char *tofind, char *buffer)
{
  int res = 0;
  int pos = 0;
  int start_pos;
  for (start_pos = 0; start_pos < strlen(buffer) && pos < strlen(tofind); start_pos++) {
    if (buffer[start_pos] == tofind[pos]) {
      pos++;
    }
    else {
      pos = 0;
    }
  }
  if (pos == strlen(tofind)) {
    res++;
    int final_pos = start_pos;
    while (buffer[final_pos+1] != '<' && buffer[final_pos+2] != '/' && final_pos < strlen(buffer)) {
      final_pos++;
    }
    char error_message[final_pos-start_pos];
    for (int i = 0; i < (final_pos-start_pos); i++) {
      error_message[i] = buffer[start_pos+i];
	if ((i+1) == (final_pos-start_pos)) {
		error_message[i+1] = '\0';
	}
    }
    window_message(error_message);
  }
  return res;
}
