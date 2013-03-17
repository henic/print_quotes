
/***************************************************************************/
#include <stdio.h>
#include <string.h>

#define  MAX_LEN_LINE         220

#define  RUS_LETTERS_NUMBER   66
#define  HALF_ALEPHBET        33
#define  LEN_ASCII_TABLE      256

typedef  char LINE          [MAX_LEN_LINE];
typedef  char ASCII_TABLE   [LEN_ASCII_TABLE];
typedef  char LETTERS_TABLE [RUS_LETTERS_NUMBER];


/***************************************************************************/
FILE *f_src = NULL,
     *f_dst = NULL;

ASCII_TABLE ascii_table;

const LETTERS_TABLE  koi_letters = {
    'á', 'â', '÷', 'ç', 'ä', 'å', '³', 'ö', 'ú', 'é',
    'ê', 'ë', 'ì', 'í', 'î', 'ï', 'ð', 'ò', 'ó', 'ô',
    'õ', 'æ', 'è', 'ã', 'þ', 'û', 'ý', 'ø', 'ù', 'ÿ',
    'ü', 'à', 'ñ', 'Á', 'Â', '×', 'Ç', 'Ä', 'Å', 'Å',
    'Ö', 'Ú', 'É', 'Ê', 'Ë', 'Ì', 'Í', 'Î', 'Ï', 'Ð',
    'Ò', 'Ó', 'Ô', 'Õ', 'Æ', 'È', 'Ã', 'Þ', 'Û', 'Ý',
    'Ø', 'Ù', 'ß', 'Ü', 'À', 'Ñ',
};

/***********************************************************************/
static int Open_Files (int argc, char *argv[]) {

  if (argc!=3) {
     printf ("Usage: Tolower <infile> <outfile>\n");
     return -1;
  }

  if (! strcmp (argv[1], argv[2])) {
     printf ("Arguments should differ\n");
     return -1;
  }

  f_src = fopen (argv[1], "r");
  if (f_src==NULL) {
     printf ("Cannot open file %s", argv[1]);
     return -1;
  }
  
  f_dst = fopen (argv[2], "w");
  if (f_dst=NULL) {
     printf ("Cannot open file %s", argv[2]);
     return -1;
  }

  return 0;
}

/***********************************************************************/
static void Close_Files (void) {
    if (f_src !=NULL) fclose (f_src);
    if (f_dst !=NULL) fclose (f_dst);
}


/***********************************************************************/
static void init_ascii_table (void) {
  int i;
  for (i=0; i<256; i++)
    ascii_table[i] = (char) i;
  for (i=0; i<HALF_ALEPHBET; i++) {
   //printf ("%c->%c ",
   //ascii_table[(unsigned char)koi_letters[i]], koi_letters[i+HALF_ALEPHBET]);
     ascii_table[(unsigned char)koi_letters[i]] = koi_letters[i+HALF_ALEPHBET];
  }
  //printf ("\n");
}

/***************************************************************************/
static char koi8_char_tolower (char ch) {
   return ascii_table[(unsigned char)ch];
}

/***************************************************************************/
static void koi8_string_tolower (char *src, char *dst) {
	short i;
	char tmp;
	src[MAX_LEN_LINE-1]='\0'; // well, to be sure
	for (i=0; src[i] && src[i]!='\n'; i++) {
		tmp = koi8_char_tolower (src[i]);
		dst [i] = tmp;
	}
	dst [i] = '\0';
}

/***************************************************************************/
int main (int argc, char *argv[]) {
  unsigned int i;
  unsigned long words_cnt=0L;
  int rc;
  LINE str, res;

  init_ascii_table ();

  if (Open_Files(argc, argv)) 
      return -1;
  
/***************************************************************************/
/*                  the main loop: find required blocks                    */
/***************************************************************************/
  while (fgets (str, MAX_LEN_LINE, f_src) != NULL) {
    koi8_string_tolower (str, res); 
    printf ("%s\n", res);
    //fprintf (f_dst, "%s\n", res);
    printf ("%d\n", strlen(res));
    fputs (res, f_dst);
  }

/**************************************************************************/
  Close_Files();
  return 0;
}

