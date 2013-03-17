
#include <stdio.h>
#include <string.h>

#include "an_r.h"
#include "an_prot.h"

/***************************************************************************/
void Check_Keyword_Is_OK (char *kwd) {
     if (kwd==NULL) {
        Error("Unexpected NULL keyword", 1);
        return;
     }

     if (strstr(kwd, "хуй")!=NULL  ||
         strstr(kwd, "пизд")!=NULL  ||
         strstr(kwd, "говн")!=NULL  ||
         strstr(kwd, "срат")!=NULL  ||
         strstr(kwd, "срал")!=NULL  ||
         strstr(kwd, "срак")!=NULL  ||
         strstr(kwd, "залуп")!=NULL  ||
         strstr(kwd, "блядь")!=NULL  ||
         (strstr(kwd, "ебат")!=NULL &&
          strstr(kwd, "хлебат")==NULL &&
          strstr(kwd, "дебат")==NULL  &&
          strstr(kwd, "гребат")==NULL &&
          strstr(kwd, "колебат")==NULL
         ) ||
         (strstr(kwd, "ебал")!=NULL &&
          strstr(kwd, "хлебал")==NULL &&
          strstr(kwd, "гребал")==NULL &&
          strstr(kwd, "колебал")==NULL
         ) ||
         strstr(kwd, "жоп")!=NULL ||
         strstr(kwd, "ебан")!=NULL) {
      printf ("<b><font size=5>\n");
      printf ("Цензура :-). Поиск непристойных словечек - по договоренности\n");
      printf ("с <a href=http://tiger.kulichki.net>автором</a><br>\n");
      printf ("</font></b><hr>\n");
      strcpy (kwd, "xxx");
     }
}


