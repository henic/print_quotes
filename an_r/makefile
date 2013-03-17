###
###   an_r.cgi  Makefile
###

PREFIX=/usr/local
BINDIR=$(PREFIX)/bin
SECTION=2
CC=gcc

INCLUDES= \
	an_r.h \
	an_s.h \
	an_prot.h \
	flags.h

AN_OBJS = \
	advert.o \
	block.o \
	checkkwd.o \
	colors.o \
	error.o \
	files.o \
	flags.o \
	header.o \
	hex2asc.o \
	keywords.o \
	matrix.o \
	names.o \
	oneline.o \
	params.o \
	print.o \
	question.o \
	reload.o \
	serv.o \
	search.o \
	sort.o \
	stat.o \
	tolowr.o

AN_S_OBJS = \
	advert.o \
	an_s.o \
	block.o \
	checkkwd.o \
	colors.o \
	error.o \
	files.o \
	flags.o \
	header.o \
	hex2asc.o \
	keywords.o \
	matrix.o \
	names.o \
	params.o \
	print.o \
	serv.o \
	sort.o \
	stat.o \
	tolowr.o

SENDANEK_OBJS = \
	files.o \
	flags.o \
	hex2asc.o \
	error.o \
	names.o \
	sendanek.o \
	serv.o

SEND_MSG_OBJS = \
	files.o \
	flags.o \
	hex2asc.o \
	error.o \
	names.o \
        send_msg.o \
        serv.o

all:	an_r.cgi	an_e.cgi	an_s.cgi sendanek.cgi send_msg.cgi

an_r.cgi:	$(AN_OBJS) an_r.o $(INCLUDES)
	$(CC) -o an_r.cgi $(AN_OBJS) an_r.o
	strip an_r.cgi
#	mv an_r.cgi /home/httpd/cgi-bin/cgiwrap/tiger/.
#	mv an_r.cgi ~tiger/public_html/cgi-bin

an_e.cgi:	$(AN_OBJS) an_e.o $(INCLUDES)
	$(CC) -o an_e.cgi $(AN_OBJS) an_e.o
	strip an_e.cgi
#	mv an_e.cgi /home/httpd/cgi-bin/cgiwrap/tiger/.
#	mv an_e.cgi ~tiger/public_html/cgi-bin

an_s.cgi:	$(AN_S_OBJS) $(INCLUDES)
	$(CC) -o an_s.cgi $(AN_S_OBJS)
	strip an_s.cgi
#	mv an_s.cgi /home/httpd/cgi-bin/cgiwrap/tiger/.
#	mv an_s.cgi ~tiger/public_html/cgi-bin

sendanek.cgi:	$(SENDANEK_OBJS) $(INCLUDES)
	$(CC) -o sendanek.cgi $(SENDANEK_OBJS)

send_msg.cgi:   $(SEND_MSG_OBJS) $(INCLUDES)
	$(CC) -o send_msg.cgi $(SEND_MSG_OBJS)

an_r.o:	an_r.c $(INCLUDES)
	$(CC) -c $(CFLAGS) an_r.c

an_e.o:	an_r.c $(INCLUDES)
	$(CC) -DENG -o an_e.o -c $(CFLAGS) an_r.c

.c.o:	$(INCLUDES)
	$(CC) -c $(CFLAGS) $*.c
