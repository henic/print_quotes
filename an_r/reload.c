/**********************************************************************/
/*                             Reload.c                               */
/**********************************************************************/

#include <stdio.h>
#include "an_r.h"

void Reload_Button_Print (short advanced_version,
                          short repeats_number, 
                          long  random_number) {

  printf ("<center>\n");
  printf ("<font size=+4>\n");
  if (Flags_Get_Language()) {
       printf ("<input type=submit value=\"More\"><br>\n");
  }
  else {
    if (!(random_number%10))
       printf ("<input type=submit value=\"éÓÞÏ!\"><br>\n");
    else
       printf ("<input type=submit value=\"åÝÅ!\"><br>\n");
  }

  printf ("</font>\n");
  printf ("</center>\n");
  printf ("\n");
}

