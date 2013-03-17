/**********************************************************************/
/*                              Files.c                               */
/**********************************************************************/

#include <stdio.h>
//#include <string.h>

#include "an_r.h"
#include "an_prot.h"


/**********************************************************************/
static  FILE *f_text  = NULL,
             *f_words = NULL,
             *f_ofidx = NULL,
             *f_nums  = NULL,
             *f_index = NULL;

/***********************************************************************/
/* it's possible to open text & index files or all of them, according  */
/* to the last parameter (use_search_files)                            */
/***********************************************************************/
int Files_Open (char *text_file_name,
                char *index_file_name,
                char *words_file_name,
                char *ofidx_file_name,
                char *nums_file_name,
                int  use_search_files) {
  LINE str;

 if (Files_Open_Src_File (text_file_name))
     return -1;

 if (Files_Open_Idx_File (index_file_name))
     return -2;

  if (! use_search_files) return 0;

  f_words = fopen (words_file_name, "r");
  if (f_words==NULL) {
     sprintf (str, "Cannot open file %s", words_file_name);
     Error (str, 1);
  }

  f_ofidx = fopen (ofidx_file_name, "rb");
  if (f_ofidx==NULL) {
     sprintf (str, "Cannot open file %s", ofidx_file_name);
     Error (str, 1);
  }

 if (Files_Open_Nums_File (nums_file_name))
     return -3;
  
  return 0;
}

/***********************************************************************/
void Files_Close (void) {
    if (f_text !=NULL) {fclose (f_text);  f_text=NULL;}
    if (f_words!=NULL) {fclose (f_words); f_words=NULL;}
    if (f_ofidx!=NULL) {fclose (f_ofidx); f_ofidx=NULL;}
    if (f_nums !=NULL) {fclose (f_nums);  f_nums=NULL;}
    if (f_index!=NULL) {fclose (f_index); f_index=NULL;}
}



/**********************************************************************/
int Files_Open_Src_File (char *s_text_file) {
  LINE msg;
  f_text = fopen (s_text_file, "r");
  if (f_text==NULL) {
     sprintf (msg, "Cannot open text file %s\n", s_text_file);
     Error (msg, 1);
     return 1;
  }
  return 0;
}

/**********************************************************************/
int Files_Open_Nums_File (char *s_num_file) {
  LINE msg;
  f_nums = fopen (s_num_file, "rb");
  if (f_nums==NULL) {
     sprintf (msg, "Cannot open num file %s\n", s_num_file);
     Error (msg, 1);
     return 1;
  }
  return 0;
}

/**********************************************************************/
void Files_Close_Nums_File (void) {
  if (f_nums!=NULL) {fclose (f_nums); f_nums=NULL;}
}

/**********************************************************************/
int Files_Open_Idx_File (char *s_idx_file) {
  LINE msg;
  f_index = fopen (s_idx_file, "rb");
  if (f_index==NULL) {
     sprintf (msg, "Cannot open index file %s\n", s_idx_file);
     Error (msg, 1);
     return 1;
  }
  return 0;
}

/**********************************************************************/
void Files_Close_Idx_File (void) {
  if (f_index!=NULL) {fclose (f_index); f_index=NULL;}
}


/**********************************************************************/
long Files_Get_Blocks_Number (void) {
   return (Filesize (f_index) >> 2);
}

/**********************************************************************/
long Files_Get_Nums_Number (void) {
   return (Filesize (f_nums) >> 2);
}

/**********************************************************************/
void Files_Get_Offset_From_Index (long offset_in_idx_file, 
                                  void *offs, int size) {
    if (f_index==NULL)
       Error("Files_Offset_From_Index: the index file is not opened", 1);
    if (fseek (f_index, offset_in_idx_file, SEEK_SET))
	Error ("Files_Get_Offset_From_Index: Fseek error", 1);
    if (! fread ((void *)offs, size, 1, f_index))
        Error ("Files_Get_Offset_From_Index: Fread error", 1);
}

/**********************************************************************/
void Files_Get_Line (long offs, char *str) {
    if (f_text==NULL)
        Error("Files_Get_Line: the source file is not opened", 1);
    if (fseek (f_text, offs, SEEK_SET))
        Error ("Files_Get_Line Fseek error", 1);
    if (fgets (str, MAX_LEN_LINE, f_text) == NULL)
	Error ("Files_Get_Line: can't get the text", 1);
}

/**********************************************************************/
char* Files_Get_Next_Line (char *str) {
    if (f_text==NULL)
       Error("Files_Get_Next_Line: the source file is not opened", 1);
    return (fgets (str, MAX_LEN_LINE, f_text));
}

/**********************************************************************/
void Files_Seek_Text (long offs) {
    if (f_text==NULL)
       Error("Files_Seek_To_Offset: the source file is not opened", 1);
    if (fseek(f_text, offs, SEEK_SET))
       Error("SeekToOffset fseek error", 1);
}

/**********************************************************************/
void Files_Seek_Ofidx (unsigned long offset_in_file) {
   LINE msg;
   int rc;
   rc = fseek (f_ofidx, offset_in_file, SEEK_SET);
   if (rc) {
      sprintf (msg, "Files_Seek_In_Ofidx: Can't fseek to %ld (rc=%d)\n",
	       offset_in_file, rc);
      Error (msg, 1);
   }
}

/**********************************************************************/
void Files_Get_From_Ofidx (unsigned long *offs_in_numbers) {
   LINE msg;
   int rc;
   rc=fread (offs_in_numbers, sizeof(long),1,f_ofidx);
   if (!rc) {
      sprintf (msg, "Files_Get_From_Ofidx: Can't fread from Ofidx (rc=%d)\n",
	       rc);
      Error (msg, 1);
   }
}

/**********************************************************************/
void Files_Seek_Nums (unsigned long offset_in_file) {
   LINE msg;
   int rc;
   rc=fseek (f_nums, offset_in_file, SEEK_SET);
   if (rc) {
      sprintf (msg, "Files_Seek_Nums: Can't fseek to %ld (rc=%d)\n",
	       offset_in_file, rc);
      Error (msg, 1);
   }
}

/**********************************************************************/
void Files_Get_From_Nums (unsigned long *num) {
   LINE msg;
   int rc;
   rc=fread (num, sizeof(num), 1, f_nums);
   if (!rc) {
       sprintf (msg, "Files_Get_from_Nums: Can't fread (rc=%d)\n", rc);
       Error (msg, 1);
   }
}

/**********************************************************************/
char* Files_Get_Next_Word (char *str) {
    if (f_words==NULL)
       Error("Files_Get_Next_Word: the source file is not opened", 1);
    return (fgets (str, MAX_LEN_LINE, f_words));
}

