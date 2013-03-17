/***********************************************************************/
/*                              Print.c                                */
/***********************************************************************/

#include <stdio.h>
#include <string.h>

#include "an_r.h"
#include "an_s.h"
#include "an_prot.h"
#include "flags.h"

static char Empty_String[10] = "";

#define MAX_ADV 20
unsigned int advrt_idx;
LINE advrt[MAX_ADV] = {
 "Новости",       "Новини",        "Всякости",      "Разности",
 "Ящик пива",     "Море сексу",    "Hadashot",      "Сюды",
 "Самореклама",   "Ждем-с",        "News",          "Всячина",
 "Приглашаем",    "Не реклама",    "Новый раздел",  "Путь в никуда",
 "Для взрослых",  "Не промахнись", "Метро",         "Вам не сюда"
};

LINE themes[MAX_NUM_THEMES] = {
 "Вовочка", "Штирлиц", "Секс",     "Чапаев", "Ржевский",
 "Грузины", "Евреи",   "Наркоман", "Ельцин", "Чукчи"
}; 

static char *KTypeIsChecked (int i) {
 return (Flags_Get_Keyword_Type()==i) ?
            "checked" : Empty_String;
}

static char *GetFirstKWD (void) {
 return (Keywords_Get_Size() ? Keywords_Get(0) : Empty_String);
}

/***********************************************************************/
void Print_Config (void) {
  int i;
  short language         = Flags_Get_Language();
  int advanced_version   = Flags_Get_Advanced_Version();
  int repeats_number     = Flags_Get_Repeats_Number ();
  long int random_number = Flags_Get_Random_Number ();
  long int start_number  = Flags_Get_Random_Choosing() ?
                             0 : 
                             Flags_Get_Start_Number ()+repeats_number;

  printf ("<form action=%s method=GET>\n", Get_Program_Path ()); 
  printf (language ? "Select " : "Выбрать ");
  
  // random - sequential
  printf ("<select name=r>\n");
  printf ("<option value=0 %s>sequent\n",
          Flags_Get_Random_Choosing() ? "" : "selected");
  printf ("<option value=1 %s>random\n",
          (! Flags_Get_Random_Choosing()) ? "" : "selected");
  printf ("</select>\n");

  // required number of blocks 
  printf ("<font size=+0>\n");
  if (advanced_version) {
    printf ("<select name=n>\n");
    for (i=2; i<11; i++)
      if (i!=8 && i!=9) {
        if (i==repeats_number)
           printf ("<option value=%d selected>%d\n", i, i);
        else
           printf ("<option value=%d>%d\n", i, i);
      }
    printf ("</select>\n");
  }
  printf ("</font>\n");
  printf (language ? "jokes " : "анекдотов ");

  // start number
  if (language) {
  printf ("starting from <input type=input name=s size=5 value=%ld><br>\n", 
          start_number); 
  printf ("<input type=radio name=k value=%d %s>in whole file<br>\n",
               UNDEFINED_KEYWORD, KTypeIsChecked(UNDEFINED_KEYWORD));
/*
  printf ("<input type=radio name=k value=%d %s>by the theme\n",
               PREDEFINED_KEYWORD, KTypeIsChecked(PREDEFINED_KEYWORD));
*/
  // reduce database
  } else {

  printf ("начиная с номера <input type=input name=s size=5 value=%ld><br>\n", 
          start_number); 
  printf ("<input type=radio name=k value=%d %s>По всему файлу<br>\n",
               UNDEFINED_KEYWORD, KTypeIsChecked(UNDEFINED_KEYWORD));
  printf ("<input type=radio name=k value=%d %s>По данной теме\n",
               PREDEFINED_KEYWORD, KTypeIsChecked(PREDEFINED_KEYWORD));
  printf ("<select name=t>\n"); 
  for (i=0; i<MAX_NUM_THEMES; i++)
    if (i==Flags_Get_Theme())
        printf ("<option value=%d selected>%s\n", i, themes[i]);
    else
        printf ("<option value=%d>%s\n", i, themes[i]);
  printf ("</select><br>\n");
  }

  if (language)
  printf ("<input type=radio name=k value=%d %s>Contain the word\n",
          USER_DEFINED_KEYWORD, KTypeIsChecked(USER_DEFINED_KEYWORD));
  else
  printf ("<input type=radio name=k value=%d %s>Содержащие слово\n",
          USER_DEFINED_KEYWORD, KTypeIsChecked(USER_DEFINED_KEYWORD));
  printf ("<input type=text  name=p size=35 value=%s><br>\n", GetFirstKWD());
 
  printf ("<input type=hidden name=v value=%d>\n", advanced_version);
  printf ("<input type=hidden name=e value=%d>\n", language);
  printf ("<input type=hidden name=z value=%d>\n", random_number);
}

/***********************************************************************/
void Print_Links (int advanced_version) {
  short language         = Flags_Get_Language ();

  printf ("<br><font size=2>\n");
  if (language) {
   printf ("<a href=\"http:%s?v=%d\">Russian version</a>\n", 
               PROGRAM_PATH_R, advanced_version); 
  } else {
    if (advanced_version)
      printf ("<a href=\"http:%s?v=0\">Мини-версия</a> |\n", 
               PROGRAM_PATH_R);
    else
      printf ("<a href=\"http:%s?v=1\">Полная версия</a> |\n", 
               PROGRAM_PATH_R, language);
    printf ("<a href=\"http:%s?v=%d\">English</a> |\n", 
               PROGRAM_PATH_E, advanced_version); 

    printf ("<a href=\"http://tiger.kulichki.com/avtora.htm\">Авторы</a> |\n");
    printf ("<a href=\"http:/\">Tiger</a> |\n");
    printf ("<a href=\"http://tiger.kulichki.com/an_search.htm\">Поиск анекдотов</a> |\n");
    printf ("<a href=\"http://tiger.kulichki.com/nr.htm\">HP</a> |\n");
    printf ("<a href=\"http://tiger.kulichki.com/kama.eng\">Fragments</a> |\n");
    printf ("<a href=\"http://tiger.kulichki.com/kama.htm\">Кама-Сутра</a> |\n");
    printf ("<a href=\"%s\">Позы</a> |\n", POSES_PATH);
    printf ("<a href=\"http://www.kulichki.com/lubov\">Love</a> |\n");
    printf ("<a href=\"http://www.anikina.com\">Болото</a> |\n");
    printf ("<a href=\"http://www.kulichki.com/news\">News</a>\n");
  }
  printf ("</font>\n");
  printf ("<hr>\n");
}

/**********************************************************************/
void Print_Subscription (void) {
/*
  printf("<form method=post action=%s>\n", FORMMAIL_PATH);  
  printf(" <input type=hidden name=required value=email>\n");
  printf(" <input type=hidden name=recipient value=\"%s\">\n", 
            TIGER_EMAIL);
  printf(" <input type=hidden name=return_link_url\n");
  printf("        value=\"%s\">\n", Get_Program_Path());
  printf(" <input type=hidden name=redirect\n");
  printf("        value=\"%s\">\n\n", Get_Program_Path());
  printf ("E-Рассылка \"Tigers\"\n");
  printf(" <input type=text NAME=email SIZE=25 value=\"email@domain\">\n");
  printf(" <input TYPE=submit VALUE=\"Send\">\n");
  printf("\n");
  printf(" <input type=hidden name=subject value=\"Subscribe Tigers\">\n");
  printf("</form>\n");
*/
  
  if (Flags_Get_Language()) return;
 
  printf ("<br><font size=+1><b>E-Рассылки:</b></font>\n");
  printf("<a href=mailto:%s>", SUBSCRIPTION_EMAIL);
  printf ("<b>Tigers</b></a> | \n");
  
  printf("<a href=%s>", QUICK_HTM);
  printf ("<b>funny.anekdot.unlimited</b></a><br>\n");
}


/**********************************************************************/
void Print_Invitation (long rand_number) {
#ifndef TEST_VERSION
  advrt_idx = (int) (rand_number % MAX_ADV);
  printf ("<form action=/news target=_blank>\n");
  printf ("<input type=submit value=\"%s\">\n", advrt[advrt_idx]);
  printf ("</form>\n");
#endif
}

/**********************************************************************/
void Print_Midi_Console (void) {
#ifndef TEST_VERSION
  if (!(Flags_Get_Random_Number() % MUSIC_FREQUENCY)) {
    printf ("<embed src=ali.mid height=15 width=50\n");
    printf ("autostart=true controls=smallconsole><br>\n");
  }
#endif
}


/**********************************************************************/
void Print_FButtons (long index) {
    printf(" <font size=2>\n");
    if (Flags_Get_Language()) {
      printf(" <a href=%ssendanek.cgi?n=%lu&l=1&a=1>Send link</a>&nbsp;\n", 
             PATH_TO_SEND, index);
      printf("<a href=%ssendanek.cgi?n=%lu&l=0&a=1>Send Joke</a>&nbsp;\n", 
             PATH_TO_SEND, index);
      printf(
       "<a href=%ssendanek.cgi?n=%lu&e=1&a=1>Error report</a>&nbsp;<br>\n", 
  	     PATH_TO_SEND, index);
    } else {
     printf(" <a href=%ssendanek.cgi?n=%lu&l=1&a=0>Послать ссылку</a>&nbsp;\n", 
            PATH_TO_SEND, index);
     printf("<a href=%ssendanek.cgi?n=%lu&l=0&a=0>Послать анекдот</a>&nbsp;\n", 
            PATH_TO_SEND, index);
    printf("<a href=%ssendanek.cgi?n=%lu&e=1&a=0>Error report</a>&nbsp;<br>\n", 
            PATH_TO_SEND, index);
    }
    printf(" </font>\n");
}

/**********************************************************************/
/*
void Print_Voting (long index) {
    printf("<font size=2>\n");
    printf("<form method=post action=%s>\n", VOTING_PATH);
    printf("  <input type=hidden index=%ld>\n", index);
    printf("  <input type=radio name=vote value=\"-2\">-2");
    printf("  <input type=radio name=vote value=\"-1\">-1");
    printf("  <input type=radio name=vote value=\"0\" checked>0");
    printf("  <input type=radio name=vote value=\"1\">1");
    printf("  <input type=radio name=vote value=\"2\">2");
    printf("  <input type=submit value=vote>\n");
    printf("</form>\n");
    printf("</font>\n");
}
*/

/**********************************************************************/
void Print_Warning (void) {
    printf ("<br><b><i>\n");
    printf ("Спасибо за ответы!<br>\n");
    printf ("Рекомендую линк:\n");
    printf (
       "<a href=http://www.cs.bgu.ac.il/~victor/mentos.mpg>Ментос</a><br>\n");
    printf ("</i></b>\n\n");
}

/**********************************************************************/
void Print_AnrBlocks (void) {
  short         blocks_cnt;            /* just a counter              */
  unsigned long offset_in_idx_file;    /* no comments                 */
  long offs;
  long random_index;                   /* random-chosen block index   */
  short repeats_number;
  int   max_index=Flags_Get_Blocks_Number ();
  int   start_number = Flags_Get_Random_Choosing() ? 
                          0 : Flags_Get_Start_Number();
  repeats_number = Flags_Get_Repeats_Number ();

  for (blocks_cnt=0; 
       blocks_cnt<repeats_number && start_number+blocks_cnt<max_index;
       blocks_cnt++) {
    random_index = Matrix_Numbers_Get(blocks_cnt);
    offset_in_idx_file = (random_index) << 2;

    Files_Get_Offset_From_Index (offset_in_idx_file, &offs, sizeof(offs));
    Block_Read  (offs);
    Block_Print (random_index);
    Print_FButtons (random_index);
    //Print_Voting (random_index);
    printf ("<hr>\n");
  }
}

/***************************************************************************/
void Print_One_Block (unsigned long num) {
    unsigned long offs;
    int kwd_num;
    int ofs;
    LINE str;
    int highlight = ((Flags_Get_Highlight) () ||
                     (Flags_Get_Keyword_Type()==USER_DEFINED_KEYWORD));
    Files_Get_Offset_From_Index (num*sizeof(long), &offs, sizeof(offs));
    Files_Seek_Text (offs);
    do {
       Files_Get_Next_Line (str);
       if (highlight) {
         kwd_num = Keywords_Search (str, &ofs);
         if (kwd_num==-1)
           printf ("%s<br>\n", str);
         else
           Print_Highlight (str, ofs, Keywords_Get(kwd_num));
       }
       else
       printf ("%s<br>\n", str);
    } while (str[0]!='\n');
    printf ("<br>\n");
}



/***************************************************************************/
void Print_AnsBlocks (void) {
    int i;
    int nNumbersMatrixLen = Matrix_Numbers_Size ();
    for (i=0; i<nNumbersMatrixLen; i++)
       Print_One_Block (Matrix_Numbers_Get(i));
}

/***************************************************************************/
void Print_Highlight (char* str, int ofs, char* kwd) {
    LINE result;
    strncpy (result, str, ofs);
    result[ofs]='\0';
    strcat  (result, "<b>");
    strncat (result, str+ofs, strlen(kwd));
    strcat  (result, "</b>");
    strcat  (result, str+ofs+strlen(kwd));
    printf  ("%s<br>\n", result);
}

/***************************************************************************/
void Print_Last_Links (void) {
    if (Flags_Get_Language())
      return; /* do not print them in English version */
    printf ("<hr>Актуальные ссылки<br><br>\n");
    printf ("<a href=%s>Гостевая книга</a><br>", GUESTBOOK_HTM);
    printf ("<a href=%s>Благодарности</a><br>",          THANKS_HTM);
    printf ("<a href=%s>Статья</a> о поиске анекдотов<br>", ARTICLE_HTM);
    printf ("<a href=%s>База данных</a> этой программы<br>",
            FILEINFO_HTM);
    printf ("<a href=%s>Информация</a> о данной поисковой системе<br>",
            SEARCHINFO_HTM);
    printf ("<a href=%s>VBSplit</a> - Программа поиска дублей<br>",  
            VBSPLIT_HTM);
}

