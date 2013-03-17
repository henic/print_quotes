#include <stdio.h>
#include <string.h>

#define  MAX_LEN_LINE       200
typedef  char LINE    [MAX_LEN_LINE];

int main (int argc, char *argv[]) {

  FILE *f=NULL, *g=NULL;
  LINE str, word;
  int num;
  int minlen;
  int rc;

  if (argc!=4) {
    printf ("Usage: %s <input_file> <outfile> <minlength>\n", argv[0]);
    return -1;
  }

  f = fopen (argv[1], "r");
  if (f==NULL) {
     printf ("Cannot open files '%s'\n", argv[1]);
     return -1;
  }

  g = fopen (argv[2], "w");
  if (g==NULL) {
     printf ("Cannot open files '%s'\n", argv[2]);
     return -1;
  }

  rc = sscanf(argv[3], "%d", &minlen);
  if (rc!=1 || minlen<=2) {
    printf ("integer minlength greater than 2 expected\n");
    return -1;
  }

  while (fgets (str, MAX_LEN_LINE, f) != NULL) {
    if (sscanf (str, "%s %d", word, &num) != 2) {
        printf ("Sscanf failed on the string '%s'\n", str);
        break;
    }
    if (strlen(word) >=minlen)
        fprintf (g, "%s", str);
  }
  fclose (f);
  fclose(g);
  return 0;
}

