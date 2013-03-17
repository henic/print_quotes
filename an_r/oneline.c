/**********************************************************************/
/*                            Oneline.c                               */
/**********************************************************************/

#include <stdio.h>

#include "an_r.h"
#include "an_prot.h"
#include "flags.h"

/**********************************************************************/
static void Print_1ln (long random_number,
                       long blocks_number) {

    LINE str;
    long offs;
    long random_index;
    long offset_in_idx_file;

    random_index = random_number % blocks_number;
    offset_in_idx_file = random_index << 2;
    Files_Get_Offset_From_Index (offset_in_idx_file, &offs, sizeof(offs));
    Files_Get_Line(offs, str);
    if (! Flags_Get_Language())
       printf ("<b>Бонус:</b>&nbsp &nbsp <i>%s</i><br><hr>\n", str);
    else 
       printf ("<b>Bonus:</b>&nbsp &nbsp <i>%s</i><br><hr>\n", str);
}

/**********************************************************************/
void OneLine (void) {
#ifndef TEST_VERSION
  long oneline_number;
  int rc;
  if (Flags_Get_Advanced_Version()) {
    rc = Files_Open(ONELINE_FILE, ONELINE_IDX, "", "", "", 0);
    if (!rc) {
       oneline_number = Files_Get_Blocks_Number ();
       Print_1ln (Flags_Get_Random_Number(), oneline_number);
       Files_Close();
    }
  }
#endif
}

