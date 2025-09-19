// uneex_LAD2025- 01_TerminalProject
// (c) Zkir MIT license

#include <curses.h>
#include <locale.h>
#include <string.h>

#define DX 4
#define DY 2

int main(int argc, char *argv[]) {
       if (argc < 2) {
            printf("Error: Please specify a file name.\n");
            printf("Usage: %s <file name>\n", argv[0]);
            return 1; 
       	}
	
		FILE *file = fopen(argv[1], "r");
		if (!file) {
			perror("Error opening file");
			return 1;
		}

        WINDOW *frame, *win;
        int c = 0;

        setlocale(LC_ALL, "");
        initscr();
		noecho();
	    
        frame = newwin(LINES - 2*DY, COLS - 2*DX, DY, DX);
        box(frame, 0, 0);
        mvwaddstr(frame, 0, (int)((COLS - 2*DX - 5) / 2), argv[1]);
        wrefresh(frame);

        win = newwin(LINES - 2*DY - 2, COLS - 2*DX-2, DY+1, DX+1);
        keypad(win, TRUE);
        scrollok (win, TRUE);
	
		int WIN_HEIGHT = LINES - 2*DY - 2;
		int WIN_WIDTH  = COLS  - 2*DX - 2-1;
	
		char line[256];
    	int line_count = 0;
	
		// Print the first page
		while (line_count < WIN_HEIGHT && fgets(line, sizeof(line), file)) {
			// remove new line symbol if any
			line[strcspn(line, "\r")] = '\0';
			line[strcspn(line, "\n")] = '\0';
        	
			// trim the line if necessary
			int len = strlen(line);
			if (len > WIN_WIDTH) {
				line[WIN_WIDTH] = '\0';
			}	
			wprintw(win, "\n%s", line);
			line_count++;
		}

	
		//print the remaining file line by line
        while((c = wgetch(win)) != 27){
			if (c==32){
				if(fgets(line, sizeof(line), file)!=NULL){
					line[strcspn(line, "\r")] = '\0';
					line[strcspn(line, "\n")] = '\0';
					int len = strlen(line);
					if (len > WIN_WIDTH) {
						line[WIN_WIDTH] = '\0';
					}
					wprintw(win, "\n%s", line);
				}	
			}	
		}			
        delwin(win);
        delwin(frame);
        endwin();
		fclose(file);
        return 0;
}
