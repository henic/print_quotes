/************************************************************************/
/*                                flags.h                               */
/************************************************************************/

#ifndef _FLAGS_H_
#define _FLAGS_H_

long  Flags_Get_Random_Number    (void);
long  Flags_Get_Start_Number     (void);
long  Flags_Get_Blocks_Number    (void);

short Flags_Get_Advanced_Version (void);
short Flags_Get_Answer           (void);
short Flags_Get_Is_Repeater      (void);
short Flags_Get_Need_Question    (void);
short Flags_Get_Repeats_Number   (void);

short Flags_Get_Random_Choosing  (void);
short Flags_Get_And_Or_Flag      (void);
short Flags_Get_Theme            (void);
short Flags_Get_Ignore_Case      (void);
short Flags_Get_Keyword_Type     (void);
short Flags_Get_Highlight        (void);
short Flags_Get_MustDie          (void);
short Flags_Get_Bonus            (void);
short Flags_Get_Language         (void);


void  Flags_Set_Random_Number    (long  lRandom_Number);
void  Flags_Set_Start_Number     (long  lStart_Number);
void  Flags_Set_Blocks_Number    (long  lBlocks_Number);

void  Flags_Set_Advanced_Version (short nAdvanced_Version);
void  Flags_Set_Answer           (short nAnswer);
void  Flags_Set_Is_Repeater      (short nIs_Repeater);
void  Flags_Set_Need_Question    (short nNeed_Question);
void  Flags_Set_Repeats_Number   (short nRepeats_Number);

void  Flags_Set_Random_Choosing  (short nRandom_Choosing);
void  Flags_Set_And_Or_Flag      (short nAnd_Or_Flag);
void  Flags_Set_Theme            (short nTheme);
void  Flags_Set_Ignore_Case      (short nIgnore_Case);
void  Flags_Set_Keyword_Type     (short nKeyword_Type);
void  Flags_Set_Highlight        (short nHighlight);
void  Flags_Set_Bonus            (short nBonus);
void  Flags_Set_MustDie          (short nMD);
void  Flags_Set_Language         (short nLang);

#endif

