
/***********************************************************************/
/*                              Serv.c                                 */
/***********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "an_r.h"
#include "an_prot.h"

/**********************************************************************/
//const char delimiters [] = " \007\046~!@#$^^&*()_+=`\\|'\"/?><,.;:";
static const char nondelimiters[] =
"1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-ÊÃÕËÅÎÇÛÝÚÈßÆÙ×ÁÐÒÏÌÄÖÜÑÞÓÍÉÔØÂÀêãõëåîçûýúèÿæù÷áðòïìäöüñþóíéôøâà";

/***************************************************************************/
char* Get_Program_Path (void) {
  return ((Flags_Get_Language () == ENGLISH) ?
                PROGRAM_PATH_E : PROGRAM_PATH_R);
}

/***************************************************************************/
int Serv_Is_Delimiter (char ch) {
   return (strchr(nondelimiters, ch)==NULL);
}



/***********************************************************************/
/* Generation based on PID and remote IP */
long int Get_Random_Number(void) {
    long int result = rand();
    return result;
}

/**********************************************************************/
long Filesize (FILE *stream) {
   LINE msg;
   long curpos, length;
   int rc;

   if (stream==NULL)
     Error ("Filesize: Stream is NULL", 1);

   curpos = ftell(stream);
   rc = fseek (stream, 0L, SEEK_END);
   if (rc) {
      sprintf (msg, "Filesize: fseek (%d, 0L, SEEK_END) failed with code %d",
                    stream, rc);
      Error (msg, 1);
      return -1;
   }
   length = ftell (stream);
   rc = fseek (stream, curpos, SEEK_SET);
   if (rc) {
      sprintf (msg, "Filesize: fseek (%d, %d, SEEK_SET) failed with code %d",
                    stream, curpos, rc);
      Error (msg, 1);
      return -2;
   }

   return length;
}

/**********************************************************************/
int Found_Substring (char *str, char *templ) {
    int i;
    int length_of_template = strlen(templ);
    for (i=0; i<length_of_template; i++)
        if (tolower(str[i])!=templ[i])
            return 0;
    return 1;
}


