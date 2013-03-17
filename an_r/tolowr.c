/***********************************************************************/
/*                            Tolowr.c                                 */
/***********************************************************************/

#include "an_r.h"
#include "an_prot.h"


const RUS_LETTERS_TABLE  rus_letters = {
    'á', 'â', '÷', 'ç', 'ä', 'å', '³', 'ö', 'ú', 'é',
    'ê', 'ë', 'ì', 'í', 'î', 'ï', 'ð', 'ò', 'ó', 'ô',
    'õ', 'æ', 'è', 'ã', 'þ', 'û', 'ý', 'ø', 'ù', 'ÿ',
    'ü', 'à', 'ñ', 'Á', 'Â', '×', 'Ç', 'Ä', 'Å', 'Å',
    'Ö', 'Ú', 'É', 'Ê', 'Ë', 'Ì', 'Í', 'Î', 'Ï', 'Ð',
    'Ò', 'Ó', 'Ô', 'Õ', 'Æ', 'È', 'Ã', 'Þ', 'Û', 'Ý',
    'Ø', 'Ù', 'ß', 'Ü', 'À', 'Ñ',
};

const ENG_LETTERS_TABLE eng_letters = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z',
};

ASCII_TABLE ascii_table;

/***************************************************************************/
static char Koi8_Char_Tolower (char ch) {
    unsigned short index = (unsigned char) ch;
    if (index>=LEN_ASCII_TABLE)
        Error("Koi8_Char_Tolower: invalid char idx", 1);
    return ascii_table[index];
}

/***********************************************************************/
void Tolower_Init_Ascii_Table (void) {
  int i;
  for (i=0; i<256; i++)
    ascii_table[i] = (char) i;

  for (i=0; i<HALF_ENG_ALEPHBET; i++) {
    ascii_table[(unsigned char)eng_letters[i]] = 
           eng_letters[i+HALF_ENG_ALEPHBET];
  }
  for (i=0; i<HALF_RUS_ALEPHBET; i++) {
    ascii_table[(unsigned char)rus_letters[i]] = 
           rus_letters[i+HALF_RUS_ALEPHBET];
  }
}

/***************************************************************************/
void Tolower_String (char *src, char *dst) {
    short i;
    char tmp;
    src[MAX_LEN_LINE-1]='\0'; // well, to be sure
    for (i=0; src[i]; i++) {
       tmp = Koi8_Char_Tolower (src[i]);
       dst [i] = tmp;
    }
    dst [i] = '\0';
}


