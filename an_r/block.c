/**********************************************************************/
/*                              Block.c                               */
/**********************************************************************/

#include <string.h>
#include "an_r.h"
#include "an_s.h"
#include "an_prot.h"

/**********************************************************************/
static LINE  block [MAX_BLOCK_LEN];
static unsigned short nBlockLength = 0;

/***************************************************************************/
/*                     is the keyword found in the block                   */
/***************************************************************************/
int Block_Keyword_Found (char *kwrd, short ignore_case) {
  LINE temp_str;
  int i;
  for (i=0; i<nBlockLength; i++) {
    if (ignore_case==IGNORE)
        Tolower_String (block[i], temp_str);
    else
        strcpy (temp_str, block[i]);

    if (strstr(temp_str, kwrd) != NULL)
        return 1;
  }
  return 0;
}

/***************************************************************************/
void Block_Add_String (char *str) {
    LINE msg;
    if (nBlockLength==MAX_BLOCK_LEN-1) {
       sprintf (msg, "Block_Add_String: too long block");
       Error (msg, 1);
    }
    strcpy (block [nBlockLength++], str);
}

/***************************************************************************/
void Block_Reset(void) {
    nBlockLength=0;
}

/***************************************************************************/
void Block_Print (long index) {
    int i;
    printf("<pre>\n");
    printf ("%d. ", index);
    for (i=0; i<nBlockLength; i++) {
      if (strchr(block[i],'\n')==NULL)
		 strcat(block[i], "\n");
      printf ("%s", block[i]);
    }
    printf("</pre>\n");
}

/***************************************************************************/
void Block_Read (long offs) {
    LINE str;
    Files_Seek_Text (offs);
    Block_Reset();
    while (Files_Get_Next_Line(str)!=NULL) {
      Block_Add_String (str);
      if (!str[0] || str[0]=='\n' || str[0]=='\r') break;
    }
}

