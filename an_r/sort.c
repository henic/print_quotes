/**********************************************************************/
/*                             Sort.c                                 */
/**********************************************************************/


#include <stdio.h>
#include "an_prot.h"

//#define TEST_SORT_FUNCTION 1


/**********************************************************************/
void Sort_And_Exclude (unsigned long *buf,
                       unsigned int  *kwd,
                       unsigned int  *pLen) {
  long ltmp; int ntmp;
  int i, j, k;
  int len;

  len = *pLen;
  for (i=0;   i<len-1; i++) {
    //printf ("%d: ", i);
    //for (k=0; k<len; k++)
    //   printf ("%d ", buf[k]);
    //printf("\n");
    for (j=i+1; j<len; j++)
      if (buf[i]==buf[j] && kwd[i]==kwd[j]) { // delete one of them
      for (k=j;k<len-1; k++) {
        buf[k] = buf[k+1];
        kwd[k] = kwd[k+1];
      }
      len --;
      j--;
    }
    else { // different pairs
    if (buf[i]>buf[j] || (buf[i]==buf[j] && kwd[i]>kwd[j])) {
       // exchange items
       ltmp   = buf[i];
       buf[i] = buf[j];
       buf[j] = ltmp;
       ntmp   = kwd[i];
       kwd[i] = kwd[j];
       kwd[j] = ntmp;
    }
      }
  }
  *pLen = len;
}


/**********************************************************************/
/* Remove_Doubles - delete doubles according to "and/or" parameter    */
/**********************************************************************/
void Sort_Remove_Doubles (unsigned long *buf,
                          unsigned int  len,
                          unsigned int  *pLen,
                          unsigned long *result,
                          int           and_flag) {
   int i, j, k;
   int keywords_number;

   //len = *pLen;
   if (and_flag) {
      Save_Msg_Finished();
      keywords_number = 2/*Keywords_Get_Size ()*/;
      i=1;
      j=0;
      k=1;
      while (i<len) {
         if (buf[i]!=buf[i-1]) {
           if (k>=keywords_number)
              result[j++] = buf[i-1];
           k=1;
         }
         else k++;
         i++;
      }
      if (k>=keywords_number)
         result[j++] = buf[i-1];
   }
   else { // "OR" - means just delete doubles
      i=0;
      j=1;
      result[0]=buf[i];
      do {
         i++;
         if (i==len) break;
         if (buf[i]!=buf[i-1])
           result[j++]=buf[i];
      } while (i<len);
   }
   *pLen = j;
}

#ifdef TEST_SORT_FUNCTION
int main (void) {

int i;
unsigned long arr[50] = {1,2,3,3,4,3,4,5,4,3,2,3,4,5,6,4,3,3,7,8,9,0,7,4,4,3,1,0,4,3,2,4,3,2,3,4,5,9,4};
unsigned int  kwd[50] = {4,3,5,6,4,3,4,5,7,8,3,2,1,3,3,4,2,2,2,3,4,6,7,0,9,8,7,5,4,4,3,4,5,6,7,8,2,2,2};
unsigned long res[50];
unsigned int  len = 39;
unsigned int  len_res;

Sort_And_Exclude (arr, kwd, &len);
printf ("Results: ");
for (i=0; i<len; i++)
  printf ("%d ", arr[i]);
  printf("\n");
printf ("Keywrds: ");
for (i=0; i<len; i++)
  printf ("%d ", kwd[i]);
  printf("\n");

Sort_Remove_Doubles (arr, len, &len_res, res, 0);
printf ("OR_Flag: ");
for (i=0; i<len_res; i++)
  printf ("%d ", res[i]);
  printf("\n");

Sort_Remove_Doubles (arr, len, &len_res, res, 1);
printf ("AndFlag: ");
for (i=0; i<len_res; i++)
  printf ("%d ", res[i]);
  printf("\n");

return 0;
}

#endif
