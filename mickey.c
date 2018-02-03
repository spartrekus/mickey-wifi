
////////////////////////////
///  Mickey-wifi, author: Spartrekus
///  Wifi Configuration, based on ncurses
///  Platform: PDP, debian, and *BSD*
///  Note: TC rocks!!
////////////////////////////


//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
#include <stdio.h>
#if defined(__linux__)
#define MYOS 1
#elif defined(_WIN32)
#define PATH_MAX 2500
#define MYOS 2
#elif defined(_WIN64)
#define PATH_MAX 2500
#define MYOS 3
#elif defined(__unix__)
#define MYOS 4
#define PATH_MAX 2500
#else
#define MYOS 0
#endif




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>



//////////////////////////
// ncurses
//#include <ncurses.h>
//////////////////////////
#if defined(__linux__)
#define MYOS 1
#include <ncurses.h>
#elif defined(_WIN32)
#define MYOS 2
#include <curses.h>
#elif defined(_WIN64)
#define MYOS 3
#include <curses.h>
#elif defined(__unix__)
#define MYOS 4
#include <ncurses.h>
#else
#define MYOS 0
#include <ncurses.h>
#endif

int rows, cols;  





void gfxcline( int myone, int mytwo , int mythree )
{
    //int trows, tcols;
    //getmaxyx( stdscr, trows , tcols);
    int foo;
    for( foo = mytwo ; foo <= mythree ; foo++) 
         mvaddch( myone , foo , ' ' );
}

void gfxhline( int myone, int mytwo , int mythree )
{
    //int trows, tcols;
    //getmaxyx( stdscr, trows , tcols);
    int foo;
    for( foo = mytwo ; foo <= mythree ; foo++) 
         mvaddch( myone , foo , ACS_HLINE );
}


void gfxvline( int liy )
{
      int fooxy = 0;
      getmaxyx( stdscr, rows, cols);
      for( fooxy = 1 ; fooxy <= cols-2 ; fooxy++) 
         mvaddch( liy , fooxy, ACS_HLINE );
}


void gfxyline( int liy )
{
      int fooxy = 0;
      getmaxyx( stdscr, rows, cols);
      for( fooxy = 0 ; fooxy <= cols- 1 ; fooxy++) 
         mvprintw( liy , fooxy, " " );
}

void gfxrectangle( int y1, int x1, int y2, int x2 )
{
    int foo, fooy , foox ;
    foo = x1;
    for( fooy = y1 ; fooy <= y2 ; fooy++) 
     for( foox = x1 ; foox <= x2 ; foox++) 
      mvaddch( fooy , foox , ' ' );
}



void gfxframe( int y1, int x1, int y2, int x2 )
{
    int foo, fooy , foox ;
    foo = x1;
    for( fooy = y1 ; fooy <= y2 ; fooy++) 
        mvaddch( fooy , foo , ACS_VLINE );
    foo = x2;
    for( fooy = y1 ; fooy <= y2 ; fooy++) 
         mvaddch( fooy , foo , ACS_VLINE );
    foo = y1;
    for( foox = x1 ; foox <= x2 ; foox++) 
         mvaddch( foo , foox , ACS_HLINE );
    foo = y2;
    for( foox = x1 ; foox <= x2 ; foox++) 
         mvaddch( foo , foox , ACS_HLINE );
    mvaddch( y1 , x1 , ACS_ULCORNER );
    mvaddch( y1 , x2 , ACS_URCORNER );
    mvaddch( y2 , x1 , ACS_LLCORNER );
    mvaddch( y2 , x2 , ACS_LRCORNER );
}


void colornorm()
{
    attroff( A_REVERSE );
    attroff( A_BOLD );
    color_set( 0, NULL );
}






//////////////////////////
//////////////////////////
//////////////////////////
//////////////////////////
void win_keypress()
{
  int win_key_gameover = 0;
  int ch = 0;
  while( win_key_gameover == 0)
  {
       erase();
       mvprintw( 0, 0, "Key Win Content" );
       mvprintw( 5,5, "%d", ch );
       ch = getch();
       if ( ch == 'i' ) 
           win_key_gameover = 1 ;
       else if ( ch == 'q' ) 
           win_key_gameover = 1 ;
  }
}




void crossgraphvga_colors(void)
{
  color_set( 7 , NULL ); attroff( A_REVERSE ); mvprintw( 2,2, "Darker  ;  Brighter (bold)" );
  
  getmaxyx( stdscr, rows, cols );

  int x = 5; int i = 1;
  for( i = 0; i <= rows-1 ; i++)  //ncurses as by default 8 colors
  { 
    mvprintw( x, 2 , "%d ", i );

    attron( A_REVERSE );
    attroff( A_BOLD );
    color_set( i , NULL );
    printw( "%d", i );
    colornorm(); printw( " " );

    attroff( A_REVERSE );
    attron(  A_BOLD );
    color_set( i , NULL );
    printw( " ; %d", i );
    colornorm(); printw( " " );

    // reverse and bold
    colornorm(); 
    color_set( i , NULL );
    attron( A_REVERSE );
    attroff( A_BOLD ); //for the console
    attron(  A_BLINK ); //for the console
    printw( " R%d", i );
    colornorm(); printw( " " );


    color_set( i , NULL );
    attron(  A_REVERSE );
    attron(  A_BOLD ); //for the console
    attroff( A_BLINK ); //for the console
    printw( " Rev,Bold%d", i );
    colornorm(); printw( " " );

    color_set( i , NULL );
    attron(  A_REVERSE );
    attron(  A_BOLD ); //for the console
    attron(  A_BLINK ); //for the console
    printw( " Rev,Bold,Blink%d", i );
    colornorm(); printw( " " );

    x += 1; 
    colornorm(); printw( " " );
    color_set( 7 , NULL ); printw( " (#.%d)", i );

    mvprintw( rows-1, cols-8, "|%d,%d|" , rows, cols );
  } 

  refresh();
  x += 2; 
  attroff( A_REVERSE );
  color_set( 7, NULL ); mvprintw(  x, 5 , "<Press Key>" );

  // clean up
  attroff( A_REVERSE ); 
  attroff( A_BOLD ); 
  attroff( A_BLINK ); 
  color_set( 0, NULL ); 
}








/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
int fexist(char *a_option)
{
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }

  // this is compatible to check if a file exists
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  // exists
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
}








////////////////////////////////////////////////////////////////////
char *strrlf(char *str) 
{     // copyleft, C function made by Spartrekus 
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if (str[i] != '\n' && str[i] != '\n') 
        ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}
////////////////////////////////////////////////////////////////////
char *strcut( char *str , int myposstart, int myposend )
{     // copyleft, C function made by Spartrekus 
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( ( str[i] != '\0' ) && ( str[i] != '\0') )
         if ( ( i >=  myposstart-1 ) && (  i <= myposend-1 ) )
           ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}






////////////////////////////////
void nwpapass( char *tessid, char *tpass )
{
       char cmdi[PATH_MAX];
       def_prog_mode();
       endwin();
       strncpy( cmdi , " wpa_passphrase  " , PATH_MAX );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , tessid , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "  " , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " \"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , tpass , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "\"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " > /etc/network/wifi.conf " , PATH_MAX - strlen( cmdi ) -1 );
       system( cmdi );
       reset_prog_mode();
}






////////////////////////////////
void nrunwith( char *theprg , char *thefile )
{
       char cmdi[PATH_MAX];
       def_prog_mode();
       endwin();
       strncpy( cmdi , "   " , PATH_MAX );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , theprg , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "  " , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " \"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , thefile , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "\"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       system( cmdi );
       reset_prog_mode();
}


////////////////////////////////
void nruncmd( char *thecmd   )
{
       char cmdi[PATH_MAX];
       def_prog_mode();
       endwin();
       strncpy( cmdi , "  " , PATH_MAX );
       strncat( cmdi , thecmd , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       system( cmdi );
       reset_prog_mode();
}









////////////////////////
////////////////////////
////////////////////////
////////////////////////
char *strninput( int mystarty, char *myinitstring )
{
   int strninput_gameover = 0; 
   char strmsg[PATH_MAX];
   char charo[PATH_MAX];
   strncpy( strmsg, myinitstring , PATH_MAX );
   int ch ;  int foo ; 
   int fooj; 
   while ( strninput_gameover == 0 )
   {
                  getmaxyx( stdscr, rows, cols);
                  attroff( A_REVERSE );

                  gfxrectangle( mystarty-2 , 0 , mystarty+2, cols -1 );
                  gfxframe(     mystarty-2 , 0 , mystarty+2, cols -1 );

                  for ( fooj = 1 ; fooj <= cols-2;  fooj++)
                    mvaddch( mystarty , fooj , ' ' );

                  mvprintw( mystarty , 5, ":> %s" , strrlf( strmsg ) );

                  attron( A_REVERSE );
                  printw( " " );
                  attroff( A_REVERSE );
                  attroff( A_REVERSE );
                  attroff( A_BOLD );
                  refresh() ; 

                  ch = getch();
   
		  if ( ch == 8 )  // for ssh on linux
		  {
		      strncpy( strmsg, strcut( strmsg, 1 , strlen( strmsg ) -1 )  ,  PATH_MAX );
	 	  } 

		  else if ( ch == 263 )  
		  {
		      strncpy( strmsg, strcut( strmsg, 1 , strlen( strmsg ) -1 )  ,  PATH_MAX );
	 	  } 

	          else if (
			(( ch >= 'a' ) && ( ch <= 'z' ) ) 
		        || (( ch >= 'A' ) && ( ch <= 'Z' ) ) 
		        || (( ch >= '1' ) && ( ch <= '9' ) ) 
		        || (( ch == '0' ) ) 
		        || (( ch == '~' ) ) 
		        || (( ch == '!' ) ) 
		        || (( ch == '&' ) ) 
		        || (( ch == '=' ) ) 
		        || (( ch == ':' ) ) 
		        || (( ch == ';' ) ) 
		        || (( ch == '<' ) ) 
		        || (( ch == '>' ) ) 
		        || (( ch == ' ' ) ) 
		        || (( ch == '|' ) ) 
		        || (( ch == '#' ) ) 
		        || (( ch == '?' ) ) 
		        || (( ch == '+' ) ) 
		        || (( ch == '/' ) ) 
		        || (( ch == '\\' ) ) 
		        || (( ch == '.' ) ) 
		        || (( ch == '$' ) ) 
		        || (( ch == '%' ) ) 
		        || (( ch == '-' ) ) 
		        || (( ch == ',' ) ) 
		        || (( ch == '{' ) ) 
		        || (( ch == '}' ) ) 
		        || (( ch == '(' ) ) 
		        || (( ch == ')' ) ) 
		        || (( ch == ']' ) ) 
		        || (( ch == '[' ) ) 
		        || (( ch == '*' ) ) 
		        || (( ch == '"' ) ) 
		        || (( ch == '@' ) ) 
		        || (( ch == '-' ) ) 
		        || (( ch == '_' ) ) 
		        || (( ch == '^' ) ) 
		        || (( ch == '\'' ) ) 
	             ) 
		  {
                           foo = snprintf( charo, PATH_MAX , "%s%c",  strmsg, ch );
			   strncpy( strmsg,  charo ,  PATH_MAX );
		  }
		  else if ( ch == 10 ) 
		  {
                        strninput_gameover = 1;
		  }
     }
     char ptr[PATH_MAX];
     strncpy( ptr, strmsg, PATH_MAX );
     size_t siz = sizeof ptr ; 
     char *r = malloc( sizeof ptr );
     return r ? memcpy(r, ptr, siz ) : NULL;
}


void nnewfile( char *fileinputsrc )
{
     FILE *fp;  
     fp = fopen( fileinputsrc , "wb+" );
     fputs( "\n" , fp );
     fclose( fp );
}

///////////////////////////////
///////////////////////////////
void nappendtofile( char *fileinputsrc, char *thestring )
{
     FILE *fp;  
     fp = fopen( fileinputsrc , "ab+" );
     fputs( thestring , fp );
     fclose( fp );
}



void drawit(void)
{
   int i;
   erase();
   color_set( 16, NULL );
   attroff( A_BOLD );
   attroff( A_UNDERLINE );
   attron( A_REVERSE );
   attroff( A_BOLD );
   gfxrectangle( 0, 0, rows-1 , cols -1 );

   colornorm();  i = 16;
   color_set( i , NULL );
   attron( A_REVERSE );
   attroff( A_BOLD ); //for the console
   attron(  A_BLINK ); //for the console
   mvprintw( 0, 1 , "WIFI CONFIGURATION" );
   gfxhline( 1, 1 , cols -2 );


}



///////////////////////////////////////////////////////////
int main( int argc, char *argv[])
{
   char cmdi[PATH_MAX];
   char fileoutput[PATH_MAX];
   strncpy( fileoutput, "/etc/network/interfaces.bak", PATH_MAX );
   FILE *fp;
   char usermsg[PATH_MAX];

   char myessid[PATH_MAX];
   char mypassword[PATH_MAX];
   strncpy( myessid,    "" , PATH_MAX );
   strncpy( mypassword ,  ""  , PATH_MAX );

   initscr();
   keypad(stdscr, true);
   curs_set( 0 );
   noecho();

   start_color();
   init_pair(0, COLOR_WHITE, COLOR_BLACK);
   init_pair(1, COLOR_RED, COLOR_BLACK);
   init_pair(2, COLOR_GREEN, COLOR_BLACK);
   init_pair(3, COLOR_BLUE, COLOR_YELLOW);
   init_pair(3, COLOR_BLUE, COLOR_BLACK);
   init_pair(4, COLOR_CYAN, COLOR_BLACK);
   init_pair(6, COLOR_YELLOW, COLOR_BLACK);
   init_pair(14, COLOR_WHITE, COLOR_BLUE);
   init_pair(15, COLOR_BLUE, COLOR_WHITE);
   init_pair(16, COLOR_BLUE, COLOR_YELLOW);
   init_pair(17, COLOR_BLACK, COLOR_WHITE);

   color_set( 2, NULL );



   int ch ; 
   int gameover = 0;
   while ( gameover == 0)
   {
           getmaxyx( stdscr, rows , cols);
           gfxrectangle( 0 , 0 , rows-1 , cols -1 );
           drawit();
	   refresh();

           colornorm();  
           color_set( 0 , NULL );
           attron( A_REVERSE );
           attroff( A_BOLD ); //for the console
           attron(  A_BLINK ); //for the console

           color_set( 15 , NULL );
           mvprintw( 4, 1, "ESSID          [Press Key: 1]:  %s" , myessid );
           mvprintw( 5, 1, "WPA2 PASSWORD  [Press Key: 2]:  %s", mypassword );
           mvprintw( 6, 1, "Install Wifi!  [Press Key: 5]:  ");
           mvprintw( 7, 1, "Test dhclient  [Press Key: 6]:  ");
           mvprintw( 8, 1, "Reboot!        [Press Key: 7]:  ");
           mvprintw( 9, 1, "Quit           [Press Key: 0]:  ");

           colornorm();
           ch = getch();
           if ( ch == 'C' ) 
           { crossgraphvga_colors( ); getch(); }

           else if ( ch == 'K' ) 
              win_keypress( );

           else if ( ch == ':' ) 
           {
              color_set( 17, NULL );
              strninput( rows/2 , "" );
           }

           else if ( ch == '1' ) 
           {
              color_set( 17, NULL );
              strncpy( myessid,     strninput( rows/2 , "" ), PATH_MAX );
           }

           else if ( ch == '2' ) 
           {
              color_set( 17, NULL );
              strncpy( mypassword , strninput( rows/2 , "" ), PATH_MAX );
           }

           else if ( ch == '5' ) 
           {
              color_set( 16, NULL );
              mvprintw( rows-1 , 1 , "Are you sure ? "); 

              color_set( 17, NULL );
              strncpy( usermsg, strninput( rows/2 , "Yes!" ), PATH_MAX );
              if ( strcmp( usermsg, "Yes!" ) == 0 )
              {

              nnewfile(      "/etc/network/interfaces" );
              nappendtofile( "/etc/network/interfaces" , "\n" );
              nappendtofile( "/etc/network/interfaces" , "\n" );
              nappendtofile( "/etc/network/interfaces" , "auto wlan0\n" ); 
              nappendtofile( "/etc/network/interfaces" , "iface wlan0 inet dhcp\n" ); 
              nappendtofile( "/etc/network/interfaces" , "wpa-conf /etc/network/wifi.conf\n" ); 
              nappendtofile( "/etc/network/interfaces" , "\n" );
              nappendtofile( "/etc/network/interfaces" , "\n" );

              nwpapass(  myessid,  mypassword );
              }
           }



           else if ( ch == '6' ) 
           {
                nruncmd( " dhclient -v wlan0 " );
           }

           else if ( ch == '7' ) 
           {
              color_set( 16, NULL );
              mvprintw( rows-1 , 1 , "Are you sure ? "); 
              color_set( 17, NULL );
              strncpy( usermsg, strninput( rows/2 , "Yes!" ), PATH_MAX );
              if ( strcmp( usermsg, "Yes!" ) == 0 )
              nruncmd( " reboot " );
           }

           else if ( ch == '0' ) 
           {
              gameover = 1;
           }

    }

    curs_set( 1 );
    endwin();			/* End curses mode		  */

    printf( "Call dhclient ... \n" );
    system( "  dhclient -v wlan0 " );
    printf( "Wifi Configuration: Bye ! \n" );
    return 0;
}



