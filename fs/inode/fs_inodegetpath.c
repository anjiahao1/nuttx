/****************************************************************************
 * fs/inode/fs_inodegetpath.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <errno.h>
#include <string.h>
#include <nuttx/fs/fs.h>

#include "inode/inode.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: inode_getpath
 *
 * Description:
 *   Given the full path from inode.
 *
 ****************************************************************************/

int inode_getpath(FAR struct inode *inode, FAR char *path, size_t len)
{
  if (path == NULL)
    {
      return -EINVAL;
    }
  else if (inode == NULL)
    {
      path[0] = '\0';
      return OK;
    }
  else
    {
      int ret = inode_getpath(inode->i_parent, path, len);
      if (ret < 0)
        {
          return ret;
        }
    }

  strlcat(path, inode->i_name, len);
  if (inode->i_child || INODE_IS_MOUNTPT(inode))
    {
      strlcat(path, "/", len);
    }

  return OK;
}
