AC_CONFIG_AUX_DIR([build-aux])
AC_INIT([c2rn], [1.0], [aleksei.x446688@mail.ru])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign])
AC_CONFIG_SRCDIR([src/gui.c])
AC_PROG_CC
PKG_CHECK_MODULES([GTK3], [gtk+-3.0])
PKG_CHECK_MODULES([SSL], [openssl])
PKG_CHECK_MODULES([CHECK], [check >= 0.9.10])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
 tests/Makefile
])
AC_OUTPUT
