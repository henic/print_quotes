/***********************************************************************/
/*                      Set of service functions                       */
/***********************************************************************/

#include <stdio.h>
#include "an_r.h"
#include "an_prot.h"

void Error (char *msg, int ProgramError) {
  printf ("<center><font size=+2><b>%s</b></font></center>\n\n", msg);
  if (ProgramError) {
    printf("    <form method=post action=\"%s\">\n", FORMMAIL_PATH);
    printf("\n");
    printf("<input type=hidden name=title value=\"Error Form Results\">\n");
    printf(
    "<input type=hidden name=return_link_title value=\"Back to Main Page\">\n");
    printf("    <input type=hidden name=text_color value=navy>\n");
    printf("\n");
    printf("    <input type=hidden name=\"return_link_url\"\n");
    printf("          value=\"http://www.kulichki.com%s?%s\">\n", 
          Get_Program_Path(), Get_Args_Str());
    printf("    <input type=hidden name=redirect\n");
    printf("         value=\"http://www.kulichki.com%s?%s\">\n", 
          Get_Program_Path(), Get_Args_Str());
    printf("\n");
    printf("    <input type=hidden name=subject  value=\"%s\">\n", msg);
    printf("<input type=hidden name=required value=\"recipient\"><br>\n");
    printf("\n");
    printf("<input type=hidden name=recipient size=30 value=\"%s\"><br>\n",
           TIGER_EMAIL);
    printf("<input type=hidden name=params value=%s>\n", Get_Args_Str());
    printf("Please <font size=+1><input TYPE=submit \n");
    printf("VALUE=\"Send\"></font> this info to \n");
    printf("<a href=/~tiger>author</a><br><br>\n");
    printf("</form>\n");
  }
  /*Header_TailPrint ();*/
  printf ("</body></html>\n");
  Files_Close ();
  exit (0);
}

