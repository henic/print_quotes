/***********************************************************************/
/*                          Header.c                                   */
/***********************************************************************/

#include <stdio.h>
#include "an_r.h"
#include "an_prot.h"

/***********************************************************************/
/* random number is of the type long, so we have 4 random bytes        */
/***********************************************************************/
void Header_AnrPrint (void) {
  short *six_colors = Colors_Get_Six_Colors ();
  char  *stextcolor = Colors_Get_Text_Color ();
  printf ("Content-Type: text/html\n\n");
  printf ("<html>\n");
  printf ("<head><title>%s</title></head>\n", TITLE);
  printf ("<body bgcolor=\"#%02x%02x%02x\" fgcolor=\"#%02x%02x%02x\"\n",
            six_colors[0], six_colors[1], six_colors[2], 
            six_colors[3], six_colors[4], six_colors[5]);
  printf ("link=\"#0000EE\" vlink=\"#00008f\" alink=\"00008f\" text=%s>\n",
          stextcolor);
  printf ("<center><h4>%s</h4></center>\n", 
          Flags_Get_Language() ? HEADER_E : HEADER_R);
}

/***********************************************************************/
void Header_SearchPrint (void) {
  printf ("Content-Type: text/html\n\n");
  printf ( "<HTML>\n");
  printf ( "<HEAD><TITLE>Results of anecdotes searching</TITLE></HEAD>\n");
  printf ( "<H1>Your query results:</H1>\n");
  printf ( "<BODY><HR>\n");
}

/***********************************************************************/
void Header_TailPrint (void) {
  printf ("</BODY></html>\n");
}

