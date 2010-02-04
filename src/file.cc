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
// QMeta - a library to manipulate image metadata based on Qt.
//
// This file implements the detail of the File class.

#include "file.h"

#include <QtCore>

#include "exif.h"

namespace qmeta {

// Constructs the File object.
File::File(QObject *parent) : QObject(parent) {
  set_exif(NULL);
  set_file(NULL);
}

// Opens a new file object to represent the file with the given file_path
// and stores it as a data member. Returns true if successful.
bool File::Open(const QString &file_path) {
  QFile *file = new QFile(file_path, this);
  if (!file->open(QIODevice::ReadOnly)) {
    return false;
  } else {
    set_file(file);
    return IsValid();
  }
}

// Returns the thumbnail from supported metadata. Currently Exif is the only
// supported metadata.
QByteArray File::Thumbnail() {
  QByteArray thumbnail;
  if (exif())
    thumbnail = exif()->Thumbnail();
  return thumbnail;
}

}  // namespace qmeta
