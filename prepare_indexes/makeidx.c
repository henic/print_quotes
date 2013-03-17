/***********************************************************************/
/* Makeidx.c - the program which makes index of big file - list offsets*/
/*             of blocks begin. Used when need fast searching of the   */
/*             block with given number                                 */
/*                                                                     */
/* Copyright (C) Victor Bolotnikov, Tigers Ltd, 1997.                  */
/*                                                                     */
/* Last edition: 18.04.97                                              */
/*                                                                     */
/* Known bugs:                                                         */
/*    Unexisting last block offset is saved. Nevermind, it's OK, pals  */
/***********************************************************************/

#include <stdio.h>
#include <string.h>

#define  MAX_LEN_LINE       200
typedef  char LINE    [MAX_LEN_LINE];

FILE *f=NULL, *g=NULL;
LINE str;
long offs=0L;

/***********************************************************************/
int main (argc, argv)
int argc;
char *argv[];
{
  if (argc!=3) {
     printf ("Usage: makeidx <source_file> <index_file>\n");
     return -1;
  }

  if (!strcmp (argv[1], argv[2])) {
     printf ("source and destination files should be different\n");
     return -1;
  }

  f = fopen (argv[1], "r");
  if (f==NULL) {
     printf ("Cannot open source file '%s'\n", argv[1]);
     return -1;
  }

  g = fopen (argv[2], "wb");
  if (g==NULL) {
     printf ("Cannot open output file '%s'\n", argv[2]);
     return -1;
  }

/***********************************************************************/
  fwrite ((void *)&offs, sizeof (offs), 1, g);        /* first block begin */
  while (!feof (f)) {                                 /* for all blocks    */
    if (fgets (str, MAX_LEN_LINE, f)==NULL) break;    /* read line         */
    if (!str[0] || str[0]=='\n' || str[0]=='\r') {    /* empty line is a   */
        offs = ftell(f);                              /* delimiter.        */
        fwrite ((void *)&offs, sizeof (offs), 1, g);  /* save offset       */
    }
  }

  fclose (f);
  fclose (g);
  return 0;
}
