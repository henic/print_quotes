/**********************************************************************/
/*                              Keywords.c                            */
/**********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "an_r.h"
#include "an_s.h"
#include "an_prot.h"
#include "flags.h"

static LINE           sKeywords[MAX_NUM_KWDS];
static unsigned short nKeywordsNumber = 0;

/***************************************************************************/
int Keywords_Get_Size (void) {return nKeywordsNumber;}

/***************************************************************************/
void Keywords_Add (char *sKwd) {
   if (nKeywordsNumber>=MAX_NUM_KWDS) {
      Error ("Too many keywords", 1);
   }
   else
      strcpy (sKeywords[nKeywordsNumber++], sKwd);
}

/***************************************************************************/
char* Keywords_Get (int n) {
   LINE msg;
   if (n>=nKeywordsNumber || n<0) {
      sprintf (msg, "Invalid keyword[%d] request", n);
      Error (msg, 1);
   }
   return sKeywords[n];
}

/***************************************************************************/
void Keywords_Proceed_Ignore_Case (short ignore_case) {
   int i;
   if (ignore_case==IGNORE)
     for (i=0; i<nKeywordsNumber; i++) {
        Tolower_String (sKeywords[i], sKeywords[i]);
     }
}

/***************************************************************************/
void Keywords_Print (void) {
  unsigned short i;
  printf ("Got the following keywords:<br>\n");
  for (i=0; i<nKeywordsNumber; i++)
    printf ("<b>%s</b><br>\n", sKeywords[i]);
  printf ("<hr>\n");
}


/***************************************************************************/
void Keywords_Extract (char *list_params, int list_params_len) {
   PARAM_LINE str_params;
   unsigned short param_len_cnt;
   unsigned short param_len_limit;
   unsigned short c;
   char *p_parm;
   char cparm;

   nKeywordsNumber = 0;
   if (strlen(list_params)>=list_params_len)
       list_params[list_params_len]='\0';
   param_len_limit = strlen(list_params);
   strcpy (str_params, list_params);
   p_parm=str_params;
   param_len_cnt = 0;
   while (*p_parm && param_len_cnt<param_len_limit) {
     while (*p_parm && (Serv_Is_Delimiter(*p_parm)) &&
            param_len_cnt<param_len_limit) {
        p_parm++;                      // skip delimiters
        param_len_cnt++;               // count the length
     }
     if ((! *p_parm) || (*p_parm=='\n') || (*p_parm=='\r'))
        return;

     cparm = *p_parm;
     c=0;
     while (cparm && (!Serv_Is_Delimiter(cparm)) &&
            param_len_cnt<param_len_limit) {
        sKeywords[nKeywordsNumber][c++] = cparm;
        p_parm++;
        param_len_cnt++;
        cparm = *p_parm;
     }
     sKeywords[nKeywordsNumber][c] = '\0';
     //Check_Keyword_Is_OK (sKeywords[nKeywordsNumber]);
     if (c>2 && nKeywordsNumber<MAX_NUM_KWDS-1)
        nKeywordsNumber++;
   }
}


/***************************************************************************/
/* the function returns index of the found keyword or -1. In case when     */
/* any keyword is found output parameter ofs contains offset of the        */
/* keyword from the string start.                                          */
/***************************************************************************/
int Keywords_Search (char* str, int *ofs) {
   LINE lower_str;
   LINE keyword;
   int  keyword_len;
   int  o=0;
   int max_len;
   unsigned short i;
   char *p;
   Tolower_String(str, lower_str);

   for (i=0; i<nKeywordsNumber; i++) {
      p = strstr (lower_str, sKeywords[i]);
      if (p !=NULL) {
	   strcpy (keyword, sKeywords[i]);
           keyword_len = strlen(keyword);
           max_len = strlen(lower_str) - keyword_len;
           while (strncmp(lower_str+o, keyword, keyword_len) &&
                  o<max_len)
              o++;
      *ofs = o;
      return i;
    }
   }
   return -1;
}


