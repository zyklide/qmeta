// Copyright 2010, Ollix
// All rights reserved.
//
// This file is part of QMeta.
//
// QMeta is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or any later version.
//
// QMeta is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License
// along with QMeta. If not, see <http://www.gnu.org/licenses/>.

// ---
// Author: olliwang@ollix.com (Olli Wang)
//
// QMeta - a library to manipulate file_types metadata based on Qt.
//
// This file implements the detail of the Jpeg class.

#include "jpeg.h"

#include <QtCore>
#include <qitty/byte_array.h>

#include "exif.h"

namespace qmeta {

Jpeg::Jpeg(QObject *parent) : FileType(parent) {}

// Reimplements the FileType::CreateExifObject() function.
bool Jpeg::CreateExifObject() {
  // Jumps to the beginning of the APP1 marker.
  file()->seek(2);
  // Checks the APP1 marker.
  if (file()->read(2).toHex() != "ffe1")
    return false;
  // Retrieves the APP1 length. The length doesn't include the APP1 marker.
  int app1_length = qitty_utils::ToInt(file()->read(2));
  if (app1_length == -1)
    return false;
  // Checks the Exif Identifier Code.
  if (file()->read(6).toHex() != "457869660000")
    return false;

  // Creates the Exif object.
  Exif *exif = new Exif(this);
  set_exif(exif);
  return true;
}

// Opens a JPEG file with the specified file_path. Returns true if the specified
// file_path is a valid JPEG file and initialization is completed.
bool Jpeg::Open(const QString &file_path) {
  if (!FileType::Open(file_path))
    return false;

  // Checks the first 2 bytes if equals to the SOI marker.
  file()->seek(0);
  if (file()->read(2).toHex() != "ffd8")
    return false;

  return true;
}

}  // namespace qmeta