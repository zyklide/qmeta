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
// This file implements the details of all classes related to Exif data.

#include "exif_data.h"

#include <QtCore>

namespace qmeta {

ExifData::ExifData(QByteArray byte_array, QObject *parent) : QObject(parent) {
  set_byte_array(byte_array);
}

QByteArray ExifData::ToHex() {
  return byte_array().toHex();
}

QString ExifData::ToString() {
  return QString(byte_array());
}

}  // namespace qmeta
