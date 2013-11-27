/*
 * obpipec.c
 * 
 * Copyright 2013 Mark Whittaker <magpie240@gmx.com>
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

/*
 * IF YOU REALLY WANT TO READ THIS CODE, MAIL ME AND I'LL
 * DOCUMENT IT PROPERLY.
 */


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char  givendirs[2][256];
char *desktopfiles[384];
char  iconholder[2048][256];
char  iconpath[256];
char  outstring[16384];
int   givendirscounter = 0;
int   iconcounter = 0;
int   num_entries = 0;
struct ob_entry {
	char name[96];
	char exec[96];
	char iconname[96];
	int  category;
	int  nodisplay;
};
struct ob_entry entries[384];


void cacheicons(char *icondir)
{
	DIR *dir;
	struct dirent *entry;
	char temp[256];
	
	if ((dir = opendir(icondir)) != NULL) {
		while ((entry = readdir(dir)) != NULL) {
			temp[0] = 0;
			strcat(temp, icondir);
			strcat(temp, "/");
			if ((strstr(entry->d_name, ".png")) != NULL || (strstr(entry->d_name, ".xpm")) != NULL) {
//				printf("DEBUG: %s\t %s\n", icondir, entry->d_name);
				strcat(temp, entry->d_name);
				strcpy(iconholder[iconcounter++], temp);
			}
		}
	closedir(dir);
	}
}

char *lookupicon(char *i_name)
{
	int i = 0;
	
	iconpath[0] = 0;
	for (; i < iconcounter; i++)
		if (strstr(iconholder[i], i_name) != NULL) {
			strcpy(iconpath, iconholder[i]);
			break;
		}
	return iconpath;
}

int listentries()
{
	DIR    *dir;
	struct dirent *entry;
	int    i = 0, offset = 0;
	char   temp[256];
	
	for (i = 0; i < givendirscounter + 1; i++) {
		dir = opendir(givendirs[i]);
		while ((entry = readdir(dir)) != NULL) {
			if (strstr(entry->d_name, ".desktop")) {
				temp[0] = 0;
				strcat(temp, givendirs[i]);
				strcat(temp, "/");
				strcat(temp, entry->d_name);
				*(desktopfiles + offset) = malloc(256 * sizeof(char));
				strcpy(*(desktopfiles + offset), temp);
				offset++;
			}
		}
		closedir(dir);
	}
	return offset;
}

void openentries()
{
	int     offset = 0;
	FILE   *fp;
	char   *line = NULL;
	size_t  len = 0;
	int  toklen = 0;
	ssize_t read;
	char   *token;
	
	for (offset = 0; offset < num_entries; offset++) {
		fp = fopen(*(desktopfiles + offset), "r");
		if (fp == NULL)
			exit(EXIT_FAILURE);
		while ((read = getline(&line, &len, fp)) != -1) {
			if (strncmp(line, "Name=", 5) == 0) {
				token = strtok(line, "=");
				token = strtok(NULL, "=");
				token[strlen(token) - 1] = 0;
				strcpy(entries[offset].name, token);		
			}
			else if (strncmp(line, "Exec=", 5) == 0) {
				token = strtok(line, "=");
				token = strtok(NULL, "=");
				token[strlen(token) - 1] = 0;
				toklen = (int)strlen(token);
//				printf("DEBUG - %s\t%c\n", token, *(token + (int)toklen -2));
				if(token[toklen - 2] == '%') {
					token[toklen - 2] = 0;
//					printf("\t -> %s\n", token);
				}
				strcpy(entries[offset].exec, token);
			}
			else if (strncmp(line, "Icon=", 5) == 0) {
				token = strtok(line, "=");
				token = strtok(NULL, "=");
				token[strlen(token) - 1] = 0;
				strcpy(entries[offset].iconname, lookupicon(token));
			}
			else if (strncmp(line, "Categories=", 11) == 0) {
				token = strtok(line, "=");
				token = strtok(NULL, "=");
				token[strlen(token) - 1] = 0;
				if (strstr(token, "AudioVideo"))
					entries[offset].category = 1;
				else if (strstr(token, "Development"))
					entries[offset].category = 2;
				else if (strstr(token, "Education"))
					entries[offset].category = 3;
				else if (strstr(token, "Game"))
					entries[offset].category = 4;
				else if (strstr(token, "Graphics"))
					entries[offset].category = 5;
				else if (strstr(token, "Network"))
					entries[offset].category = 6;
				else if (strstr(token, "Office"))
					entries[offset].category = 7;
				else if (strstr(token, "Settings"))
					entries[offset].category = 8;
				else if (strstr(token, "System"))
					entries[offset].category = 9;
				else if (strstr(token, "Utility"))
					entries[offset].category = 10;
			}
			else if (strncmp(line, "NoDisplay", 9) == 0)
				entries[offset].nodisplay = 1;
			else if (strncmp(line, "OnlyShowIn=", 11) == 0)
				entries[offset].nodisplay = 1;
			else if ((strncmp(line, "[", 1)) == 0 && (strncmp(line, "[D", 2) != 0)) {
				break;
			}
		}
		fclose(fp);
	}
}

int validate(char *checkme)
{
	DIR *dir;
	size_t len = strlen(checkme);
	
	if (*(checkme + len - 1) == '/')
		*(checkme + len - 1) = 0;

	if ((dir = opendir(checkme)) == NULL)
		return -1;
	else {
//		*(givendirs + givendirscounter) = malloc(256 * sizeof(char));
		strcpy(givendirs[1], checkme);
		closedir(dir);
		return 0;
	}
}

int cmp_by_name(const void *a, const void *b)
{
	struct ob_entry *ia = (struct ob_entry *)a;
	struct ob_entry *ib = (struct ob_entry *)b;
	return strcmp(ia->name, ib->name);
}

void printobmenu(const char *menuname, int cat, char *foldericon)
{
	int i = 0;
	
	printf("  <menu id=\"pipe%s\" icon=\"%s\" label=\"%s\">\n", menuname, foldericon, menuname);
	
	for (i = 0; i < num_entries; i++) {
		if ((entries[i].nodisplay == 0) && (entries[i].category == cat))
			printf("    <item label=\"%s\" icon=\"%s\"><action name=\"Execute\"><execute>%s</execute></action></item>\n", entries[i].name, entries[i].iconname, entries[i].exec);
	}
	
	printf("  </menu>\n");
}

char  *read_gtk_icon_theme()
{
	char        *homedir = getenv("HOME");
	char        *line = NULL;
	char        *token;
	char         gtkfile[256];
	static char  finalname[128];
	static char  icondirectory[256];
	size_t       len = 0;
	size_t       namelen = 0;
	ssize_t      read;
	FILE        *fp;
	struct stat  sb;
	
	sprintf(gtkfile, "%s/.gtkrc-2.0", homedir);
	if ((fp = fopen(gtkfile, "r")) == NULL)
		return NULL;
	while (( read = getline(&line, &len, fp)) != -1) {
		if (strncmp(line, "gtk-icon-theme-name", 19) == 0) {
			token = strtok(line, "=");
			token = strtok(NULL, "=");
			strcpy(finalname, token + 1);
			namelen = strlen(finalname);
			*(finalname + (namelen - 2)) = 0;
		}
	}
	fclose(fp);
	
	sprintf(icondirectory,"%s/.icons/%s/apps/24", homedir, finalname);
	if ((stat(icondirectory, &sb) != -1))
		return icondirectory;
	sprintf(icondirectory,"%s/.icons/%s/24x24/apps", homedir, finalname);
	if ((stat(icondirectory, &sb) != -1))
		return icondirectory;
	sprintf(icondirectory,"/usr/share/icons/%s/apps/24", finalname);
	if ((stat(icondirectory, &sb) != -1))
		return icondirectory;
	sprintf(icondirectory,"/usr/share/icons/%s/24x24/apps", finalname);
	if ((stat(icondirectory, &sb) != -1))
		return icondirectory;
	return NULL;
}
	
int main(int argc, char **argv)
{
	int opts = 0;
	char foldericon[64];
//	char iconthemepath[256];
	char *iconthemename = NULL;
	char *helpmessage = "\nobpipec generates an openbox pipemenu with icons using standard\n\
desktop entries and the default hicolor icon set.\n\n \
-d  DIR  add an additional directory of desktop entries (an explicit directory name)\n \
-i       try to read icon theme from .gtkrc-2.0";


	opterr = 0;
	while ((opts = getopt(argc, argv, "hd:i")) != -1)
		switch (opts) {
			case 'h':
				printf("%s\n", helpmessage);
				return 0;
				break;
			case 'd':
				printf("Case D :: %s\n", optarg);
				if (validate(optarg) == -1) {
					fprintf(stderr, "Unknown desktop directory given. I won't continue.\n");
					return 1;
				}
				givendirscounter = 1;
				break;
			case 'i':
				if ((iconthemename = read_gtk_icon_theme()) != NULL)
					cacheicons(iconthemename);
				else
					printf("no icons\n");
				break;
			case '?':
				printf("Broken %c option\n", optopt);
				return 1;
		}
	
	strcpy(givendirs[0], "/usr/share/applications");
	cacheicons("/usr/share/pixmaps");
	cacheicons("/usr/share/icons/hicolor/64x64/apps");
	cacheicons("/usr/share/icons/hicolor/48x48/apps");
	cacheicons("/usr/share/icons/hicolor/32x32/apps");
	cacheicons("/usr/share/icons/hicolor/24x24/apps");
	cacheicons("/usr/share/icons/hicolor/16x16/apps");
	
	if (access("/usr/share/icons/gnome/32x32/places/folder.png", F_OK) == 0)
		strcpy(foldericon, "/usr/share/icons/gnome/32x32/places/folder.png");
	else if (access("/usr/share/icons/Tango/32x32/places/folder.png", F_OK) == 0)
		strcpy(foldericon, "/usr/share/icons/Tango/32x32/places/folder.png");

	num_entries = listentries();
	openentries();
	
	qsort(entries,  num_entries, sizeof(struct ob_entry), cmp_by_name);


	printf("<openbox_pipe_menu>\n");
	printobmenu("AudioVideo",  1, foldericon);
	printobmenu("Development", 2, foldericon);
	printobmenu("Education",   3, foldericon);
	printobmenu("Games",       4, foldericon);
	printobmenu("Graphics",    5, foldericon);
	printobmenu("Network",     6, foldericon);
	printobmenu("Office",      7, foldericon);
	printobmenu("Settings",    8, foldericon);
	printobmenu("System",      9, foldericon);
	printobmenu("Utilities",  10, foldericon);
	printf("</openbox_pipe_menu>\n");
	return 0;
}

