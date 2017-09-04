#include <ncurses.h>
#include <cstdlib>
#include <string>
using namespace std;
int main_menu(int yMax, int xMax);

int main(int argc, char** argv) {
	initscr();
	noecho();
	curs_set(0);
	cbreak();

	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	int user_choice = main_menu(yMax, xMax);
	switch(user_choice) {
		case 0:
			mvprintw(0, 0, "your choice was 0");
			break;
		case 1:
			mvprintw(0, 0, "your choice was 1");
			break;
		case 2:
			mvprintw(0, 0, "your choice was 2");
			break;
		default: 
			break;
	}

	getch();
	endwin();
	return 0;
}

int main_menu(int yMax, int xMax) {
	//TITLE SCREEN MESSAGES
	char mesg1[] = "----------------------------------";
	char mesg2[] = "* A S C I I    B L A C K J A C K *";
	char mesg3[] = "Created by Alex Anthony Cortes-Ose";
	char mesg4[] = "----------------------------------";
	mvprintw(6,(xMax-strlen(mesg1))/2,"%s",mesg1);
	mvprintw(7,(xMax-strlen(mesg2))/2,"%s",mesg2);
	mvprintw(8,(xMax-strlen(mesg3))/2,"%s",mesg3);
	mvprintw(9,(xMax-strlen(mesg4))/2,"%s",mesg4);
	//NEW USER INPUT WINDOW
	WINDOW* menuwin = newwin(8, xMax - 12, 12, 5);
	box(menuwin, 0, 0);
	refresh();
	wrefresh(menuwin);
	keypad(menuwin, true);
	//HANDLE HIGHLIGHTING AND CHOICE
	string choices[3] = {
		"START GAME",
		"HELP",
		"QUIT"
	};
	int choice;
	int highlight = 0;
	while(true) {
		for(int i = 0; i < 3; i++) {
			if(i == highlight) wattron(menuwin, A_REVERSE);
			mvwprintw(menuwin, i + 1, 1, choices[i].c_str());
			wattroff(menuwin, A_REVERSE);
		}
		choice = wgetch(menuwin);
		switch(choice) {
			case KEY_UP:
				highlight--;
				if(highlight == -1) {
					//HANDLE OUT OF BOUNDS CURSOR
					highlight = 0;
				}
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 3) {
					//HANDLE OUT OF BOUNDS CURSOR
					highlight = 2;
				}
				break;
			default:
				break;
		}
		if(choice == 10) { //ENTER
			break;
		}
	}
	return highlight;
}