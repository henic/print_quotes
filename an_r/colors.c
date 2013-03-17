/***********************************************************************/
/*                            Colors.c                                 */
/***********************************************************************/

#include <string.h>

#include "an_r.h"
#include "an_prot.h"


/**********************************************************************/
/*                            Colors                                  */
/**********************************************************************/
static short  six_colors[6];
static char   stextcolor[20];

static short  black        = 0;
static short  rand_color;
static short  first_color,
              second_color;

short *Colors_Get_Six_Colors (void) {return &six_colors[0];}
char  *Colors_Get_Text_Color (void) {return stextcolor;}

/***********************************************************************/
short Colors_Get_Black  (void) {return black;}
short Colors_Get_Rand   (void) {return rand_color;}
short Colors_Get_First  (void) {return first_color;}
short Colors_Get_Second (void) {return second_color;}

void Colors_Set_Black   (short nblack) {black = nblack;}
/***********************************************************************/
void Colors_Set (long random_number) {

  short r1, r2, r3, r4, r5, r6;
  r1 = (short)(random_number       % MAX_COLOR);
  r2 = (short)((random_number>>8)  % MAX_COLOR);
  r3 = (short)((random_number>>16) % MAX_COLOR);
  r4 = (short)((random_number>>24) % MAX_COLOR);
  r5 = (short)((random_number>>20) % MAX_COLOR);
  r6 = (short)((random_number>>28) % MAX_COLOR);

  rand_color = r1;

  if (!black) {
     first_color  = (short)(0xFF-r1);
     second_color = r1;
     strcpy(stextcolor, "black");
     r1=(short)(0xFF-r1);
     r2=(short)(0xFF-r2);
     r3=(short)(0xFF-r3);
  }
  else {
     second_color = (short)(0xFF-r1);
     first_color  = rand_color;
     strcpy(stextcolor, "white");
     r4=(short)(0xFF-r4);
     r5=(short)(0xFF-r5);
     r6=(short)(0xFF-r6);
  }
  six_colors[0]=r1;
  six_colors[1]=r2;
  six_colors[2]=r3;
  six_colors[3]=r4;
  six_colors[4]=r5;
  six_colors[5]=r6;
}

