/*****************************************************************************/
/*       Print blocks which contain given keywords from the database         */
/*****************************************************************************/
/*                                                                           */
/*  Copyright (C) Victor Bolotnikov, Tigers Ltd, 1997-2000      			 */
/*                                                                           */
/*  Comments & suggestions to tiger@kulichki.com                             */
/*                                                                           */
/*  Algorithm (a bit simplified):                                            */
/*    for all blocks in the file                                             */
/*      for all keywords                                                     */
/*        if keyword is found in the block                                   */
/*           print block                                                     */
/*                                                                           */
/*                                                                           */
/*  Last edition: 26-Apr-00                                                  */
/*                                                                           */
/*  Known bugs: None and can not be.                                         */
/*                                                                           */
/*****************************************************************************/

/*
 *              Copyright Statement, Tigers Ltd, 1993-99
 *	
 * This software contains proprietary and trade secret information
 * of Tigers Ltd and is protected by Federal Copyright law.
 * This software can not be copied or distributed in any form, including
 * electronic, magnetic, paper and verbal medium, or disclosed
 * to any third party or any person. It can be distributed or used only
 * as mentioned in the license agreement signed Tigers Ltd.
 */

#include "an_r.h"
#include "an_prot.h"
#include "names.h"
#include "flags.h"

/***************************************************************************/
int main (void) {

  Header_SearchPrint ();
  Tolower_Init_Ascii_Table ();
  Adv_Print_Advert ();

  Params_Get ();
  Names_Set_Files ();

  Save_Statistics(SEARCH);  

  if (! Keywords_Get_Size())
     Error ("No keys given", 0);
 
  Keywords_Print ();

  if (Files_Open(
       Names_Get_Text_File(), 
       Names_Get_Index_File(), 
       Names_Get_Words_File(), 
       Names_Get_Ofidx_File(), 
       Names_Get_Nums_File(), 
       1)) {
     Files_Close ();
     return -1;
  }

  Flags_Set_Blocks_Number (Files_Get_Blocks_Number());
  Matrix_Ans_Get_Blocks ();
  Print_AnsBlocks ();

  Files_Close();
  Header_TailPrint ();
  return 0;
}

