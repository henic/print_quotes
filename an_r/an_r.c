/***********************************************************************/
/* An_r.c - the program which reads from file some random blocks       */
/*                                                                     */
/* Copyright (C) Victor Bolotnikov, Tigers Ltd, 1997-2000 			   */
/*                                                                     */
/* Comments & suggestions to tiger@kulichki.com                        */
/*                                                                     */
/* Last edition: 25-Apr-00                                             */
/*                                                                     */
/* Known bugs: None                                                    */
/***********************************************************************/

/*
 *              Copyright Statement, Tigers Ltd, 1993-2000
 *
 * This software contains proprietary and trade secret information
 * of Tigers Ltd and is protected by Federal Copyright law.
 * This software can not be copied or distributed in any form, including
 * electronic, magnetic, paper and verbal medium, or disclosed
 * to any third party or any person. It can be distributed or used only 
 * as mentioned in the license agreement signed Tigers Ltd.
 */  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "an_r.h"
#include "an_s.h"
#include "an_prot.h"
#include "flags.h"
#include "names.h"

/**********************************************************************/
int main (void) {
  long random_number;
  short advanced_version;
  int rc;


  srand ((unsigned)time(NULL));
  random_number = Get_Random_Number ();

#ifdef ENG
Flags_Set_Language (ENGLISH);
#else
Flags_Set_Language (RUSSIAN);
Flags_Set_Theme (random_number % MAX_NUM_THEMES);
#endif

  Colors_Set (random_number);
  Header_AnrPrint ();
  Adv_Print_Rambler_Code (RAMBLER_CODE);
  Tolower_Init_Ascii_Table ();
  Flags_Set_Keyword_Type (UNDEFINED_KEYWORD);
  Params_Get();
  Names_Set_Files ();

  Keywords_Proceed_Ignore_Case (Flags_Get_Ignore_Case());

  Adv_Print_Advert();
  advanced_version = Flags_Get_Advanced_Version();
  Print_Links (advanced_version);
  if (advanced_version) {
     //Print_Invitation (second_color);
     Print_Subscription();
     Search_Print (random_number);
  }

  rc = Files_Open (Names_Get_Text_File(), 
                   Names_Get_Index_File(), 
                   Names_Get_Words_File(), 
                   Names_Get_Ofidx_File(), 
                   Names_Get_Nums_File(), 
                   (Flags_Get_Keyword_Type()!=UNDEFINED_KEYWORD));
  if (rc) {Header_TailPrint(); return -1;}

  Save_Statistics (ROBOT);

  if (advanced_version)
    if (Flags_Get_Is_Repeater())
       Print_Warning();

  //Print_Midi_Console ();
  Flags_Set_Blocks_Number (Files_Get_Blocks_Number());
  Flags_Set_Random_Number (random_number % Flags_Get_Blocks_Number());

  Matrix_Anr_Get_Blocks ();
  Print_AnrBlocks ();
  Files_Close ();

  Print_Config ();
  Reload_Button_Print (advanced_version, 
                       Flags_Get_Repeats_Number(),random_number);
  Print_Last_Links ();
  Adv_Print_Rambler_Image ();
  Adv_Print_Top ();
  if (advanced_version) {
    //Print_Question(Flags_Get_Need_Question(), random_number);
    Adv_Print_RLE_RLE100(random_number);
    //Adv_Print_RLE_RB2 (random_number);
  }

  Header_TailPrint ();
  return 0;
}

