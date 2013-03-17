/**********************************************************************/
/*                             stat.c                                 */
/**********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "an_r.h"
#include "an_prot.h"

/**********************************************************************/
static FILE *f_stat;

static LINE remote_addr="Undefined remote address";

/**********************************************************************/
static void Get_Time (char *result) {
  time_t timet;
  struct tm*   timetm;
  timet = time(NULL);
  timetm = gmtime(&timet);
  sprintf (result, "%d.%d-%d.%d.%d",
            timetm->tm_mon+1, timetm->tm_mday, timetm->tm_hour,
            timetm->tm_min,   timetm->tm_sec);
}

/**********************************************************************/
void Save_Msg_Finished (void) {
  f_stat = fopen (LOG_FILE, "a");
  if (f_stat==NULL)
  Error ("Cannot open logfile", 1);
  fprintf (f_stat, "Succeeded");
  fclose (f_stat);
}

/**********************************************************************/
void Save_Statistics (int search) {
#ifndef TEST_VERSION
  char time_str[80];
  char *pRemoteAddr = getenv ("REMOTE_ADDR");
  if (pRemoteAddr !=NULL)
      strcpy (remote_addr, pRemoteAddr);
  else remote_addr[0]='\0';

  f_stat = fopen (LOG_FILE, "a");
  if (f_stat==NULL) {
      Error("Cant open log file", 1);
  }

  Get_Time (time_str);
  fprintf (f_stat, "%c %s %s %s\n", 
           (search==SEARCH) ? 's' : 'a', 
           time_str, 
           remote_addr, 
           Get_Args_Str());
  fclose  (f_stat);
#endif
}


/**********************************************************************/
void Get_Statistics (void) {

#ifndef TEST_VERSION  
  unsigned long  file_length;
  unsigned long  reqd_offset;
  unsigned short hits_counter = 0;
  LINE env_line;

  f_stat = fopen (LOG_FILE, "r");
  if (f_stat==NULL) {
    /*printf ("LOGFILE not found\n");*/
    return;
  }

  file_length = Filesize(f_stat);
  reqd_offset = (file_length<AVG_RECORD_SIZE*MAX_DELTA_RECORDS) ?
                   0L : file_length - AVG_RECORD_SIZE*MAX_DELTA_RECORDS;
  if (fseek(f_stat, reqd_offset, SEEK_SET)) {
     Error ("Get_Statistics: fseek failed", 1);
     return;
  }

  fgets (env_line, MAX_LEN_LINE, f_stat); /* dummy reading */

  while (fgets (env_line, MAX_LEN_LINE, f_stat) != NULL) {
    if (strstr (env_line, remote_addr) != NULL)
         hits_counter++;
  }
  //if (hits_counter>2)
  //   is_repeater = 1;

  fclose (f_stat);
#endif
}


