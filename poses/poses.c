/***********************************************************************/
/* Poses.c - the program which reads from file random blocks           */
/*                                                                     */
/* Copyright (C) Victor Bolotnikov, Tigers Ltd, 1997.                  */
/*                                                                     */
/* Last edition: 18.08.00                                              */
/*                                                                     */
/* Known bugs: None                                                    */
/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/***********************************************************************/
#define  MAX_LEN_LINE          200
#define  LOG_FILE_NAME         "../poses/poses.log"
#define  TEXT_FILE_NAME        "../poses/poses.txt"
#define  INDEX_FILE_NAME       "../poses/poses.idx"

#define  NUM_RECORDS_TO_REWIND 100
#define  RECORD_SIZE           15
#define  NUM_BYTES_TO_REWIND   NUM_RECORDS_TO_REWIND*RECORD_SIZE

typedef  unsigned char uchar;
typedef  char LINE    [MAX_LEN_LINE];

#define KULICHKI_URL "http://www.kulichki.com"

#define TOP_BANNER_FILE    "/home/public_html/rban/include/_tiger_include_top"
#define BOTTOM_BANNER_FILE "/home/public_html/rban/include/_tiger_include"

/**********************************************************************/
static int Insert_File (char* fname) {
    FILE *f;
    char str[1000];
    f = fopen (fname, "r");
    if (f == NULL)
        return -1;
    while (fgets (str, 1000, f) != NULL) {
        printf ("%s\n", str);
    }
    fclose (f);
    return 0;
}



/***********************************************************************/
#define MAX_REL 10
unsigned int rel_idx;
LINE rel[MAX_REL] = {
 "Еще!", "More", "Еще парочку", "Хочу еще поз", "Добавить",
 "Повторить", "Маловато будет", "Исчо", "Не понял", "Не въехал"
};



FILE *src=NULL, *idx=NULL;
FILE *stat=NULL;
LINE str;
long offs;
LINE remote_addr;
int  rand_num;

unsigned short blocks_number;         /* how many blocks contrains the file*/
unsigned short blocks_cnt;            /* just a counter                    */
unsigned short repeats_number = 2;    /* how many blocks to get            */
unsigned short random_index   = 0;    /* random-chosen block index         */
unsigned long  offset_in_idx_file;    /* no comments                       */

unsigned int need_warning = 0;

/***********************************************************************/
static long filesize (FILE *stream) {
   long curpos, length;
   curpos = ftell(stream);
   fseek(stream, 0L, SEEK_END);
   length = ftell(stream);
   fseek(stream, curpos, SEEK_SET);
   return length;
}

/***********************************************************************/
static void print_links (void) {
  printf ("<font size=2>\n");
  printf ("<a href=\"%s/~tiger/avtora.htm\">Авторы</a> |\n", KULICHKI_URL);
  printf ("<a href=\"%s/~tiger/\">Main</a> |\n", KULICHKI_URL);
  printf ("<a href=\"%s/~tiger/an_search.htm\">Поиск</a> |\n", KULICHKI_URL);
  printf ("<a href=\"http://tiger.kulichki.net/an_r.htm\">Анекдоты</a> |\n");
  printf ("<a href=\"%s/~tiger/nr.htm\">HP</a> |\n", KULICHKI_URL);
  printf ("<a href=\"%s/~tiger/kama.eng\">Fragments</a> |\n", KULICHKI_URL);
  printf ("<a href=\"%s/~tiger/kama.htm\">Кама-Сутра</a> |\n", KULICHKI_URL);
  printf ("<a href=\"%s/lubov\">Любовь</a> |\n", KULICHKI_URL);
  printf ("<a href=\"%s/boloto\">Болото</a>\n", KULICHKI_URL);
  printf ("</font>\n");
  printf ("<br>\n");
}

/***********************************************************************/
static void print_style (void) {
  printf ("\n");
  printf ("<style>\n");
  printf ("    a:hover  {\n");
  printf ("        text-decoration : underline;\n");
  printf ("        color : #009900;\n");
  printf ("    }\n");
  printf ("\n");
  printf ("          font.red  {\n");
  printf ("        font-size : 8pt;\n");
  printf ("        color : #ff0000;\n");
  printf ("                font-weight : bold;\n");
  printf ("      }\n");
  printf ("\n");
  printf ("      font  {\n");
  printf ("        font-size : 9pt;\n");
  printf ("        color : #888888;\n");
  printf ("        font-weight : bold;\n");
  printf ("      }\n");
  printf ("\n");
  printf ("    </style>\n");
}

/***********************************************************************/
static void print_kulline (void) {
  printf ("<table width=\"90%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" align=\"center\"  bgcolor=\"#ffffff\">\n");
  printf ("<tr>\n");
  printf ("    <td align=\"center\">\n");
  printf ("\n");
  printf ("<table align=\"center\" width=\"99%\" cellspacing=\"2\" cellpadding=\"2\" border=\"0\">\n");
  printf ("<tr>\n");
  printf ("    <td  align=\"center\"><font size=\"1\"><font class=\"red\"><nobr>ВСЕ&nbsp;&nbsp;КУЛИЧКИ</nobr></b></font></font></td>\n");
  printf ("</tr>\n");
  printf ("</table>\n");
  printf ("\n");
  printf ("<!--Вызов линейки \"Все Кулички\"-->\n");
  printf ("<table BORDER=0  CELLSPACING=5 CELLPADDING=0>\n");
  printf ("<tr>\n");
  printf ("\n");
  printf ("<td width=100 align=left valign=top>\n");
  printf ("<a href=\"/jed\"><FONT SIZE=2 Color=\"#0000ff\">Анекдоты</a></Font><br>\n");
  printf ("<!-- <a href=\"/marazm\"><FONT SIZE=2 Color=\"#0000ff\">Маразмы</a></Font><br> -->\n");
  printf ("<a href=\"/stolitsa/jumor.html\"><FONT SIZE=2 Color=\"#0000ff\">Юмор</Font><br>\n");
  printf ("<a href=\"/stolitsa/divan.html\"><FONT SIZE=2 Color=\"#0000ff\">Диван</a></Font><br>\n");
  printf ("<a href=\"http://sport.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Спорт</a></Font><br>\n");
  printf ("<a href=\"http://football.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Футбол</a></Font><br>\n");
  printf ("<a href=\"http://tennis.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Теннис</a></Font><br>\n");
  printf ("<a href=\"http://formula-1.kulichki.net\"><FONT SIZE=2\n");
  printf ("Color=\"#0000ff\">Формула-1</a></Font><br>\n");
  printf ("<!-- <a href=\"http://hockey.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Хоккей</a></Font><br> -->\n");
  printf ("<a href=\"http://auto.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Авто</a></Font><br>\n");
  printf ("</td>\n");
  printf ("\n");
  printf ("<td width=105 align=left valign=top>\n");
  printf ("<a href=\"http://music.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Музыка</a></Font><br>\n");
  printf ("<a href=\"http://www.kulichki.com/pmusic/r_home.htm\"><FONT SIZE=2 Color=\"#0000ff\">MP3-концерт</a></Font><br>\n");
  printf ("<a href=\"http://referat.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Рефераты</a></Font><br>\n");
  printf ("<a href=\"http://love.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Знакомства</a></Font><br> \n");
  printf ("<a href=\"/postcards\"><FONT SIZE=2 Color=\"#0000ff\">Открытки</a></Font><br>                 \n");
  printf ("<a href=\"http://tv.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Программы TV</a></Font><br> \n");
  printf ("<!-- <a href=\"/goroskop\"><FONT SIZE=2 Color=\"#0000ff\">Гороскопы</a></Font><br> -->        \n");
  printf ("<a href=\"http://games.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Игротека</a></Font><br>  \n");
  printf ("<a href=\"http://pristavka.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Видеоигры</a></Font><br>\n");
  printf ("\n");
  printf ("</td>\n");
  printf ("\n");
  printf ("<td width=105 align=left valign=top>\n");
  printf ("<a href=\"/stolitsa/zazer.html\"><FONT SIZE=2 Color=\"#0000ff\">Зазеркалье</a></Font><br>\n");
  printf ("<a href=\"http://polit.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Политцентр</a></Font><br>\n");
  printf ("<a href=\"/stolitsa/infotc.html\"><FONT SIZE=2 Color=\"#0000ff\">Инфоцентр</a></Font><br>\n");
  printf ("<a href=\"http://health.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Медцентр</a></Font><br>\n");
  printf ("<a href=\"http://cooking.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Кулинария</a></Font><br>\n");
  printf ("<a href=\"http://freesoft.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Freesoft</a></Font><br>\n");
  printf ("<a href=\"/stolitsa/komptc.html\"><FONT SIZE=2 Color=\"#0000ff\">Компьютеры</a></Font><br>\n");
  printf ("<a href=\"/stolitsa/baraholka\"><FONT SIZE=2 Color=\"#0000ff\">Барахолки</a></Font><br>\n");
  printf ("\n");
  printf ("</td>\n");
  printf ("\n");
  printf ("<td width=116 align=left valign=top>\n");
  printf ("<a href=\"/stolitsa/pochtamt/listy.html\"><FONT SIZE=2 Color=\"#0000ff\">Рассылки</a></Font><br>\n");
  printf ("<a href=\"http://sterva.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Стервы</a></Font><br>\n");
  printf ("<a href=\"http://opencity.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Досуг</a></Font><br>\n");
  printf ("<!-- <a href=\"mailto:admin@kulichki.com\"><FONT SIZE=2 Color=\"#0000ff\">E-mail</a></Font><br> -->\n");
  printf ("<a href=\"http://job.kulichki.net\"><FONT SIZE=2 Color=\"#0000ff\">Работа</a></Font><br>\n");
  printf ("<a href=\"/stolitsa/biznes/job.html\"><FONT SIZE=2 Color=\"#0000ff\">Вакансии</a></Font><br>\n");
  printf ("<a href=\"/stolitsa/spisok.html\"><FONT SIZE=2 Color=\"#0000ff\">Жители</a></Font><br>      \n");
  printf ("<a href=\"/stolitsa/biznes\"><FONT SIZE=2 Color=\"#0000ff\">Реклама</a></Font><br>          \n");
  printf ("\n");
  printf ("</td>\n");
  printf ("\n");
  printf ("</tr>\n");
  printf ("\n");
  printf ("</table>\n");
  printf ("\n");
  printf ("<!--Конец вызова-->\n");
  printf ("        </td>\n");
  printf ("\n");
  printf ("</table>\n");
}

/***********************************************************************/
static void print_counters (void) {

  printf("<p><a href=http://links.cnt.ru>");
  printf("<img src=http://tiger.kulichki.net/Pictures/vsya_gray.gif\n");
  printf("align=\"\" width=88 height=31 border=0\n");
  printf("alt=\"Вся русская эротика\"></a>\n");

  printf("<!--NUMBER ONE COUNTER--><a target=_top\n");
  printf("href=http://www.one.ru>\n");
  printf("<img src=\"http://www.one.ru/cgi-bin/cnt.cgi?id=16117&t=1\"\n");
  printf("width=88 height=31 alt=\"be number one\" border=0></a>\n");
  printf("<!--NUMBER ONE COUNTER-->\n");

  printf("<a href=\"http://lstat.susanin.com/cgi-bin/lstat/stat.cgi?uid=boloto\" target=\"_top\">\n");
  printf("<img src=\"http://lstat.susanin.com/cgi-bin/lstat/lstat.cgi?boloto&7999999\"\n");
  printf("аheight=31 width=88 border=0 alt=\"Counted by L-STAT\"></a>\n");
  printf("<script language=\"javascript\"><!--\n");
  printf("n=navigator;d=document;dname=\"boloto\";function\n");
  printf("lstat(){d.write(\"<img border=0  src=\"http://lstat.susanin.com\",\n");
  printf("\"/cgi-bin/lstat/lstatj.cgi?srw=\"+srw+\"&srb=\"+srb+\"&fim=1&\",\n");
  printf("\"refer=\"+escape(d.referrer)+\"&srh=\"+srh+\"&dname=\"+dname+\"\" height=1 \",\n");
  printf("\"width=1>\");}srb=\"na\";srw=\"na\";srh=\"na\"//-->\n");
  printf("</script><script language=\"javascript1.2\"><!--\n");
  printf("s=screen;srw=s.width;srh=s.height;escape(n.appName)!=\"Netscape\"?\n");
  printf("srb=s.colorDepth:srb=s.pixelDepth;//-->\n");
  printf("</script>\n");
  printf("<!-- End of Part 1 -->\n");
  printf("<!-- LSTAT counter Part 2 -->\n");
  printf("<script language=\"javascript\"><!--\n");
  printf("lstat();//-->\n");
  printf("</script>\n");
  printf("<!-- End of Part 2 -->\n");

  printf("<!-- Vio.Net.ru CODE -->\n");
  printf("<script language=javascript>\n");
  printf("var color=0; // Your BackGround Color: 0 - WHITE; 1 - BLACK\n");
  printf("var id=1335;\n");
  printf("var x=Math.round(Math.random()*2000000);\n");
  printf("document.write(\"<a href=http://www.vio.net.ru/cgi-bin/\");\n");
  printf("document.write(\"in.cgi?id=\"+id+\"&x=\"+x+\" target=_top>\");\n");
  printf("document.write(\"<img src=http://www.vio.net.ru/cgi-bin/\");\n");
  printf("document.write(\"view.cgi?type=\"+color+\"&id=\"+id+\"&x=\"+x+\" width=88 height=63\");\n");
  printf("document.write(\" alt='Vio.Net.ru Каталог эротики' border=0></A>\"); </script>\n");
  printf("<!-- Vio.Net.ru CODE -->\n");


}

/***********************************************************************/
static unsigned int Get_Rel_Idx (int random_index) {
  int i = random_index % 100;
  if (i<40) return 0;
  if (i<60) return 1;
  if (i<70) return 2;
  if (i<77) return 3;
  if (i<84) return 4;
  if (i<89) return 5;
  if (i<92) return 6;
  if (i<95) return 7;
  if (i<98) return 8;
  return 9;
}

/***********************************************************************/
static void print_kul_banner (void) {
int rc;
  printf("<center>\n");

    rc = Insert_File (TOP_BANNER_FILE);
    if (rc)
       printf ("Cannot open top banner file\n");

    printf ("</center>\n");

/*
  printf("<a href=\"http://banners.rambler.ru:8080/ban.clk?pg=761\">\n");
  printf("<img src=\"http://banners.rambler.ru:8080/ban.ban?pg=761\" alt=\"Banners\n");
  printf("Network\" width=468 height=60 border=0></a><br>\n");
  printf("<FONT SIZE=-1><A HREF=\"/stolitsa/business/\">Реклама в Интернет</A></FONT>\n");
*/


    printf ("<BR><Center><FONT SIZE=-1><A\n");
    printf ("HREF=http://www.kulichki.com/advert>Реклама в\n");
    printf ("Интернет</A></FONT></Center>\n");


}


/***********************************************************************/
static void print_reload (int random_index) {
  printf ("<center>\n");
  printf ("<font size=+4>\n");

  printf ("<form action=http://www.kulichki.com/cgi-bin/cgiwrap/tiger/poses.cgi method=get>\n");
  printf ("<input type=submit value=\"%s\"><br>\n",
          rel[Get_Rel_Idx(random_index)]);
  printf ("<input type=hidden name=num value=%d>\n", random_index % 117);
  printf ("</form>\n");

  printf ("</font>\n");
  printf ("</center>\n");
  printf ("\n");
}

/***********************************************************************/
static void print_header (void) {
  printf ("Content-Type: text/html\n\n");
  printf ("<html>\n");
  printf ("<head>\n");
  printf ("<META  name=description content=\"Позы\">\n");
  printf ("<meta name=author content=\"Tigers Ltd, Inc\">\n");
  printf ("<meta name=keywords content=\"Кама-сутра Камасутра позы poses sex sexuality kama-sutra\">\n");
  printf ("<META HTTP-EQUIV=Refresh CONTENT=60>\n");
  printf ("<title>Sexual poses</title>\n");
  printf ("</head>\n");
  printf ( "<body bgcolor=\"#f2f3f3\">\n");
  printf ("<basefont size=3>\n");

  print_kul_banner ();

  printf ("<center><h2>Случайные позы</h2></center>\n");

  print_links ();
  printf ("<br><br>\n");
  printf ("<font size=-1>\n");
  /*printf ("Идея: <a href=\"mailto:valera@kulichki.com\">Валера Колпаков</a><br>\n");*/
  printf ("Реализация: <a href=\"mailto:tiger@kulichki.com\">Виктор Болотников</a><br>\n");
  printf ("Для новой позы - дави на \"Reload\"<br>\n");
  printf ("<hr>\n");
  printf ("Предназначение данной страницы - стеб.\n");
  printf ("Как завоевывать сердца девушек -\n");
  printf ("учить бессмысленно.\n");
  printf ("Техническую информацию по сексологии можете\n");
  printf ("почерпнуть из руководств на странице <a href=\"http:/lubov\">Ани</a>,\n");
  printf ("хотя и нет от них большой пользы (женатые меня поймут). Ничего нового здесь вас\n");
  printf ("не ждет, однако идея показалась забавной. Захаживайте вечерком,\n");
  printf ("выбирайте позу на сегодня.<br>\n");
  printf ("Имя читателя, угадавшего количество поз в используемой базе данных,\n");
  printf ("будет записано на этой странице золотыми буквами.\n");
  printf ("<br>\n");
  printf ("Если будет настроение, база данных увеличится примерно втрое: еще столько\n");
  printf ("же новых способов бродят у меня в голове, и кое-что найдется в Кама-Сутре.<br>\n");
  printf ("<center><img src=http://tiger.kulichki.net/colorbar.gif alt=\"\"></center><br>\n");
  printf ("</font>\n");
}

/**********************************************************************/
static void print_tail (void) {
  printf ("</BODY>\n");
  printf ("</HTML>\n");
}

/**********************************************************************/
static void error (char *msg) {
  printf ("%s\n\n", msg);
  print_tail ();
  if (src!=NULL) fclose (src);
  if (idx!=NULL) fclose (idx);
  exit (0);
}

/**********************************************************************/
static void open_files (void) {
  src = fopen (TEXT_FILE_NAME, "r");
  if (src==NULL) {
     printf ("Cannot open file poses.txt\n");
     error ("");
  }

  idx = fopen (INDEX_FILE_NAME, "rb");
  if (idx==NULL) {
     printf ("Cannot open file poses.idx\n");
     error ("");
  }
}

/**********************************************************************/
void get_statistics (void) {
  unsigned long  file_length;
  unsigned short hits_counter = 0;
  time_t current_time, hit_time;
  LINE env_line;
  stat = fopen (LOG_FILE_NAME, "r");
  if (stat==NULL) {
    printf ("LOGFILE not found\n");
    return;
  }
  //file_length = filesize (stat);
  fgets (env_line, MAX_LEN_LINE, stat);
  current_time = time(NULL);
  while (fgets (env_line, MAX_LEN_LINE, stat) != NULL) {
    if (strstr (env_line, remote_addr) != NULL) {
      sscanf (env_line, "%lu", &hit_time);
      if (current_time - hit_time <300)
    hits_counter++;
    }
  }
  if (hits_counter>2)
    need_warning = 1;
  fclose (stat);
}

/**********************************************************************/
void save_statistics (void) {
  stat = fopen (LOG_FILE_NAME, "a");
  if (stat==NULL) {
    printf ("LOGFILE could not be opened\n");
    return;
  }
  fprintf (stat, "%lu:%s\n", time(NULL), remote_addr);
  fclose  (stat);
}

/**********************************************************************/
void main (void) {

  print_header ();
  open_files ();
  blocks_number = (short)(filesize (idx) >> 2) - 1; /* last number */
                                  /* doesn't take part in the game */
  srand (time(NULL));
  strcpy (remote_addr, getenv ("REMOTE_ADDR"));
  //get_statistics  ();
  //save_statistics ();

  rand_num = rand ();

/***********************************************************************/
  if (need_warning) {
    //printf ("<br><h2><b><i>\n");
    //printf ("Monster! How many poses do you need?<br>\n");
    //printf ("</i></b></h2>\n\n");
  }
  for (blocks_cnt=0; blocks_cnt<repeats_number; blocks_cnt++) {
    random_index = rand () % blocks_number;
    offset_in_idx_file = ((long)random_index) << 2;
    fseek (idx, offset_in_idx_file, SEEK_SET);
    fread ((void *)&offs, sizeof(offs), 1, idx);
    fseek (src, offs, SEEK_SET);
    printf ("<BR>\n");
    while (fgets (str, MAX_LEN_LINE, src)!=NULL) {
      printf ("%s\n", str);
      if (!str[0] || str[0]=='\n' || str[0]=='\r') break;
    }
    printf ("<br><br><hr>\n");
  }

  fclose (src);
  fclose (idx);

  print_reload (random_index);
  printf ("</center>\n");
  print_counters ();

  print_style ();
  print_kulline();
  print_tail ();
}
