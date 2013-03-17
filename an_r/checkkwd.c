
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

     if (strstr(kwd, "���")!=NULL  ||
         strstr(kwd, "����")!=NULL  ||
         strstr(kwd, "����")!=NULL  ||
         strstr(kwd, "����")!=NULL  ||
         strstr(kwd, "����")!=NULL  ||
         strstr(kwd, "����")!=NULL  ||
         strstr(kwd, "�����")!=NULL  ||
         strstr(kwd, "�����")!=NULL  ||
         (strstr(kwd, "����")!=NULL &&
          strstr(kwd, "������")==NULL &&
          strstr(kwd, "�����")==NULL  &&
          strstr(kwd, "������")==NULL &&
          strstr(kwd, "�������")==NULL
         ) ||
         (strstr(kwd, "����")!=NULL &&
          strstr(kwd, "������")==NULL &&
          strstr(kwd, "������")==NULL &&
          strstr(kwd, "�������")==NULL
         ) ||
         strstr(kwd, "���")!=NULL ||
         strstr(kwd, "����")!=NULL) {
      printf ("<b><font size=5>\n");
      printf ("������� :-). ����� ������������ �������� - �� ��������������\n");
      printf ("� <a href=http://tiger.kulichki.net>�������</a><br>\n");
      printf ("</font></b><hr>\n");
      strcpy (kwd, "xxx");
     }
}


