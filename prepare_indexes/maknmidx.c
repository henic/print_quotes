#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  MAX_LEN_LINE       90
typedef  char LINE    [MAX_LEN_LINE];


FILE *f_text =NULL;
FILE *f_wnums=NULL;
FILE *f_ofidx=NULL;
FILE *f_nums =NULL;
FILE *f_words=NULL;

LINE s_name, s_wnums, s_ofidx, s_nums, s_words;
LINE current_word;

/* ----------------------------------------------------------- */
static int Open_Files (int argc, char *argv[]) {

  if (argc!=2) {
      printf ("Usage: %s <name_no_ext>\n",
              argv[0]);
      return 1;
  }

  if (strchr(argv[1], '.')!=NULL) {
	  printf ("Argument should not contain '.'\n");
	  return 1;
  }

  strcpy (s_name,  argv[1]);
  strcpy (s_wnums, argv[1]);
  strcpy (s_ofidx, argv[1]);
  strcpy (s_nums,  argv[1]);
  strcpy (s_words, argv[1]);

  strcat (s_name,  ".txt");
  strcat (s_wnums, ".wnm");
  strcat (s_ofidx, ".ofd");
  strcat (s_nums,  ".num");
  strcat (s_words, ".wrd");
  

  f_text = fopen (s_name, "r");
  if (f_text==NULL) {
     printf ("Cannot open file '%s'\n", s_name);
     return 1;
  }

  f_wnums = fopen (s_wnums, "r");
  if (f_wnums==NULL) {
     printf ("Cannot open file '%s'\n", s_wnums);
     return 1;
  }

  f_ofidx = fopen (s_ofidx, "wb");
  if (f_ofidx==NULL) {
     printf ("Cannot open file '%s'\n", s_ofidx);
     return 1;
  }

  f_nums = fopen (s_nums, "wb");
  if (f_nums==NULL) {
     printf ("Cannot open file '%s'\n", s_nums);
     return 1;
  }

  f_words = fopen (s_words, "w");
  if (f_words==NULL) {
     printf ("Cannot open file '%s'\n", s_words);
     return 1;
  }

  return 0;
}

/* ----------------------------------------------------------- */
static void Close_Files (void) {
    fclose (f_text);
    fclose (f_wnums);
    fclose (f_ofidx);
    fclose (f_nums);
    fclose (f_words);
}

/* ----------------------------------------------------------- */
void Find_Save (char *word, long num) {
  int  rc;
  long offset;

  if (strcmp (current_word, word)) {
     strcpy (current_word, word);
     fprintf(f_words,"%s\n", word);
     offset = ftell (f_nums);
     rc = fwrite (&offset, sizeof(offset), 1, f_ofidx);
     if (!rc) printf ("Error fwrite failed\n");
  }
  rc = fwrite (&num, sizeof (long), 1, f_nums);
}

/* ----------------------------------------------------------- */
int main (int argc, char *argv[]) {
    LINE str;
    LINE word;
    long num;
    long cnt=0L;
    int  rc;

    if (Open_Files(argc, argv))
        return -1;

    current_word[0]='\0';
    while (fgets (str, MAX_LEN_LINE, f_wnums) != NULL) {
        cnt++;
        rc = sscanf (str, "%s %ld", word, &num);
        if (rc!=2) {
           printf ("str #%ld: failed sscanf from '%s'\n", cnt, str);
           break;
        }
        if (!strcmp(word, "вася"))
           cnt=cnt;
        Find_Save(word, num);
    }
    Close_Files ();
    return 0;
}

