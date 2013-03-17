
/**********************************************************************/
/*                             Params.c                               */
/**********************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "an_r.h"
#include "an_s.h"
#include "an_prot.h"
#include "flags.h"

/**********************************************************************/
static PARAM_LINE args_str;
char *Get_Args_Str(void) {return args_str;}

/**********************************************************************/



/***********************************************************************/
/*                             Params_Get                              */
/*                                                                     */
/* List of possible parameters to be appeared in the main program call:*/
/*                                                                     */
/* bool a    1 if answer on trivia is "yes"                            */
/* bool b    1 if inverse coloring is required                         */
/* char*c    "and","AND","or", "OR" according to required searching    */
/* bool e    1 if the language is "English"                            */
/* void h    requires display help information                         */
/* bool i    1 if ignore letters case                                  */
/* int  k    keyword type (predefined, user-defined. random            */
/* bool l    1 if highlighting is required                             */
/* int  n    a number of blocks to be printed                          */
/* char*p    keywords string                                           */
/* bool r    1 if random selection is used                             */
/* int  s    start block number                                        */
/* int  t    theme number if used (n/m if not)                         */
/* bool v    1 if advanced (full) version is used                      */
/* bool w    1 if MustDie bonus is required                            */
/* bool y    1 if oneline bonus is required                            */
/* int  z    heh, 10 dollars for information about it...               */
/*                                                                     */
/***********************************************************************/
void Params_Get  (void) {
  PARAM_LINE ascii_args_str;
  LINE and_or_value;
  LINE msg;
  char *plen;
  char *passed_parameter;
  unsigned short args_str_length=0;
  int  i;
  int  rc;
  int  n_temp;
  long l_temp;
#ifndef TEST_VERSION
  args_str[0]='\0';
  ascii_args_str[0]='\0';
  plen = getenv ("CONTENT_LENGTH");

  if (plen != NULL) {
    if (sscanf (plen, "%u", &args_str_length) != 1)
      Error ("CONTENT_LENGTH environment variable is not defined<br>", 1);
    else
      fgets (args_str, args_str_length+1, stdin);
  }
  else {
    plen = getenv("QUERY_STRING");
    if (plen!=NULL)
        strcpy (args_str, plen);
    else
        args_str[0]='\0';
  }
  Hex2Ascii (args_str, ascii_args_str);

  //printf ("parameters: '%s'=='%s'<br>\n", args_str, ascii_args_str);
  //return;
  passed_parameter = strtok (ascii_args_str, "&");
  if (passed_parameter==NULL) return;
  do {
    if (Found_Substring (passed_parameter, "a=")) {
        if (!strncmp(passed_parameter+2, ANSWER_YES, strlen(ANSWER_YES)))
           Flags_Set_Answer (1);
        else
        if (!strncmp(passed_parameter+2, ANSWER_NO, strlen(ANSWER_NO)))
           Flags_Set_Answer (2);
        else {
           Error ("Invalid Answer parameter", 0);
           Flags_Set_Answer (0);
        }
    }
    else
    if (Found_Substring (passed_parameter, "b=")) {
        if (sscanf (passed_parameter+2, "%d", &n_temp) != 1)
           Error ("Invalid inverse parameter", 0);
        if (n_temp) n_temp=1;
        Colors_Set_Black (n_temp);
    }
    else

    if (Found_Substring (passed_parameter, "c=")) {
        strcpy (and_or_value, passed_parameter+2);
        if (! strcmp (and_or_value, "AND") ||
            ! strcmp (and_or_value, "and"))
        Flags_Set_And_Or_Flag (1);
        else
        if (! strcmp (and_or_value, "OR") ||
            ! strcmp (and_or_value, "or"))
        Flags_Set_And_Or_Flag (0);
        else  {
           sprintf (msg, "Unexpected value %s", passed_parameter);
           Error (msg, 0);
        }
    }
    else
    if (Found_Substring (passed_parameter, "e=")) {
        if (sscanf (passed_parameter+2, "%d", &n_temp) != 1)
           Error ("Invalid language parameter", 0);
        if (n_temp) n_temp=1;
        Flags_Set_Language (n_temp);
    }
    else
    if (Found_Substring (passed_parameter, "h")) {
       Error (USAGE, 0);
    }
    else
    if (Found_Substring (passed_parameter, "i=")) {
         switch (passed_parameter[2]) {
           case 0: Flags_Set_Ignore_Case(CASE_SENSITIVE); break;
           case 1: Flags_Set_Ignore_Case(IGNORE); break;
           default: printf("Unexpected Ignore parameter value");
         }
    }
    else
    if (Found_Substring (passed_parameter, "k=")) {
       if (sscanf (passed_parameter+2, "%d", &n_temp) != 1)
	  Error ("Invalid keyword_type parameter", 0);
       Flags_Set_Keyword_Type (n_temp);
    }
    else
    if (Found_Substring (passed_parameter, "l=")) {
       if (sscanf (passed_parameter+2, "%d", &n_temp) != 1)
	  Error ("Invalid highlight parameter", 0);
       Flags_Set_Highlight (n_temp);
    }
    else
    if (Found_Substring (passed_parameter, "n=")) {
	if (sscanf (passed_parameter+2, "%d", &n_temp) != 1)
	  Error ("Invalid repeats_number parameter", 0);
	if (n_temp<1u || n_temp>10u) {
	      Error("User, не выпендривайся<br>", 0);
	     Flags_Set_Repeats_Number(3u);
	}
	else
	    Flags_Set_Repeats_Number(n_temp);
    }
    else
    if (Found_Substring (passed_parameter, "p=")) {
       Keywords_Extract (passed_parameter+2, MAX_PARAM_LINE_LEN-2);
    }
    else
    if (Found_Substring (passed_parameter, "r=")) {
       if (sscanf (passed_parameter+2, "%d", &n_temp) != 1)
          Error ("Invalid random_choosing parameter", 0);
       else
          Flags_Set_Random_Choosing (n_temp);
    }
    else
    if (Found_Substring (passed_parameter, "s=")) {
        if (sscanf (passed_parameter+2, "%ld", &l_temp) != 1)
           Error ("Invalid start_number parameter", 0);
        else Flags_Set_Start_Number (l_temp);
    }
    else
    if (Found_Substring (passed_parameter, "t=")) {
       rc = sscanf (passed_parameter+2, "%d", &n_temp);
       if (rc!=1) Error("Theme parameter expected", 0);
       else Flags_Set_Theme (n_temp);
    }
    else
    if (Found_Substring (passed_parameter, "v=")) {
        if (sscanf (passed_parameter+2, "%d", &n_temp) != 1)
           Error ("Invalid advanced_version parameter", 0);
        Flags_Set_Advanced_Version (n_temp);
        if (Flags_Get_Advanced_Version())
            Flags_Set_Advanced_Version(1u);
    }
    else
    if (Found_Substring (passed_parameter, "w=")) {
       rc = sscanf (passed_parameter+2, "%d", &n_temp);
       if (rc!=1) Error("MustDie parameter expected", 0);
       else Flags_Set_MustDie (n_temp);
    }
    else
    if (Found_Substring (passed_parameter, "y=")) {
       rc = sscanf (passed_parameter+2, "%d", &n_temp);
       if (rc!=1) Error("Bonus parameter expected", 0);
       else Flags_Set_Bonus (n_temp);
    }
    else
    if (Found_Substring (passed_parameter, "z=")) {
       // heh, try to guess what is it for 
    }
    else
      Error("Invalid parameters passed to An.cgi", 0);

    passed_parameter=strtok (NULL, "&");
  } while (passed_parameter!=NULL);

#else
  Keywords_Add("Вася");
  Keywords_Add("USA");
  Keywords_Add("дАть");
  Flags_Set_Ignore_Case (IGNORE);
  Flags_Set_And_Or_Flag(OR_FLAG);
  //Flags_Set_Keyword_Type(USER_DEFINED_KEYWORD);
  if (Flags_Get_Ignore_Case()==IGNORE)
     for (i=0; i<Keywords_Get_Size(); i++)
        Tolower_String (Keywords_Get(i), Keywords_Get(i));
#endif
  Params_Print ();
}


/***************************************************************************/
void Params_Print (void) {
#ifdef TEST_VERSION
   printf("Set parameters:r=%d, adv=%d, black=%d, st=%d, ans=%d, ",
          Flags_Get_Repeats_Number(), Flags_Get_Advanced_Version(),
          Colors_Get_Black(), Flags_Get_Start_Number(), Flags_Get_Answer());
   printf("kwd_t=%d,t=%d,and=%d, ignore=%d<br><br>\n",
          Flags_Get_Keyword_Type(), Flags_Get_Theme(),
          Flags_Get_And_Or_Flag(), Flags_Get_Ignore_Case());
#endif
}


