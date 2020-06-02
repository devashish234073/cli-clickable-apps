#include <curses.h>
#include <stdio.h>

int minX[3][3];
int minY[3][3];
int maxX[3][3];
int maxY[3][3];
int cX[3][3];
int cY[3][3];
int debug = 1;

void printbox(int boardX,int boardY,int x,int y){
  minX[boardX][boardY]=x;
  minY[boardX][boardY]=y;
  maxX[boardX][boardY]=x+6;
  maxY[boardX][boardY]=y+4;
  cX[boardX][boardY]=x+3;
  cY[boardX][boardY]=y+2;

  move(y++,x);
  addstr("*******");
  move(y++,x);
  addstr("*     *");
  move(y++,x);
  addstr("*     *");
  move(y++,x);
  addstr("*     *");
  move(y++,x);
  addstr("*******");
}

void markbox(int boardX,int boardY){
  int x=minX[boardX][boardY];
  int y=minY[boardX][boardY];
  move(y++,x);
  addstr("-------");
  move(y++,x);
  addstr("-     -");
  move(y++,x);
  addstr("-     -");
  move(y++,x);
  addstr("-     -");
  move(y++,x);
  addstr("-------");
}

int board[3][3];

void resetBoard(){
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      board[i][j]=-1;
    }
  }
}

int playerWon=-1;
int gameover = 0;
char currChar='X';
int boxesFilled = 0;
void switchChar(){
  if(currChar=='X'){
    currChar='O';
  } else {
    currChar='X';
  }
}

int won[6];

int playAt(int x,int y){
  if(gameover==1){
    return -1;
  }
  if(boxesFilled>=9){
    gameover = 1;
    return -1;
  }
  if(board[x][y]!=-1){
    return -1;
  }
  board[x][y]=currChar;
  boxesFilled++;
  switchChar();
  if(board[0][0]!=-1 && board[0][0]==board[0][1]){
    if(board[0][0]==board[0][2]){
      playerWon=board[0][0];
      gameover = 1;
    }
  } else if(board[0][0]!=-1 && board[0][0]==board[1][0] && board[0][0]==board[2][0]){
      won[0]=cX[0][0];won[1]=cY[0][0];
      won[2]=cX[1][0];won[3]=cY[1][0];
      won[4]=cX[2][0];won[5]=cY[2][0];
      playerWon=board[0][0];
      gameover = 1;
  } else if(board[0][0]!=-1 && board[0][0]==board[1][1] && board[0][0]==board[2][2]){
      won[0]=cX[0][0];won[1]=cY[0][0];
      won[2]=cX[1][1];won[3]=cY[1][1];
      won[4]=cX[2][2];won[5]=cY[2][2];
      playerWon=board[0][0];
      gameover = 1;
  } else if(board[2][2]!=-1 && board[2][2]==board[1][2] && board[2][2]==board[0][2]){
      won[0]=cX[0][2];won[1]=cY[0][2];
      won[2]=cX[1][2];won[3]=cY[1][2];
      won[4]=cX[2][2];won[5]=cY[2][2];
      playerWon=board[2][2];
      gameover = 1;
  } else if(board[2][2]!=-1 && board[2][2]==board[2][1] && board[2][2]==board[2][0]){
      won[0]=cX[2][0];won[1]=cY[2][0];
      won[2]=cX[2][1];won[3]=cY[2][1];
      won[4]=cX[2][2];won[5]=cY[2][2];
      playerWon=board[2][2];
      gameover = 1;
  } else if(board[1][1]!=-1 && board[1][1]==board[0][1] && board[1][1]==board[2][1]){
      won[0]=cX[0][1];won[1]=cY[0][1];
      won[2]=cX[1][1];won[3]=cY[1][1];
      won[4]=cX[2][1];won[5]=cY[2][1];
      playerWon=board[1][1];
      gameover = 1;
  } else if(board[1][1]!=-1 && board[1][1]==board[1][0] && board[1][1]==board[1][2]){
      won[0]=cX[1][0];won[1]=cY[1][0];
      won[2]=cX[1][1];won[3]=cY[1][1];
      won[4]=cX[1][2];won[5]=cY[1][2];
      playerWon=board[1][1];
      gameover = 1;
  } else if(board[1][1]!=-1 && board[1][1]==board[2][0] && board[1][1]==board[0][2]){
      won[0]=cX[0][2];won[1]=cY[0][2];
      won[2]=cX[1][1];won[3]=cY[1][1];
      won[4]=cX[2][0];won[5]=cY[2][0];
      playerWon=board[1][1];
      gameover = 1;
  }
  if(debug){
    int line = 25;
    move(line,0);
    printw("[0][0]=%d",board[0][0]);
    move(line,11);
    printw("[0][1]=%d",board[0][1]);
    move(line++,22);
    printw("[0][2]=%d",board[0][2]);

    move(line,0);
    printw("[1][0]=%d",board[1][0]);
    move(line,11);
    printw("[1][1]=%d",board[1][1]);
    move(line++,22);
    printw("[1][2]=%d",board[1][2]);

    move(line,0);
    printw("[2][0]=%d",board[2][0]);
    move(line,11);
    printw("[2][1]=%d",board[2][1]);
    move(line++,22);
    printw("[2][2]=%d",board[2][2]);
  }
  return board[x][y];
}
 
int main()
{
  resetBoard();
  initscr();
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_GREEN);
  init_pair(2, COLOR_BLUE, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);
  cbreak();
  noecho();

  printbox(0,0,2,2);
  printbox(0,1,10,2);
  printbox(0,2,18,2);
  
  printbox(1,0,2,7);
  printbox(1,1,10,7);
  printbox(1,2,18,7);

  printbox(2,0,2,12);
  printbox(2,1,10,12);
  printbox(2,2,18,12);  

  // Enables keypad mode. This makes (at least for me) mouse events getting
  // reported as KEY_MOUSE, instead as of random letters.
  keypad(stdscr, TRUE);
  // Don't mask any mouse events
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

  printf("\033[?1003h\n"); // Makes the terminal report mouse movement events

  for (;;) { 
    int c = wgetch(stdscr);
    // Exit the program on new line fed
    if (c == '\n')
      break;
    if (c == KEY_MOUSE) {
      MEVENT event;
      if (getmouse(&event) == OK){
        for(int i=0;i<=2;i++){
         for(int j=0;j<=2;j++){
          if(event.x>minX[i][j] && event.x<maxX[i][j]){
           if(event.y>minY[i][j] && event.y<maxY[i][j]){
            int ret = playAt(i,j);
            if(ret!=-1){
              markbox(i,j);
              move(cY[i][j],cX[i][j]);
              if(playerWon!=-1){
                attron(COLOR_PAIR(1));
                move(won[1],won[0]);
                addch((char)ret);
                move(won[3],won[2]);
                addch((char)ret);
                move(won[5],won[4]);
                addch((char)ret);
                move(1,0);
                printw("player won %c",(char)playerWon);
              } else {
                if((char)ret=='X'){
                  attron(COLOR_PAIR(2));
                  addch((char)ret);
                  attroff(COLOR_PAIR(2));
                } else if((char)ret=='O'){
                  attron(COLOR_PAIR(3));
                  addch((char)ret);
                  attroff(COLOR_PAIR(3));
                } 
              }
            } else {
              if(gameover==1){
                move(0,0);
                addstr("game over! Press ENTER to exit.");
              }
            }
            break;
           }
          }
         }
        }
      }
    }
  }
 
  printf("\033[?1003l\n"); // Disable mouse movement events, as l = low

  endwin();
 
  return 0;
}

