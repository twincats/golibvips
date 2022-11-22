/* GDBus - GLib D-Bus Library
 *
 * Copyright (C) 2008-2010 Red Hat, Inc.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, see <http://www.gnu.org/licenses/>.
 *
 * Author: David Zeuthen <davidz@redhat.com>
 */

#ifndef __G_DBUS_ERROR_H__
#define __G_DBUS_ERROR_H__

#if !defined (__GIO_GIO_H_INSIDE__) && !defined (GIO_COMPILATION)
#error "Only <gio/gio.h> can be included directly."
#endif

#include <gio/giotypes.h>

G_BEGIN_DECLS

/**
 * G_DBUS_ERROR:
 *
 * Error domain for errors generated by a remote message bus. Errors
 * in this domain will be from the #GDBusError enumeration.  See
 * #GError for more information on error domains.
 *
 * Note that this error domain is intended only for
 * returning errors from a remote message bus process. Errors
 * generated locally in-process by e.g. #GDBusConnection should use the
 * %G_IO_ERROR domain.
 *
 * Since: 2.26
 */
#define G_DBUS_ERROR g_dbus_error_quark()

GLIB_AVAILABLE_IN_ALL
GQuark g_dbus_error_quark (void);

/* Used by applications to check, get and strip the D-Bus error name */
GLIB_AVAILABLE_IN_ALL
gboolean g_dbus_error_is_remote_error       (const GError    *error);
GLIB_AVAILABLE_IN_ALL
gchar   *g_dbus_error_get_remote_error      (const GError    *error);
GLIB_AVAILABLE_IN_ALL
gboolean g_dbus_error_strip_remote_error    (GError          *error);

/**
 * GDBusErrorEntry:
 * @error_code: An error code.
 * @dbus_error_name: The D-Bus error name to associate with @error_code.
 *
 * Struct used in g_dbus_error_register_error_domain().
 *
 * Since: 2.26
 */
struct _GDBusErrorEntry
{
  gint         error_code;
  const gchar *dbus_error_name;
};

GLIB_AVAILABLE_IN_ALL
gboolean g_dbus_error_register_error        (GQuark                 error_domain,
                                             gint                   error_code,
                                             const gchar           *dbus_error_name);
GLIB_AVAILABLE_IN_ALL
gboolean g_dbus_error_unregister_error      (GQuark                 error_domain,
                                             gint                   error_code,
                                             const gchar           *dbus_error_name);
GLIB_AVAILABLE_IN_ALL
void     g_dbus_error_register_error_domain (const gchar           *error_domain_quark_name,
                                             volatile gsize        *quark_volatile,
                                             const GDBusErrorEntry *entries,
                                             guint                  num_entries);

/* Only used by object mappings to map back and forth to GError */
GLIB_AVAILABLE_IN_ALL
GError  *g_dbus_error_new_for_dbus_error    (const gchar     *dbus_error_name,
                                             const gchar     *dbus_error_message);
GLIB_AVAILABLE_IN_ALL
void     g_dbus_error_set_dbus_error        (GError         **error,
                                             const gchar     *dbus_error_name,
                                             const gchar     *dbus_error_message,
                                             const gchar     *format,
                                             ...) G_GNUC_PRINTF(4, 5);
GLIB_AVAILABLE_IN_ALL
void     g_dbus_error_set_dbus_error_valist (GError         **error,
                                             const gchar     *dbus_error_name,
                                             const gchar     *dbus_error_message,
                                             const gchar     *format,
                                             va_list          var_args) G_GNUC_PRINTF(4, 0);
GLIB_AVAILABLE_IN_ALL
gchar   *g_dbus_error_encode_gerror         (const GError    *error);

G_END_DECLS

#endif /* __G_DBUS_ERROR_H__ */
