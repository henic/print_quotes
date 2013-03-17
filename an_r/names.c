/**********************************************************************/
/*                             Names.c                                */
/**********************************************************************/

#include "an_r.h"
#include "names.h"

static LINE 
     text_file_name, 
     index_file_name,
     words_file_name,
     ofidx_file_name,
     nums_file_name;

void Names_Set_Files (void) {
  if (Flags_Get_Language()) {
     strcpy (text_file_name,  TEXT_FILE_E);
     strcpy (index_file_name, INDEX_FILE_E);
     strcpy (words_file_name, WORDS_FILE_E);
     strcpy (ofidx_file_name, OFIDX_FILE_E);
     strcpy (nums_file_name,  NUMS_FILE_E);
  }
  else {
     strcpy (text_file_name,  TEXT_FILE_R);
     strcpy (index_file_name, INDEX_FILE_R);
     strcpy (words_file_name, WORDS_FILE_R);
     strcpy (ofidx_file_name, OFIDX_FILE_R);
     strcpy (nums_file_name,  NUMS_FILE_R);
  }
}

char* Names_Get_Text_File  (void) {return text_file_name;}
char* Names_Get_Index_File (void) {return index_file_name;}
char* Names_Get_Words_File (void) {return words_file_name;}
char* Names_Get_Ofidx_File (void) {return ofidx_file_name;}
char* Names_Get_Nums_File  (void) {return nums_file_name;}

