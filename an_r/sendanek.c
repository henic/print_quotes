/***************************************************************************/
/*                            SendAnek.c                                   */
/***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "an_r.h"
#include "an_prot.h"

/***************************************************************************/
long int start_number;
short error_report;
short link_only=0;
short program_error=0;
short language=0;
short mini_version=0;

static LINE args_str, ascii_args_str;
static LINE str_error;

static FILE *f_src, *f_idx;


/* the following function is unused but required for compatibility 
   with the rest of programs (linker should know it) 
*/
char* Get_Args_Str (void) {return "";}

/***********************************************************************/
/* get_parameters                                                      */
/*                                                                     */
/*                                                                     */
/* Possible parameters got from callee:                                */
/* int  n       start block number                                     */
/* bool l       1 if link only, 0 otherwise                            */
/* bool e       1 if it's error report, 0 - if information             */
/* bool a       1 if the language is "English"                         */
/* bool p       1 if it's program error (required contact the author)  */
/* bool m       1 if mini-version, 0 if the full one                   */
/* char* s      error message                                          */
/*                                                                     */
/*                                                                     */
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
    }
    else
    if (passed_parameter[0] == 'm' &&
        passed_parameter[1] == '=') {
        if (sscanf (passed_parameter+2, "%d", &mini_version) != 1)
           Error ("Invalid Version parameter", 0);
    }
    else
    if (passed_parameter[0] == 'e' &&
        passed_parameter[1] == '=') {
        if (sscanf (passed_parameter+2, "%d", &error_report) != 1)
           Error ("Invalid ErrorReport parameter", 0);
    }
    else
    if (passed_parameter[0] == 'a' &&
        passed_parameter[1] == '=') {
        if (sscanf (passed_parameter+2, "%d", &language) != 1)
           Error ("Invalid language parameter", 0);
    }
    else
    if (passed_parameter[0] == 'p' &&
        passed_parameter[1] == '=') {
        if (sscanf (passed_parameter+2, "%d", &program_error) != 1)
           Error ("Invalid Link parameter", 0);
    }
    else
    if (passed_parameter[0] == 's' &&
        passed_parameter[1] == '=')
        strcpy (str_error, passed_parameter+2);
    passed_parameter=strtok (NULL, "&");
  } while (passed_parameter!=NULL);
}

/**********************************************************************/
static void open_files (char *s_text_file, char *s_index_file) {
  LINE msg_err;
  f_src = fopen (s_text_file, "r");
  if (f_src==NULL) {
     sprintf (msg_err, "Cannot open file %s\n", s_text_file);
     Error (msg_err, 0);
  }

  f_idx = fopen (s_index_file, "rb");
  if (f_idx==NULL) {
     sprintf (msg_err, "Cannot open file %s\n", s_index_file);
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
    if (! link_only) {
      if (program_error) {
         printf ("Program error report: %s<br>\n", str_error);
      }
      if (error_report) {
        if (!language)
           printf(" Мне кажется, имеет место быть ошибка:\n");
        else
           printf(" I think the following joke contains error:\n");
      }

      if (!language)
         printf("     Анекдот номер %d на полосатом роботе\n", start_number);
      else 
         printf("     The joke number %d at \"Passed Jokes\" robot\n", 
                start_number);
 
      printf("     http://www.kulichki.com%s\n", Get_Program_Path());
      print_one_block (offs);
    }
    else {
      if (!language) {
        printf ("Чиста пацанам в тему хохма номер %d\n", start_number);
        printf ("на роботе полосатых анекдотов\n");
      }
      else {
        printf ("Cool joke number %d\n", start_number);
        printf ("at \"Passed Jokes\" robot\n");
      }
      printf ("http://www.kulichki.com%s?n=%d&l=%d\n",    
                                        Get_Program_Path (), 
                                        start_number, language);
    }

    printf("\n");
    printf("     </textarea>\n");
}

/**********************************************************************/
int main () {
    LINE text_file, index_file;
    long offs;
    long offset_in_idx_file;
    long random_index;

    printf ("Content-Type: text/html\n\n");
    printf("<html><body>\n");

    get_parameters ();
    if (language) {
       strcpy (text_file,  TEXT_FILE_E);
       strcpy (index_file, INDEX_FILE_E);
    } 
    else {
       strcpy (text_file,  TEXT_FILE_R);
       strcpy (index_file, INDEX_FILE_R);
    }

    open_files   (text_file, index_file);
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
    printf("          value=\"http://www.kulichki.com%s%s\">\n", 
             PROGRAM_PATH, program_params);
    printf("    <input type=hidden name=redirect\n");
    printf("          value=\"http://www.kulichki.com%s%s\">\n", 
             PROGRAM_PATH, program_params);
    printf("\n");
*/

    printf("    <input type=hidden name=subject  value=\"Anekdot\">\n");
    printf("<input type=hidden name=required value=\"recipient,email\"><br>\n");
    printf("\n");

    if (!error_report) {
      printf("     %s: <input type=text name=recipient size=30 ",
             language ? "To" : "To");
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
