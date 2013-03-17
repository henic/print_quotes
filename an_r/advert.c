/***************************************************************************/
/*                              advert.c                                   */
/* /news advertisement                                                     */
/***************************************************************************/

#include <stdio.h>
#include <string.h>
#include "an_r.h"
#include "an_prot.h"

#define KULICHKI_BANNER 0
#define TIGER_BANNER    1

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

/**********************************************************************/
void Adv_Print_Advert (void) {
#ifndef TEST_VERSION
    int rc;

    printf ("<center>\n");
    rc = Insert_File (TOP_BANNER_FILE);
    if (rc)
       printf ("Cannot open top banner file\n");
    printf ("</center>\n");

    printf ("<BR><Center><FONT SIZE=-1><A\n");
    printf ("HREF=http://www.kulichki.com/advert>Реклама в\n");
    printf ("Интернет</A></FONT></Center>\n");


#endif
}

/***********************************************************************/
void Adv_Print_RB2 (long random_number) {
#ifndef TEST_VERSION
    char rb2_login[10];
    short rb2_rnd = (short) random_number;
    if ((random_number % 5) > 1)
        strcpy (rb2_login, "tiger");
    else
        strcpy (rb2_login, "kulichki");

    printf("<a href=http://rb2.design.ru/cgi-bin/href/%s?%.7u target=_top>",
              rb2_login, rb2_rnd);
    printf("<img src=http://rb2.design.ru/cgi-bin/banner/%s?%.7u ",
              rb2_login, rb2_rnd);
    printf("width=100 height=100 border=0 alt=\"RB2 Network.\" ismap></a>");

#endif
}


/***********************************************************************/
void Adv_Print_Rambler_Code (unsigned short code) {
#ifndef TEST_VERSION
  printf ("<!--begin of Top100-->\n");
  printf ("<img src=http://counter.rambler.ru/top100.cnt?%u ", code);
  printf ("width=1 height=1 border=0>\n");
  printf ("<!--end of Top100 code-->\n");
#endif
}

/***********************************************************************/
void Adv_Print_Rambler_Image (void) {
#ifndef TEST_VERSION
  printf ("<!--begin of Top100-->\n");
  printf ("<a href=http://counter.rambler.ru/top100/ target=_blank>\n");
  printf (
//"<img src=images.rambler.ru/top100/banner-88x31-rambler-darkblue2.gif\n");
"<img src=http://tiger.kulichki.net/Pictures/banner-88x31-rambler-darkblue2.gif\n");

  printf ("border=0 width=88 height=31\n");
  printf ("alt=\"Rambler's Top100\"></a>\n");
  printf ("<!--end of Top100 code-->\n");
#endif
}

/***********************************************************************/
void Adv_Print_RLE (long random_number) {

#ifndef TEST_VERSION

    int rc;
   
    rc = Insert_File (BOTTOM_BANNER_FILE);
    if (rc)
       printf ("Cannot open bottom banner file\n");

/*

   short rle_rnd = (short) random_number;

   printf (" <!-- Russian LinkExchange code START -->\n");
   printf ("<iframe\n");
   printf ("src=http://www.linkexchange.ru/cgi-bin/erle.cgi?21292?%d\n", 
              rle_rnd);
   printf ("frameborder=0 vspace=0 hspace=0 width=468 height=60\n");
   printf ("marginwidth=0  marginheight=0 scrolling=no>\n");
   printf ("<a href=http://www.linkexchange.ru/users/021292/goto.map \n");
   printf ("target=_top>\n");
   printf ("<img src=http://www.linkexchange.ru/cgi-bin/rle.cgi?21292?%u\n", 
              rle_rnd);
   printf ("alt=\"RLE Banner Network\" border=0 height=60 width=468></a>\n");
   printf ("</iframe>\n");
   printf ("<!-- Russian LinkExchange code END -->\n");
*/

#endif
}

/***********************************************************************/
void Adv_Print_RLE100 (long random_number, int tiger_banner) {

#ifndef TEST_VERSION

   int rc;

   unsigned short rle_rnd = (unsigned short) random_number;

if (tiger_banner) {
 printf ("<!-- Russian LinkExchange code START - BANNER #1 (100x100)-->\n");
 printf ("  <iframe\n");
 printf ("  src=http://10e2.linkexchange.ru/cgi-bin/erle.cgi?25490-bn=0?%u\n", rle_rnd);
 printf ("  frameborder=0 vspace=0 hspace=0 width=100 height=100\n");
 printf ("  marginwidth=0  marginheight=0 scrolling=no>\n");
 printf ("  <a href=http://10e2.linkexchange.ru/users/025490/goto.map?bn=0 target=_top>\n");
 printf ("  <img src=http://10e2.linkexchange.ru/cgi-bin/rle.cgi?25490-bn=0?%u\n", rle_rnd);
 printf ("  alt=\"RLE Banner Network\" border=0 height=100 width=100></a>\n");
 printf ("  </iframe>\n");
 printf ("<!-- Russian LinkExchange code END -->\n");
}

else {
 printf ("<!-- Russian LinkExchange code START - BANNER #1 (100x100)-->\n");
 printf ("<iframe src=http://10e2.linkexchange.ru/cgi-bin/erle.cgi?23782-bn=0\n");
 printf ("frameborder=0 vspace=0 hspace=0 width=100 height=100 marginwidth=0\n");
 printf ("marginheight=0 scrolling=no>\n");
 printf ("<a href=http://10e2.linkexchange.ru/users/023782/goto.map?bn=0 target=_top>\n");
 printf ("<img src=http://10e2.linkexchange.ru/cgi-bin/rle.cgi?23782-bn=0\n");
 printf ("alt=\"RLE Banner Network\" border=0 height=100 width=100></a>\n");
 printf ("</iframe>\n");
 printf ("<!-- Russian LinkExchange code END -->\n");
}

#endif
}



/***********************************************************************/
void Adv_Print_RLE_RLE100 (long random_number) {

#ifndef TEST_VERSION
   printf("<table border=0 width=668>\n");
   printf(" <tr>\n");
   printf("    <td valign=middle>\n");
   Adv_Print_RLE100(random_number, TIGER_BANNER);
   printf("</td>\n");
   printf("    <td valign=middle>\n");
   Adv_Print_RLE(random_number);
   printf("</td>\n");
   printf("    <td valign=middle>\n");
   Adv_Print_RLE100(random_number, KULICHKI_BANNER);
   printf("</td>\n");
   printf(" </tr>\n");
   printf("</table>\n");
#endif

}

void Adv_Print_Top (void) {
return;
printf ("<!--TopList COUNTER--><a target=_top\n");
printf ("href=\"http://top.list.ru/jump?from=86942\"><img\n");
printf ("src=\"http://195.34.34.80/counter?id=86942;t=1\"\n");
printf ("border=0 height=40 width=88\n");
printf ("alt=\"TopList\"></a><!--TopList COUNTER-->\n");
}
