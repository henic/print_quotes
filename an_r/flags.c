/**********************************************************************/
/*                          Global flags                              */
/**********************************************************************/

#include "an_s.h"
#include "flags.h"

static long         random_number;
static long         start_number     = 0;
static long         blocks_number    = 0;/* how many blocks the file contains */

static short        advanced_version = 1;
static short        answer           = 0;
static short        is_repeater      = 0;
static short        need_question    = 0;
static short        repeats_number   = 3;   /* how many blocks to get */

/**********************************************************************/
/*                          Search flags                              */
/**********************************************************************/
static short        random_choosing  = 1;
static short        and_or_flag      = 0;
static short        theme            = 0;
static short        ignore_case      = IGNORE;
static short        keyword_type     = UNDEFINED_KEYWORD;
static short        highlight        = 1;
static short        mustdie          = 0;
static short        bonus            = 0;
static short        language         = 0;
/* short exact_search  = SUBSTR;*/

long  Flags_Get_Random_Number    (void) {return random_number;}
long  Flags_Get_Start_Number     (void) {return start_number;}
long  Flags_Get_Blocks_Number    (void) {return blocks_number;}

short Flags_Get_Advanced_Version (void) {return advanced_version;}
short Flags_Get_Answer           (void) {return answer;}
short Flags_Get_Is_Repeater      (void) {return is_repeater;}
short Flags_Get_Need_Question    (void) {return need_question;}
short Flags_Get_Repeats_Number   (void) {return repeats_number;}

short Flags_Get_Random_Choosing  (void) {return random_choosing;}
short Flags_Get_And_Or_Flag      (void) {return and_or_flag;}
short Flags_Get_Theme            (void) {return theme;}
short Flags_Get_Ignore_Case      (void) {return ignore_case;}
short Flags_Get_Keyword_Type     (void) {return keyword_type;}
short Flags_Get_Highlight        (void) {return highlight;}
short Flags_Get_MustDie          (void) {return mustdie;}
short Flags_Get_Bonus            (void) {return bonus;}
short Flags_Get_Language         (void) {return language;}


void  Flags_Set_Random_Number    (long  lRandom_Number)    {random_number   = lRandom_Number;}
void  Flags_Set_Start_Number     (long  lStart_Number)     {start_number    = lStart_Number;}
void  Flags_Set_Blocks_Number    (long  lBlocks_Number)    {blocks_number   = lBlocks_Number;}

void  Flags_Set_Advanced_Version (short nAdvanced_Version) {advanced_version= nAdvanced_Version;}
void  Flags_Set_Answer           (short nAnswer)           {answer          = nAnswer;}
void  Flags_Set_Is_Repeater      (short nIs_Repeater)      {is_repeater     = nIs_Repeater;}
void  Flags_Set_Need_Question    (short nNeed_Question)    {need_question   = nNeed_Question;}
void  Flags_Set_Repeats_Number   (short nRepeats_Number)   {repeats_number  = nRepeats_Number;}

void  Flags_Set_Random_Choosing  (short nRandom_Choosing)  {random_choosing = nRandom_Choosing;}
void  Flags_Set_And_Or_Flag      (short nAnd_Or_Flag)      {and_or_flag     = nAnd_Or_Flag;}
void  Flags_Set_Theme            (short nTheme)            {theme           = nTheme;}
void  Flags_Set_Ignore_Case      (short nIgnore_Case)      {ignore_case     = nIgnore_Case;}
void  Flags_Set_Keyword_Type     (short nKeyword_Type)     {keyword_type    = nKeyword_Type;}
void  Flags_Set_Highlight        (short nHighlight) 	   {highlight	    = nHighlight;}
void  Flags_Set_MustDie          (short nMD) 	           {mustdie  = nMD;}
void  Flags_Set_Bonus            (short nBonus) 	   {bonus    = nBonus;}
void  Flags_Set_Language         (short nLang) 	   	   {language = nLang;}
