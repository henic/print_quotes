
/***************************************************************************/
/* An_prot.h                Functions Prototypes                           */
/***************************************************************************/
#ifndef _AN_PROT_H_
#define _AN_PROT_H_

/* advert.c */
void    Adv_Print_Advert          (void);
void    Adv_Print_Top          (void);
void    Adv_Print_Rambler_Code    (unsigned short code);
void    Adv_Print_Rambler_Image   (void);
void    Adv_Print_RB2             (long random_number);
void    Adv_Print_RLE             (long random_number);
void    Adv_Print_RLE_RB2         (long random_number);
void    Adv_Print_RLE_RLE100      (long random_number);


void    Block_Add_String      (char *str); 
int     Block_Keyword_Found   (char *kwrd, short ignore_case);
void    Block_Print           (long index);
void    Block_Read            (long offs);
void    Block_Reset           (void);

/* colors.c */
short   Colors_Get_Black      (void);
short   Colors_Get_Rand       (void);
short   Colors_Get_First      (void);
short   Colors_Get_Second     (void);
short  *Colors_Get_Six_Colors (void);
char   *Colors_Get_Text_Color (void);
void    Colors_Set            (long   random_number);
void    Colors_Set_Black      (short nblack);

int     CheckBlock            (short and_or_flag, short ignore_case);
void    Check_Keyword_Is_OK   (char *kwd);
void    Error                 (char *msg, int program_error);

/* files.c */
void	Files_Close	      (void);
void    Files_Close_Idx_File  (void);
void    Files_Close_Nums_File (void);
long    Files_Get_Blocks_Number(void);
long    Files_Get_Nums_Number(void);
void    Files_Get_Line        (long offs, char *str);
char   *Files_Get_Next_Line   (char *str);
void    Files_Get_Offset_From_Index
                   (long offset_in_idx_file, void *offs, int size);
int     Files_Open (char *text_file_name,
                    char *index_file_name,
                    char *words_file_name,
                    char *ofidx_file_name,
                    char *nums_file_name,
                    int  use_search_files);
//int     Files_Open_Src_File   (char *s_text_file);
int     Files_Open_Idx_File   (char *s_idx_file);
int     Files_Open_Nums_File  (char *s_num_file);
void    Files_Seek_Text       (long offs);
long    Filesize              (FILE *stream);
void    Files_Seek_Ofidx      (unsigned long offset_in_file);
void    Files_Get_From_Ofidx  (unsigned long *offs_in_numbers);
void    Files_Seek_Nums       (unsigned long offset_in_file);
void    Files_Get_From_Nums   (unsigned long *num);
char*   Files_Get_Next_Word   (char *str);


int     Found_Substring       (char *str, char *templ);

char	*Get_Args_Str	      (void);

char*   Get_Program_Path      (void);

long    Get_Random_Number     (void);

/* header.c */
void    Header_SearchPrint    (void);
void    Header_TailPrint      (void);
void    Header_AnrPrint       (void);


/* hex2asc.c */
void    Hex2Ascii              (char *src, char *dst);

/* keywords.c */
void    Keywords_Add                 (char *sKwd);
void    Keywords_Extract             (char *list_params, int list_params_len);
char*   Keywords_Get                 (int n);
int     Keywords_Get_Size            (void);
void    Keywords_Print               (void);
void    Keywords_Proceed_Ignore_Case (short ignore_case);
int     Keywords_Search              (char *str, int *offset);

/* matrix.c */
unsigned int  Matrix_Numbers_Size   (void);
unsigned long Matrix_Numbers_Get    (unsigned short index);
void          Matrix_Anr_Get_Blocks (void);
void          Matrix_Ans_Get_Blocks (void);

/* oneline.c */
void Oneline (void);

/* params.c */
void    Params_Get            (void);
void    Params_Print          (void);

/* print.c */
void    Print_AnrBlocks       (void);
void    Print_AnsBlocks       (void);
void    Print_Config          (void);
void    Print_FButtons        (long index);
void    Print_Highlight       (char* str, int ofs, char* kwd);
void    Print_Invitation      (long rand_number);
void    Print_Links           (int advanced_version);
void    Print_Last_Links      (void);
void    Print_Midi_Console    (void);
void    Print_Question        (int need_question, long random_number);
void    Print_Subscription    (void);
void    Print_Warning         (void);

/* reload.c */
void Reload_Button_Print      (short advanced_ver, short repeats, long rnd);

/* search.c */
void    Search_Print          (long random_number);

/* serv.c */
int Serv_Is_Delimiter (char ch);

/* sort.c */
void Sort_And_Exclude (unsigned long *ptr,
		       unsigned int *kwd, unsigned int *length);
void Sort_Remove_Doubles (unsigned long *buf,
                          unsigned int  len,
                          unsigned int  *pLen,
                          unsigned long *result,
                          int           and_flag);


/* stat.c */
void    Get_Statistics        (void);
void    Save_Statistics       (int search);
void    Save_Msg_Finished     (void);

/* tolower.c */
void    Tolower_Init_Ascii_Table (void);
void    Tolower_String        (char *src, char *dst);

/* --------- */

#endif

