/***************************************************************************/
/*                            Send_msg.c                                   */
/***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "an_r.h"
#include "an_prot.h"

#define KULICHKI_URL        "http://www.kulichki.com"
#define RUS_ERROR_MSG       "Мне кажется, имеет место быть ошибка:"
#define ENG_ERROR_MSG       "I think the following joke contains error:"

#define TEXT_FILE_X         "../poses/poses.txt"
#define INDEX_FILE_X        "../poses/poses.idx"

/***************************************************************************/
long int start_number=0;
short error_report=0;
short link_only=0;
short program_error=0;
short language=0;
short mini_version=0;
short x_text=0;

static LINE args_str, ascii_args_str;
static LINE str_error    = "";
static LINE program_name = "";

static FILE *f_src, *f_idx;

/* the following function is unused but required for compatibility 
   with the rest of programs (linker should know it) 
*/
char* Get_Args_Str (void) {return "";}

static void Check_Is_Bool (short n) {
  if (n!=0 && n!=1)
    Error ("Parameter expected to be boolean", 0);
}

/***********************************************************************/
/* get_parameters                                                      */
/*                                                                     */
/* Possible parameters got from callee:                                */
/* int  n       start block number                                     */
/* bool l       1 if link only, 0 otherwise                            */
/* bool e       1 if it's error report, 0 - if information             */
/* bool a       1 if the language is "English"                         */
/* bool p       1 if it's program error (required contact the author)  */
/* bool m       1 if mini-version, 0 if the full one                   */
/* bool x       1 if pos_x file is used                                */
/* char* pn     program name if needed                                 */
/* char* s      error message                                          */
/***********************************************************************/
static void get_parameters (void) {
  char *plen;
  char *passed_parameter;
  unsigned short args_str_length=0;

  args_str[0]='\0';
  ascii_args_str[0]='\0';
  plen = getenv ("CONTENT_LENGTH");

  if (plen != NULL) {
    if (sscanf (plen, "%u", &args_str_length) != 1)
      Error ("CONTENT_LENGTH environment variable is badly defined<br>", 0);
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

  passed_parameter = strtok (ascii_args_str, "&");
  if (passed_parameter==NULL) return;
  do {
    if (passed_parameter[0] == 'n' &&
        passed_parameter[1] == '=') {
        if (sscanf (passed_parameter+2, "%ld", &start_number) != 1)
           Error ("Invalid start_number parameter", 0);
    }
    else
    if (passed_parameter[0] == 'l' &&
        passed_parameter[1] == '=') {
        if (sscanf (passed_parameter+2, "%d", &link_only) != 1)
           Error ("Invalid Link parameter", 0);
        Check_Is_Bool (link_only);
    }
    else
    if (passed_parameter[0] == 'm' &&
        passed_parameter[1] == '=') {
        if (sscanf (passed_parameter+2, "%d", &mini_version) != 1)
           Error ("Invalid Version parameter", 0);
        Check_Is_Bool (mini_version);
    }
    else
    if (passed_parameter[0] == 'e' &&
        passed_parameter[1] == '=') {
        if (sscanf (passed_parameter+2, "%d", &error_report) != 1)
           Error ("Invalid ErrorReport parameter", 0);
        Check_Is_Bool (error_report);
    }
    else
    if (passed_parameter[0] == 'a' &&
        passed_parameter[1] == '=') {
        if (sscanf (passed_parameter+2, "%d", &language) != 1)
           Error ("Invalid language parameter", 0);
        Check_Is_Bool (language);
    }
    else
    if (passed_parameter[0] == 'p' &&
        passed_parameter[1] == '=') {
        if (sscanf (passed_parameter+2, "%d", &program_error) != 1)
           Error ("Invalid ProgramError parameter", 0);
        Check_Is_Bool (program_error);
    }
    else
    if (passed_parameter[0] == 'x' &&
        passed_parameter[1] == '=') {
        if (sscanf (passed_parameter+2, "%d", &x_text) != 1)
           Error ("Invalid X_text parameter", 0);
        Check_Is_Bool (x_text);
    }
    else
    if (passed_parameter[0] == 's' &&
        passed_parameter[1] == '=') {
        strcpy (str_error, passed_parameter+2);
    }
    else
       Error ("Unexpected parameter", 0);
    passed_parameter=strtok (NULL, "&");
  } while (passed_parameter!=NULL);
}

/**********************************************************************/
static void open_files (short x_text, short language) {
  LINE msg_err;
  LINE text_file, index_file;

  if (x_text) {
       strcpy (text_file,  TEXT_FILE_X);
       strcpy (index_file, INDEX_FILE_X);
  }
  else {
    if (language) {
       strcpy (text_file,  TEXT_FILE_E);
       strcpy (index_file, INDEX_FILE_E);
    }
    else {
       strcpy (text_file,  TEXT_FILE_R);
       strcpy (index_file, INDEX_FILE_R);
    }
  }

  f_src = fopen (text_file, "r");
  if (f_src==NULL) {
     sprintf (msg_err, "Cannot open file %s\n", text_file);
     Error (msg_err, 0);
  }

  f_idx = fopen (index_file, "rb");
  if (f_idx==NULL) {
     sprintf (msg_err, "Cannot open file %s\n", index_file);
     Error (msg_err, 0);
  }
}

/**********************************************************************/
static void print_one_block (long offs) {
    LINE str;

    fseek (f_src, offs, SEEK_SET);
    while (fgets (str, MAX_LEN_LINE, f_src)!=NULL) {

      if (strchr(str,'\n')==NULL)
         printf ("%s\n", str);
      else
         printf ("%s", str);
      if (!str[0] || str[0]=='\n' || str[0]=='\r') break;
    }
    printf ("\n");
}


/**********************************************************************/
static void print_text (unsigned long offs) {
    printf("     <textarea rows=10 cols=80 name=comments wrap=virtual>\n");
    if (program_error) {
        printf ("Program error report: %s<br>\n", str_error);
    }
    else
    if (error_report) {
        if (!language) {
           printf(" %s\n", RUS_ERROR_MSG);
           printf("     Анекдот номер %d на полосатом роботе\n", start_number);
	   }
        else
           printf(" %s\n", ENG_ERROR_MSG);
           printf("     The joke number %d at \"Passed Jokes\" robot\n",
                start_number);
        printf("     %s%s\n", KULICHKI_URL, Get_Program_Path());
        print_one_block (offs);
    }
    else { // not program error, not error report, it means,
           // just sending info to friend
       if (!language) {
         printf ("Чиста пацанам в тему хохма номер %d\n", start_number);
         printf ("на роботе полосатых анекдотов\n");
       }
       else {
         printf ("Cool joke number %d\n", start_number);
         printf ("at \"Passed Jokes\" robot\n");
       }
       printf ("%s%s?n=%d&l=%d\n",
               KULICHKI_URL, Get_Program_Path (), start_number, language);

       if (!link_only)
           print_one_block (offs);
    }
    printf("\n");
    printf("     </textarea>\n");
}

/**********************************************************************/
int main () {
    long offs;
    long offset_in_idx_file;
    long random_index;

    printf ("Content-Type: text/html\n\n");
    printf("<html><body>\n");

    get_parameters ();

    open_files (x_text, language);
    random_index = start_number;
    offset_in_idx_file = (random_index) << 2;
    fseek (f_idx, offset_in_idx_file, SEEK_SET);
    fread ((void *)&offs, sizeof(offs), 1, f_idx);

    printf("    <form method=post action=\"%s\">\n", FORMMAIL_PATH);
    printf("\n");
    printf("<input type=hidden name=title value=\"SendJoke Form Results\">\n");
    printf("    <input type=hidden name=return_link_title ");
    printf(" value=\"Back to Main Page\">\n");
    printf("    <input type=hidden name=bgcolor value=\"#FFFFFF\">\n");
    printf("    <input type=hidden name=text_color value=navy>\n");
    printf("    <input type=hidden name=link_color value=\"#FF0000\">\n");
    printf("    <input type=hidden name=vlink_color value=\"#0000FF\">\n");
    printf("    <input type=hidden name=alink_color value=\"#0000FF\">\n");
    printf("\n");
/*
    printf("   <input type=hidden name=\"return_link_url\"\n");
    printf("          value=\"%s%s%s\">\n",
                      KULICHKI_URL, PROGRAM_PATH, program_params);
    printf("    <input type=hidden name=redirect\n");
    printf("          value=\"%s%s%s\">\n",
                      KULICHKI_URL, PROGRAM_PATH, program_params);
    printf("\n");
*/

    printf("    <input type=hidden name=subject  value=\"Anekdot\">\n");
    printf("<input type=hidden name=required value=\"recipient,email\"><br>\n");
    printf("\n");

    if (!error_report) {
      printf("     To: <input type=text name=recipient size=30 ");
      printf(" value=\"email@domain\"><br>\n");
    }
    else {
      printf("<input type=hidden name=recipient size=30 ");
      printf("value=\"%s\"><br>\n", TIGER_EMAIL);
    }

    printf("From: &nbsp; &nbsp;\n");

    if (!language)
    printf("<input type=text NAME=realname     SIZE=30 value=\"Кореш\"><br>\n");
    else
    printf("<input type=text NAME=realname     SIZE=30 value=\"Pal\"><br>\n");
    printf("EMail:\n");

    printf("<input type=text NAME=email     ");
    printf("SIZE=30 value=\"yourname@domain\"><br>\n");

    printf("<font size=+1><input TYPE=submit VALUE=\"Send\"></font><br><br>\n");
    printf("\n");

    print_text (offs);
    printf("     </form>\n");
    printf("</body></html>\n");

    fclose (f_src);
    fclose (f_idx);

    return 0;
}
