TESTS = check_web
check_PROGRAMS = check_web
check_web_SOURCES = check_web.c $(top_srcdir)/src/web.c
check_web_CFLAGS = $(CHECK_CFLAGS) $(SSL_CFLAGS) -I$(top_srcdir)/src
check_web_LDADD = $(CHECK_LIBS) $(SSL_LIBS)
