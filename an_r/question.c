
/***********************************************************************/
/*                          Question.c                                 */
/***********************************************************************/

#include <stdio.h>
#include "an_r.h"

void Print_Question (int need_question, long random_number) {
#ifndef TEST_VERSION
  FILE *fquest;
  int i, rand_question;
  LINE qstr;

  if (!need_question) return;
  fquest=fopen (QUEST_FILE_R, "r");
  if (fquest==NULL) return;
  rand_question = (int) (random_number % MAX_QUESTION);
  for (i=0; i<rand_question; i++)
     fgets (qstr, MAX_LEN_LINE, fquest);
  fclose (fquest);

  if (!qstr[0] || qstr[0]=='\n') return;
  printf ("<hr><br>\n");
  printf ("<center>\n");
  printf ("<font size=+1>Блиц-опрос</font><br>\n");
  printf ("%s<br>\n", qstr);
  printf ("<input type=submit name=a value=\"%s\">\n", ANSWER_NO);
  printf ("&nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp\n");
  printf ("<input type=submit name=a value=\"%s\">\n", ANSWER_YES);
  printf ("</form>\n");
  printf ("</center>\n");
  printf ("<hr>\n");
#endif
}

