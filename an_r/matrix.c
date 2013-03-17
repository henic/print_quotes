
/**********************************************************************/
/*                             Matrix.c                               */
/**********************************************************************/

#include "string.h"

#include "an_r.h"
#include "an_s.h"
#include "an_prot.h"
#include "flags.h"

/**********************************************************************/
static unsigned int   nWordsMatrixLen=0u;
static unsigned long  nWordsMatrix  [MAX_FOUNDS];
static unsigned int   nWordsKwds    [MAX_FOUNDS];


/**********************************************************************/
static unsigned int   nNumbersMatrixLen=0u;
static unsigned long  nNumbersMatrix[MAX_FOUNDS];
static unsigned int   nNumbersKwds  [MAX_FOUNDS];

/**********************************************************************/
static unsigned int   nResultLen=0u;
static unsigned long  nResult  [MAX_FOUNDS];

/**********************************************************************/
/*                   static functions prototypes                      */
/**********************************************************************/
static void Randomize_Results    (int n);
static void Matrix_Find_Words    (void);
static void Matrix_Find_Numbers  (void);
static void Matrix_Fill_With_Theme (long  start_number,
                 short repeats_number,
                 short theme,
                 short random_choosing);
static void Matrix_Fill_With_Offsets(void);


// matrix_numbers class
static void Matrix_Add_Number    (int keyword_number, unsigned long number);
static void Matrix_Numbers_Print (void);

// matrix_words class
static void Matrix_Add_Word      (int keyword_number, unsigned long number);
static void Matrix_Words_Print   (void);


/**********************************************************************/
/*                        Global functions                            */
/**********************************************************************/



/**********************************************************************/
unsigned int Matrix_Numbers_Size (void) {
  return nResultLen; //nNumbersMatrixLen;
}

/**********************************************************************/
unsigned long Matrix_Numbers_Get  (unsigned short index)  {
  if (index>=MAX_FOUNDS)
     Error ("Matrix_Get_Number: Inappropriate index", 1);
  return /*nNumbersMatrix*/ nResult[index];
}

/**********************************************************************/
void Matrix_Ans_Get_Blocks (void) {
  Matrix_Find_Words ();
  Matrix_Find_Numbers ();
}

/**********************************************************************/
void Matrix_Anr_Get_Blocks (void) {
    long  block_to_add;                   // the block number to be added
    long  start_number;                   // start number; may be ignored
    long  max_index;                      // total blocks number
    short repeats_number;                 // how many blocks to get
    short random_choosing;                // 0 if consequent
    short i;                              // counter

    nResultLen=0;
    random_choosing= Flags_Get_Random_Choosing ();
    repeats_number = Flags_Get_Repeats_Number ();
    max_index      = Flags_Get_Blocks_Number ();
    start_number   = Flags_Get_Start_Number ();
    switch (Flags_Get_Keyword_Type()) {
      case UNDEFINED_KEYWORD:      // standard random choosing
      for (i=0; i<repeats_number; i++) {
         block_to_add = (random_choosing ?
                          (Get_Random_Number() % max_index) :
                          start_number+i);
         if (block_to_add>=max_index)
            continue;
         Matrix_Add_Number(0, block_to_add);
         nResult[i]=block_to_add;
         nResultLen++;
      }
      break;

      case PREDEFINED_KEYWORD:     // choosing with predefined theme
          Matrix_Fill_With_Theme (start_number,  repeats_number,
                                  Flags_Get_Theme(), random_choosing);
      break;

      case USER_DEFINED_KEYWORD:
          Matrix_Fill_With_Offsets();
          break;

      default:
      Error("Unexpected KeywordType value", 1);
    }
}

/**********************************************************************/
static void Matrix_Proceed_Numbers (void) {
  Sort_And_Exclude (nNumbersMatrix, nNumbersKwds, &nNumbersMatrixLen);
  Sort_Remove_Doubles (nNumbersMatrix, nNumbersMatrixLen,
                       &nResultLen, nResult, Flags_Get_And_Or_Flag());
  if (Flags_Get_Random_Choosing()) {
     Randomize_Results (Flags_Get_Repeats_Number());
     Flags_Set_Start_Number (0);
  }
}


/**********************************************************************/
static void Matrix_Find_Numbers (void) {
  unsigned long word_number;
  int kwd_number;
  long offset_in_file;
  unsigned long num;
  int blocks_number;
  int i;
  int k;
  unsigned long offs_in_numbers, next_offs_in_numbers;
  for (i=0; i<nWordsMatrixLen; i++) {
      word_number = nWordsMatrix[i];
      kwd_number  = nWordsKwds[i];
      /* Find first offset */
      offset_in_file = word_number*sizeof(long);
      Files_Seek_Ofidx (offset_in_file);
      Files_Get_From_Ofidx(&offs_in_numbers);

      /* Find next offset */
      offset_in_file = (word_number+1)*sizeof(long);
      Files_Seek_Ofidx(offset_in_file);
      Files_Get_From_Ofidx(&next_offs_in_numbers);

      /* Compute number of found words */
      blocks_number = (int)(next_offs_in_numbers - offs_in_numbers) /
                sizeof(long);
      Files_Seek_Nums (offs_in_numbers);
      for (k=0; k<blocks_number; k++) {
        Files_Get_From_Nums (&num);
        Matrix_Add_Number(kwd_number, num);
      }
  }
#ifdef TEST_VERSION  
  Matrix_Numbers_Print ();
#endif
  Matrix_Proceed_Numbers ();
}

/**********************************************************************/
static void Matrix_Find_Words (void) {
  LINE str;
  int kwd_cnt;
  int nKeywords_Number = Keywords_Get_Size();
  unsigned long words_cnt=0L;
  nWordsMatrixLen=0;
  while (Files_Get_Next_Word(str) != NULL) {
     for (kwd_cnt=0;   // for all keywords
          kwd_cnt<nKeywords_Number;
          kwd_cnt++)
        // if keyword is found
        if (strstr (str, Keywords_Get(kwd_cnt)) != NULL)
           Matrix_Add_Word (kwd_cnt, words_cnt);
     words_cnt++;
  }
  Sort_And_Exclude (nWordsMatrix, nWordsKwds, &nWordsMatrixLen);
#ifdef TEST_VERSION  
  Matrix_Words_Print ();
#endif
}


/**********************************************************************/
static void Matrix_Fill_With_Theme (long  start_number,
                             short repeats_number,
                             short theme,
                             short random_choosing) {
    LINE theme_fname;
    //LINE msg;
    long theme_length;
    long block_to_add;
    long num;
    int  cnt;

    sprintf (theme_fname, "%s%d.idx", THEME_NAME_PREFIX, theme);
    Files_Close_Nums_File ();
    Files_Open_Nums_File (theme_fname);
    theme_length = Files_Get_Nums_Number();
    for (cnt=0; 
         cnt<theme_length && 
         cnt<repeats_number &&
         start_number+cnt<theme_length; 
         cnt++) {

       num = random_choosing ?
                 (Get_Random_Number() % theme_length) :
                 start_number+cnt;
       Files_Seek_Nums (sizeof(block_to_add)*num);
       Files_Get_From_Nums (&block_to_add);
       Matrix_Add_Number (0, block_to_add);
    }
    Matrix_Proceed_Numbers ();
}


/**********************************************************************/
// well the most difference from the predefined theme: we never know
// how long the theme is. So have to find almost all suitable blocks
static void Matrix_Fill_With_Offsets(void) {

  if (! Keywords_Get_Size()) {
        Error ("No keys given", 0);
        return;
  }
  Matrix_Find_Words ();
  Matrix_Find_Numbers();
}





/**********************************************************************/
static void Matrix_Numbers_Print (void) {
    unsigned int i;
    printf ("<b>%d items</b>\n", nNumbersMatrixLen);
    for (i=0; i<nNumbersMatrixLen; i++)
    printf ("[%d:%d] ", nNumbersMatrix[i], nNumbersKwds[i]);
    printf ("<br><br>\n");
}

/**********************************************************************/
static void Matrix_Words_Print (void) {
    unsigned int i;
    printf ("<b>%d items</b>\n", nWordsMatrixLen);
    for (i=0; i<nWordsMatrixLen; i++)
    printf ("[%d:%d] ", nWordsMatrix[i], nWordsKwds[i]);
    printf ("<br><br>\n");
}

/**********************************************************************/
static void Matrix_Add_Word (int keyword_number, unsigned long number) {
  nWordsKwds[nWordsMatrixLen]     = keyword_number;
  nWordsMatrix[nWordsMatrixLen++] = number;
  if (nWordsMatrixLen==MAX_FOUNDS-1)
      Error("Too many words found", 1);
}

/**********************************************************************/
static void Matrix_Add_Number (int keyword_number, unsigned long number) {
  //printf ("Add %ld \n", number);
  nNumbersKwds  [nNumbersMatrixLen]   = keyword_number;
  nNumbersMatrix[nNumbersMatrixLen++] = number;
  if (nNumbersMatrixLen==MAX_FOUNDS-1)
      Error("Too many numbers found. Refine your search", 0);
}

/**********************************************************************/
static void Randomize_Results (int n) {
 int i;
 unsigned long tmp; 
 float ffactor;
 int   nfactor;
 if (n>=nResultLen-1) return;
 ffactor = (float)nResultLen/(float)n; 
 nfactor = (int)ffactor;
 for (i=0; i<n; i++) {
   nResult[i] = nResult[(int)(i*ffactor)+(Get_Random_Number()%nfactor)]; 
 }
}
