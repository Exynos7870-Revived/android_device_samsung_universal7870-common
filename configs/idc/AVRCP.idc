# Copyright (C) 2015 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#
# AVRCP
#


device.internal = 1

def AddImage(info, dir, basename, dest, printInfo=True):
  data = info.input_zip.read(dir + "/" + basename)
  common.ZipWriteStr(info.output_zip, basename, data)
  if printInfo:
   info.script.Print("Patching {} image unconditionally...".format(dest.split('/')[-1]))
   info.script.AppendExtra('package_extract_file("%s", "%s");' % (basename, dest))

def FullOTA_InstallBegin(info):
  AddImage(info, "RADIO", "super_dummy.img", "/tmp/super_dummy.img", False);
  info.script.AppendExtra('package_extract_file("install/bin/flash_super_dummy.sh", "/tmp/flash_super_dummy.sh");')
  info.script.AppendExtra('set_metadata("/tmp/flash_super_dummy.sh", "uid", 0, "gid", 0, "mode", 0755);')
  info.script.AppendExtra('run_program("/tmp/flash_super_dummy.sh");')
  return