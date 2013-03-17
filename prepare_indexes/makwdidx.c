/***********************************************************************/
/* Makeidx.c - the program which makes index of big file - list numbers*/
/*             of blocks begin. Used when need fast searching of the   */
/*             block with given number                                 */
/*                                                                     */
/* Copyright (C) Victor Bolotnikov, Tigers Ltd, 1997-1999              */
/*                                                                     */
/* Last edition: 10.10.99                                              */
/*                                                                     */
/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  MAX_BLOCK_LENGTH   200
#define  MAX_NUM_KEYWORDS   100
#define  MAX_LEN_LINE       100

#define  HALF_ENG_ALEPHBET  26
#define  HALF_RUS_ALEPHBET  33
#define  ENG_LETTERS_NUMBER (HALF_ENG_ALEPHBET<<1)
#define  RUS_LETTERS_NUMBER (HALF_RUS_ALEPHBET<<1)
#define  LEN_ASCII_TABLE    256

typedef  char LINE              [MAX_LEN_LINE];
typedef  char RUS_LETTERS_TABLE [RUS_LETTERS_NUMBER];
typedef  char ENG_LETTERS_TABLE [ENG_LETTERS_NUMBER];
typedef  char ASCII_TABLE       [LEN_ASCII_TABLE];

FILE  *f=NULL, *g=NULL, *k=NULL;
LINE  str;
LINE  lower_str;

LINE  kwds [MAX_NUM_KEYWORDS];
int   num_kwds = 0;

unsigned int index_number = 0;
int   found=0;
unsigned long  block_number=0;

const RUS_LETTERS_TABLE  rus_letters = {
    'á', 'â', '÷', 'ç', 'ä', 'å', '³', 'ö', 'ú', 'é',
    'ê', 'ë', 'ì', 'í', 'î', 'ï', 'ð', 'ò', 'ó', 'ô',
    'õ', 'æ', 'è', 'ã', 'þ', 'û', 'ý', 'ø', 'ù', 'ÿ',
    'ü', 'à', 'ñ', 'Á', 'Â', '×', 'Ç', 'Ä', 'Å', 'Å',
    'Ö', 'Ú', 'É', 'Ê', 'Ë', 'Ì', 'Í', 'Î', 'Ï', 'Ð',
    'Ò', 'Ó', 'Ô', 'Õ', 'Æ', 'È', 'Ã', 'Þ', 'Û', 'Ý',
    'Ø', 'Ù', 'ß', 'Ü', 'À', 'Ñ',
};

const ENG_LETTERS_TABLE eng_letters = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z',
};

ASCII_TABLE ascii_table;

/***************************************************************************/
static char Koi8_Char_Tolower (char ch) {
    unsigned short index = (unsigned char) ch;
    if (index>=LEN_ASCII_TABLE) {printf("Errror\n"); exit(0);}
    return ascii_table[index];
}

/***********************************************************************/
void Tolower_Init_Ascii_Table (void) {
  int i;
  for (i=0; i<256; i++)
    ascii_table[i] = (char) i;
  for (i=0; i<HALF_ENG_ALEPHBET; i++) {
    //printf ("%c->%c ",
    //  ascii_table[(unsigned char)eng_letters[i]], 
    //               eng_letters[i+HALF_ENG_ALEPHBET]);
    ascii_table[(unsigned char)eng_letters[i]] = 
           eng_letters[i+HALF_ENG_ALEPHBET];
  }
  for (i=0; i<HALF_RUS_ALEPHBET; i++) {
    //printf ("%c->%c ",
    //  ascii_table[(unsigned char)rus_letters[i]], 
    //               rus_letters[i+HALF_RUS_ALEPHBET]);
    ascii_table[(unsigned char)rus_letters[i]] = 
           rus_letters[i+HALF_RUS_ALEPHBET];
  }
}

/***************************************************************************/
void Tolower_String (char *src, char *dst) {
    short i;
    char tmp;
    src[MAX_LEN_LINE-1]='\0'; // well, to be sure
    for (i=0; src[i]; i++) {
       tmp = Koi8_Char_Tolower (src[i]);
       dst [i] = tmp;
    }
    dst [i] = '\0';
}




/***********************************************************************/
void open_files (int argc, char *argv[]) {
  if (argc!=3) {
    printf ("Usage: makewdidx <source_file> <kwds_file>\n");
    exit(-1);
  }

  f = fopen (argv[1], "r");
  if (f==NULL) {
     printf ("Cannot open source file '%s'\n", argv[1]);
     exit(-1);
  }

  k = fopen (argv[2], "r");
  if (k==NULL) {
     printf ("Cannot open keywords file '%s'\n", argv[2]);
     exit(-1);
  }
}

/***********************************************************************/
int Get_Keywords_Portion (void) {
  int i;
  num_kwds=0;
  while (fgets (str, MAX_LEN_LINE, k)!=NULL) {
    if (num_kwds==MAX_NUM_KEYWORDS-1) {
       printf ("Too many keywords");
       exit (-1);
    }
    if (strchr(str, '\n') != NULL)
       *(strchr(str, '\n')) = '\0';
    if (str[0] && str[0] != '\n' && str[0]!=' ' && str[0] != '\007') {
       Tolower_String (str, kwds[num_kwds]);
       num_kwds++;
    }
    else break;
  }

  printf ("Got %d keywords:\n", num_kwds);
  for (i=0; i<num_kwds; i++)
    printf ("'%s'\n", kwds[i]);
  return num_kwds;
}


/***********************************************************************/
void Open_Index_File (void) {
  char filename[80];
  sprintf (filename, "../indexes/idx%d.idx", index_number++);
  g = fopen (filename, "wb");
  if (g==NULL) {
     printf ("Cannot open output file '%s'\n", filename);
     exit(-1);
  }
}

/***********************************************************************/
int main (argc, argv)
int argc;
char *argv[];
{
  int i;
  Tolower_Init_Ascii_Table ();
  open_files (argc, argv);

  /***********************************************************************/
  while (Get_Keywords_Portion ()) {
    Open_Index_File ();
    rewind (f);
    block_number=0;
    while (fgets (str, MAX_LEN_LINE, f)!=NULL) {    /* for all blocks    */
      Tolower_String (str, lower_str);
      for (i=0; i<num_kwds && !found; i++) {
        if (strstr(lower_str, kwds[i]) != NULL)
            found = 1;
      }

      if (!str[0] || str[0]=='\n' || str[0]=='\r') { /* empty line:      */
        if (found)                                   /* end of the block */
            fwrite ((void *)&block_number, sizeof (block_number), 1, g);
        block_number++;
        found = 0;
      }
    }
    fclose (g);
  }

  fclose (f);
  fclose (k);
  return 0;
}
