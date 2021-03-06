/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*-
 *
 * Copyright (C) 2015 Colin Walters <walters@verbum.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "config.h"

#include "otutil.h"
#include "libgsystem.h"
#include "ot-tool-util.h"

gboolean
ot_parse_boolean (const char  *value,
                  gboolean    *out_parsed,
                  GError     **error)
{
#define ARG_EQ(x, y) (g_ascii_strcasecmp(x, y) == 0)
  if (ARG_EQ(value, "1")
      || ARG_EQ(value, "true")
      || ARG_EQ(value, "yes"))
    *out_parsed = TRUE;
  else if (ARG_EQ(value, "0")
           || ARG_EQ(value, "false")
           || ARG_EQ(value, "no")
           || ARG_EQ(value, "none"))
    *out_parsed = FALSE;
  else
    {
      g_set_error (error, G_IO_ERROR, G_IO_ERROR_FAILED,
                   "Invalid boolean argument '%s'", value);
      return FALSE;
    }

  return TRUE;
}

gboolean
ot_parse_keyvalue (const char  *keyvalue,
                   char       **out_key,
                   char       **out_value,
                   GError     **error)
{
  const char *eq = strchr (keyvalue, '=');
  if (!eq)
    {
      g_set_error (error, G_IO_ERROR, G_IO_ERROR_FAILED,
                   "Missing '=' in KEY=VALUE for --set");
      return FALSE;
    }
  *out_key = g_strndup (keyvalue, eq - keyvalue);
  *out_value = g_strdup (eq + 1);
  return TRUE;
}
