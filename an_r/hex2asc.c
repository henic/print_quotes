/***************************************************************************/
/*                                hex2asc.c                                */
/***************************************************************************/

#include "an_r.h"
#include "an_prot.h"

/***************************************************************************/
void Hex2Ascii (char *src, char *dst) {
  LINE msg;
  short src_cnt=0, dst_cnt=0;
  char hex_str[4];
  char temp_char;

  while (src[src_cnt]) {
    switch (src[src_cnt]) {
      case '\045':     //%
        src_cnt++;
        hex_str[0] = src[src_cnt];
        if (!hex_str[0]) {
           sprintf (msg, "ASCII2Hex: Invalid params string '%s'", src);
           Error (msg, 1);
        }

        src_cnt++;
        hex_str[1] = src[src_cnt];
        if (!hex_str[1]) {
           sprintf (msg, "ASCII2Hex: Invalid params string '%s'", src);
           Error (msg, 1);
        }

        hex_str[2] = '\0';
        if (sscanf (hex_str, "%x", &temp_char)!=1) {
           sprintf (msg, "ASCII2Hex: Invalid hex string '%s'", hex_str);
           Error (msg, 1);
        }

        dst[dst_cnt] = temp_char;
        break;

      case '+':
        dst[dst_cnt]=' ';
        break;

      default:
        dst[dst_cnt] = src[src_cnt];
    }
    src_cnt++;
    dst_cnt++;
  }
  dst[dst_cnt]='\0';
}


