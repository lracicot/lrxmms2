dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(lrxmms2, 0.1)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

AC_PROG_CC




dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
IT_PROG_INTLTOOL([0.35.0])

GETTEXT_PACKAGE=lrxmms2
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])

AM_GLIB_GNU_GETTEXT



LT_INIT






PKG_CHECK_MODULES(GTK2,gtk+-2.0
glib-2.0)

PKG_CHECK_MODULES(XMMS2,xmms2-client-glib
xmms2-client)

AC_OUTPUT([
Makefile
src/Makefile
po/Makefile.in
src/entities/Makefile
])
