#!/bin/env python3
#
# Copyright (C) 2021-2022 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

import common
import re

def FullOTA_InstallEnd(info):
  OTA_InstallEnd(info)
  return

def IncrementalOTA_InstallEnd(info):
  OTA_InstallEnd(info)
  return

def AddImage(info, dir, basename, dest):
  data = info.input_zip.read(dir + "/" + basename)
  common.ZipWriteStr(info.output_zip, basename, data)
  info.script.Print("Patching {} image unconditionally...".format(dest.split('/')[-1]))
  info.script.AppendExtra('package_extract_file("%s", "%s");' % (basename, dest))

def OTA_InstallEnd(info):
  AddImage(info, "RADIO", "boot_ramdisk.img", "/dev/block/by-name/ramdisk")
  AddImage(info, "RADIO", "recovery_vendor.img", "/dev/block/by-name/recovery_vendor")
  return
