/***************************************************************************/
/*                              Search.c                                   */
/***************************************************************************/

#include <stdio.h>

#include "an_r.h"

const LINE search_list[] = {
"��������",      "��������",    "�������",   "������",      "���������",
"�������",       "������",      "������",    "������",      "������",
"���������",     "������",      "��������",  "�����������", "���",
"������",        "������",      "������",    "��������",    "�������",
"�������",       "�����",       "��������",  "�����",       "�����",
"��������",      "����",        "������",    "�������",     "������",
"�������",       "��������",    "�������",   "�������",     "�������",
"���������",     "���������",   "���������", "�����",       "�����",
"������",        "����",        "�����",     "���",         "����",
"����",          "���������",   "�������",   "�����",       "�����",
"����",          "����",        "�����",     "�����",       "�����",
"����",          "������",      "������",    "�����",       "�������",
"�����",         "�����",       "�������",   "������",      "�������",
"�����",         "�����",       "�����",     "�����",       "�����",
"����",          "������",      "�����",     "������",      "�����",
"�����",         "�����",       "�����",     "����",        "����",
"����",          "�������",     "���",       "����",        "�����",
"����",          "������",      "�������",   "�������",     "���������",
"���������",     "�����",       "�������",   "����",        "������",
"���������",     "�������",     "������",    "����",        "����",
"�����",         "����",        "����",      "�����",       "�����",
"������",        "����",        "�������",   "�����",       "������",
"�������",       "�������",     "�������",   "�����",       "�����",
"����",          "����",        "����",      "�������",     "�����",
"����",          "����",        "����",      "�������",     "������",
"���",           "����",        "�������",   "��������",    "����",
"������",        "���������",   "�����",     "�����",       "�����",
"�����",         "�����",       "�����������", "����������","���",
"�����",         "�����",       "����",      "�����",       "������",
"�����",         "����������",  "���������", "������",      "�����",
"�������",       "��������",    "���",       "�����",       "������",
"�������",       "�������",     "�������",   "�����",       "�����",
"������",        "�����",       "���",       "�����",       "��������",
"������",        "������",      "���������", "�����",       "������",
"�������",       "���������",   "�������",   "������",      "������",
"�����",         "�������",     "��������",  "��������",    "������",
"������",        "������",      "������",    "������",      "�������",
"��������",      "��������",    "��������",  "�����",       "������",
"�����",         "����������",  "������",    "�����",       "�������",
"�������",       "��������",    "subj",      "����",        "����",
"�������",       "�������",     "����",      "��������",    "�������",
"�������",       "������",      "������",    "�������",     "�����",
"������",        "�����",       "�����",     "�����",       "�����",
"�������",       "����",        "������",    "������",      "���������",
"�������",       "����",        "������",    "������",      "������",
"upsa",          "����",        "������",    "������",      "�������",
"���������",     "�����",       "�����",     "������",      "����",
"������",        "���",         "����",      "���",         "�����",
"����",          "����",        "����",      "�������",     "������",
"�����",         "�������",     "����",      "����",        "������",
"����",          "������",      "������",    "�������",     "������",
"������",        "���",         "�����",     "����",        "�������",
"������",        "������",      "�����",     "�����",       "�����",
"�������",       "����",        "����",      "�����������", "���������",
"�������",       "������",      "��������",  "�����",       "������",
"�����",         "��������",    "���",       "�����",       "�����",
"��������",      "�����",
};

const int max_kwd = sizeof (search_list) / sizeof (LINE);

/**********************************************************************/
void Search_Print (long random_number) {
  if (Flags_Get_Language() == ENGLISH)
     return;
  printf ("<form action=%s method=POST target=_blank>\n", SEARCH_PATH);
  printf ("<a href=/an_search.htm>�����������</a>\n");
  printf (" ����� ��������� &nbsp\n");
  printf ("<input type=text name=p size=35 value=\"%s\">\n",
            search_list[(int)(random_number % max_kwd)]);
  printf ("<input type=submit value=\"�����\">\n");
  printf ("</form>\n");
  printf ("<hr>\n");
}

