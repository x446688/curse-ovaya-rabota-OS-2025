TESTS = check_web
check_PROGRAMS = check_web
check_web_SOURCES = check_web.c $(top_builddir)/src/helper.c $(top_builddir)/src/web.c
check_web_CFLAGS = $(CHECK_CFLAGS) $(GTK3_CFLAGS) $(SSL_CFLAGS)
check_web_LDADD = $(CHECK_LIBS) $(GTK3_LIBS) $(SSL_LIBS)
