/* split text file into tokens one per line */

#include <stdio.h>
#include <string.h>

      FILE  *f, *g;


// -----------------------------------------------------
int is_delimiter (char c) {
  return (strchr (" \t\n\r\007\012,.:!?~`\'\"()-=", c)!=NULL);
}

// -----------------------------------------------------
static int Open_Files (int argc, char *argv[]) {

      if (argc!=3) {
          printf ("Usage: %s <infile><outfile>\n", argv[0]);
          return -1;
      }

      if (!strcmp (argv[1], argv[2])) {
          printf ("Input and output files should be different\n");
          return -1;
      }

      f = fopen(argv[1], "r");
      if (f==NULL) {
          fprintf(stderr, "Can't open '%s'\n", argv[1]);
          return -1;
      }

      g = fopen (argv[2], "w");
      if (g==NULL) {
          printf ("Can't open file '%s'\n", argv[2]);
          return -1;
      }
      return 0;
}

// -----------------------------------------------------
int main(int argc, char *argv[]) {
      int   c, wordlen=0;
      long  linect=0l;
      long num_blocks = 0;
      int eoln=0;

      if (Open_Files(argc, argv)) return -1;

      while ((c = getc(f)) != EOF) {
        if (is_delimiter (c)) {             // delimiter
           if (wordlen) {
               fprintf (g, " %ld\n", num_blocks);
           }
           if (c=='\n') {
	       linect++;
               if (! (linect % 1000))
                  printf ("%ld\r", linect);
               if (eoln) num_blocks++;
               eoln=1;
	   }
           else
               eoln=0;
           wordlen = 0;
	}
        else {                              // usual character
           putc (c, g);
           wordlen++;
           eoln=0;
	}
      }
      fclose(f);
      fclose(g);
      printf ("%ld blocks\n", num_blocks);
      return 0;
}
