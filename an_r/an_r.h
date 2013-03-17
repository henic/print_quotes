/************************************************************************/
/*                                  An_r.h                              */
/************************************************************************/
#ifndef _AN_R_H_
#define _AN_R_H_

#include <stdio.h>

#define VERSION                 "6.0"

/***********************************************************************/
/*    undefine it for full version (annuls advertisement, 1ln etc)     */
/***********************************************************************/
//#define  TEST_VERSION           1


/***********************************************************************/
/*             define it for the version contains searching)           */
/***********************************************************************/
#define  ROBOT                  0
#define  SEARCH                 1

/***********************************************************************/
/*                      FILE I/O constants                             */
/***********************************************************************/
#define  SEEK_SET               0
#define  SEEK_CUR               1
#define  SEEK_END               2

/***********************************************************************/
#define  TITLE                  "Random-chosen russian anecdotes"
#define  HEADER_R               "Полосатые анекдоты"
#define  HEADER_E               "Passed Jokes"

#define  TEXT_FILE_R            "../an_src/anecdotr.txt"
#define  INDEX_FILE_R	        "../an_src/anecdotr.idx"
#define  LOG_FILE               "../an_src/anecdots.log"
#define  QUEST_FILE_R	        "../an_src/questior.txt"
#define  NUMS_FILE_R            "../an_src/anecdotr.num"
#define  OFIDX_FILE_R           "../an_src/anecdotr.ofd"
#define  WORDS_FILE_R           "../an_src/anecdotr.wrd"

#define  TEXT_FILE_E            "../an_src/anecdote.txt"
#define  INDEX_FILE_E	        "../an_src/anecdote.idx"
#define  QUEST_FILE_E	        "../an_src/questioe.txt"
#define  NUMS_FILE_E            "../an_src/anecdote.num"
#define  OFIDX_FILE_E           "../an_src/anecdote.ofd"
#define  WORDS_FILE_E           "../an_src/anecdote.wrd"

/************************************************************************/
#define THEME_NAME_PREFIX       "../indexes/idx"
#define  ONELINE_FILE           "../1ln.txt"
#define  ONELINE_IDX            "../1ln.idx"
#define  PROGRAM_PATH_R         "/cgi-bin/cgiwrap/tiger/an_r.cgi"
#define  PROGRAM_PATH_E         "/cgi-bin/cgiwrap/tiger/an_e.cgi"
#define  SEARCH_PATH            "/cgi-bin/cgiwrap/tiger/an_s.cgi"
#define  POSES_PATH             "/cgi-bin/cgiwrap/tiger/poses.cgi"
#define  TIGER_EMAIL            "tiger@kulichki.com"
#define  PATH_TO_SEND           "/cgi-bin/cgiwrap/tiger/"
#define  QUICK_HTM              "/quick.htm"
#define  GUESTBOOK_HTM          "/guestbook/guestbook.html"
#define  THANKS_HTM             "/an_r/thanks.htm"
#define  ARTICLE_HTM            "/an_r/art_srch.htm"
#define  PAGEINFO_HTM           "/an_r/pageinfo.htm"
#define  FILEINFO_HTM           "/an_r/fileinfo.htm"
#define  SEARCHINFO_HTM         "/an_r/searchinfo.htm"
#define  VBSPLIT_HTM            "/vbsplit/vbsplit.htm"
#define  SUBSCRIPTION_EMAIL     "boloto-subscribe@egroups.com"
#define  FORMMAIL_PATH          "/cgi-bin/cgiwrap/tiger/formmail.pl"
#define  VOTING_PATH            "/cgi-bin/cgiwrap/tiger/voting.cgi"
#define  USAGE                  "Usage: an.cgi [h][a=answer][b=black][c=OR][e=lang][k=kwd_type][i=ignore]<br>[s=start][p=keywords][t=theme][n=repeats][v=version][r=random][w=MD][y=Bonus][z=auto]<br>"
#define  RAMBLER_CODE           844

/************************************************************************/
#define  MUSIC_FREQUENCY        200
#define  MAX_REPEATS            10
#define  MAX_COLOR              15
#define  MAX_DELTA_RECORDS      200
#define  AVG_RECORD_SIZE        30
#define  MAX_QUESTION           150   

#define  ANSWER_YES		"Да"
#define  ANSWER_NO		"Нет"

#define  RUSSIAN                0
#define  ENGLISH                1

#define  MAX_LEN_LINE           200
#define  MAX_PARAM_LINE_LEN     1024
#define  MAX_BLOCK_LEN          250
#define  LEN_ASCII_TABLE        256

/************************************************************************/
/*  required for tolower recoding                                       */
/************************************************************************/
#define  RUS_LETTERS_NUMBER     66
#define  HALF_RUS_ALEPHBET      33
#define  ENG_LETTERS_NUMBER     52
#define  HALF_ENG_ALEPHBET      26

/************************************************************************/
/*                              typedefs                                */
/************************************************************************/
typedef  char           LINE              [MAX_LEN_LINE];
typedef  char           PARAM_LINE        [MAX_PARAM_LINE_LEN];
typedef  char           RUS_LETTERS_TABLE [RUS_LETTERS_NUMBER];
typedef  char           ENG_LETTERS_TABLE [ENG_LETTERS_NUMBER];
typedef  char           ASCII_TABLE       [LEN_ASCII_TABLE];

#endif

