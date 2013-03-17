/***********************************************************************/
/* an.c - the program which reads from file one random block           */
/*                                                                     */
/* Copyright (C) Victor Bolotnikov, Tigers Ltd, 1997.                  */
/*                                                                     */
/* Last edition: 24.06.97                                              */
/*                                                                     */
/* Known bugs: None                                                    */
/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/***********************************************************************/
#define TITLE      "Random-chosen russian anecdotes"
#define HEADER     " "
#define TEXT_FILE  "anecd.t"
#define INDEX_FILE "anecd.idx"

#define  MAX_LEN_LINE 200
typedef  char LINE    [MAX_LEN_LINE];

/***********************************************************************/
FILE *src=NULL, *idx=NULL;
LINE str;
long offs;

unsigned short blocks_number;         /* just a counter                */
unsigned short random_index   = 0;    /* random-chosen block index     */
unsigned long  offset_in_idx_file;    /* no comments                   */

/***********************************************************************/
void print_header (void) {
  printf ("Content-Type: text/html\n\n");
  printf ("\n");
  printf ("<html>\n");
  printf ("<head><title>%s</title></head>\n", TITLE);
  printf ( "<body>\n");
  printf ("<center><h4>%s</h4></center>\n", HEADER);
}

/***********************************************************************/
void print_tail (void) {
  printf ("</BODY>\n");
  printf ("</HTML>\n");
}

/***********************************************************************/
static  long filesize (FILE *stream) {
   long curpos, length;
   curpos = ftell(stream);
   fseek(stream, 0L, SEEK_END);
   length = ftell(stream);
   fseek(stream, curpos, SEEK_SET);
   return length;
}

/**********************************************************************/
static void error (char *msg) {
  printf ("%s\n\n", msg);
  print_tail ();
  if (src!=NULL) fclose (src);
  if (idx!=NULL) fclose (idx);
  exit (0);
}

/**********************************************************************/
static void open_files (void) {
  src = fopen (TEXT_FILE, "r");
  if (src==NULL) {
     printf ("Cannot open file %s\n", TEXT_FILE);
     error ("");
  }

  idx = fopen (INDEX_FILE, "rb");
  if (idx==NULL) {
     printf ("Cannot open file %s\n", INDEX_FILE);
     error ("");
  }
}

/**********************************************************************/
void main (void) {

  print_header ();
  open_files   ();
  blocks_number = (short)(filesize (idx) >> 2) - 2; /* 2 last numbers don't  */
                                                    /* take part in the game */
  srand (time(NULL));

/***********************************************************************/
  random_index = rand () % blocks_number;
  offset_in_idx_file = ((long)random_index) << 2;
  fseek (idx, offset_in_idx_file, SEEK_SET);
  fread ((void *)&offs, sizeof(offs), 1, idx);
  fseek (src, offs, SEEK_SET);
  while (fgets (str, MAX_LEN_LINE, src)!=NULL) {
    printf ("%s<BR>\n", str);
    if (!str[0] || str[0]=='\n' || str[0]=='\r') break;
  }

  fclose (src);
  fclose (idx);
  print_tail ();
}

