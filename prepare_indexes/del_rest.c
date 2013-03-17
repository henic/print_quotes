#include <stdio.h>
#include <string.h>

#define  MAX_LEN_LINE       200
typedef  char LINE    [MAX_LEN_LINE];

void main (int argc, char *argv[]) {

FILE *f, *g=NULL;
LINE str1, str2;

  if (argc!=3) {
     printf ("Usage: del_rest <input_file> <output_file>\n");
     return;
  }

  if (!strcmp (argv[1], argv[2])) {
     printf ("Source and result files should be different\n");
     return;
  }

  f = fopen (argv[1], "r");
  if (f==NULL) {
     printf ("Cannot open file '%s'\n", argv[1]);
     return;
  }

  g=fopen(argv[2], "w");
  if (g==NULL) {
     printf ("Cannot open file '%s'\n", argv[2]);
     return;
  }


  fgets (str1, MAX_LEN_LINE, f);
  while (!feof (f)) {
    strcpy (str2, str1);
    do {
        fgets (str1, MAX_LEN_LINE, f);
    } while (! strcmp(str1, str2) && !feof(f));
    fprintf(g, "%s", str2);
  }
    
  fclose (f);fclose (g);
}
