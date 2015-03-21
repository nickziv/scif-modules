SO=		libmtcq.so.1
CC=		gcc
CFLAGS_DEBUG=	-m64 -fPIC -W -Wall -Wextra -g
CFLAGS_NDEBUG=	-m64 -fPIC -W -Wall -Wextra
CFLAGS=		$(CFLAGS_NDEBUG)
LIBS=		-lpthread -lc
# On Illumos, DTrace won't work correctly if -h isn't set
LDFLAGS_ILLUM=	-shared -h $(SO)
LDFLAGS_LINUX=	-shared
LDFLAGS=	$(LDFLAGS_LINUX)

fuckit:
	echo $(CFLAGS)

C_SRCS=		gemtc_api.c\
		master_proc.c\
		mtc_queue.c

C_HDRS=		gemtc_api.h\
		master_proc.h\
		mtc_queue.h

C_OBJECTS:=	$(C_SRCS:%.c=%.o)


$(C_SRCS): %.c:

$(C_OBJECTS): %.o: %.c $(C_HDRS)
	$(CC) $(CFLAGS) -o $@ -c $<

objs: $(C_OBJECTS)

$(SO): $(C_OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(SO) $(C_OBJECTS) $(LIBS)

lib: $(SO)

clean:
	rm $(C_OBJECTS) $(SO)
