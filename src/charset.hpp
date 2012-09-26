/*

  This file is a part of BoGoEngine project.

  Copyright (C) 2012 Dương H. Nguyễn <cmpitg@gmail.com>
  Copyright (C) 2012 Dương Quang Hà <contact@haqduong.net>

  BoGoEngine is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  BoGoEngine is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with BoGoEngine.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef CHARSET_H
#define CHARSET_H

#include <glibmm/ustring.h>

namespace BoGo {

    using namespace Glib;

    typedef guint CharsetT;
    typedef ustring::size_type _size_t_;

    const guint NUMBER_OF_CHARSETS = 3;
    const CharsetT CHARSET_UTF8 = 0,
        CHARSET_TCVN3 = 1,
        CHARSET_VNI = 2;

    const ustring UTF8_CHARS =
        "ÀÁẢÃẠẰẮẲẴẶĂẦẤẨẪẬÂ"
        "ÈÉẺẼẸỀẾỂỄỆÊÌÍỈĨỊ"
        "ÒÓỎÕỌỒỐỔỖỘÔỜỚỞỠỢƠ"
        "ÙÚỦŨỤỪỨỬỮỰƯ"
        "ỲÝỶỸỴ"
        "Đ"
        "àáảãạằắẳẵặăầấẩẫậâ"
        "èéẻẽẹềếểễệêìíỉĩị"
        "òóỏõọồốổỗộôờớởỡợơ"
        "ùúủũụừứửữựư"
        "ỳýỷỹỵ"
        "đ";

    const unsigned int utf8ToTCVN3[] = {
        0XB5, 0XB8, 0XB6, 0XB7, 0XB9, 0XBB, 0XBE, 0XBC, 0XBD, 0XC6, 0XA1, 0XC7,
        0XCA, 0XC8, 0XC9, 0XCB, 0XA2, 0XCC, 0XD0, 0XCE, 0XCF, 0XD1, 0XD2, 0XD5,
        0XD3, 0XD4, 0XD6, 0XA3, 0XD7, 0XDD, 0XD8, 0XDC, 0XDE, 0XDF, 0XE3, 0XE1,
        0XE2, 0XE4, 0XE5, 0XE8, 0XE6, 0XE7, 0XE9, 0XA4, 0XEA, 0XED, 0XEB, 0XEC,
        0XEE, 0XA5, 0XEF, 0XF3, 0XF1, 0XF2, 0XF4, 0XF5, 0XF8, 0XF6, 0XF7, 0XF9,
        0XA6, 0XFA, 0XFD, 0XFB, 0XFC, 0XFE, 0XA7, 0XB5, 0XB8, 0XB6, 0XB7, 0XB9,
        0XBB, 0XBE, 0XBC, 0XBD, 0XC6, 0XA8, 0XC7, 0XCA, 0XC8, 0XC9, 0XCB, 0XA9,
        0XCC, 0XD0, 0XCE, 0XCF, 0XD1, 0XD2, 0XD5, 0XD3, 0XD4, 0XD6, 0XAA, 0XD7,
        0XDD, 0XD8, 0XDC, 0XDE, 0XDF, 0XE3, 0XE1, 0XE2, 0XE4, 0XE5, 0XE8, 0XE6,
        0XE7, 0XE9, 0XAB, 0XEA, 0XED, 0XEB, 0XEC, 0XEE, 0XAC, 0XEF, 0XF3, 0XF1,
        0XF2, 0XF4, 0XF5, 0XF8, 0XF6, 0XF7, 0XF9, 0XAD, 0XFA, 0XFD, 0XFB, 0XFC,
        0XFE, 0XAE
    };

    const gchar * utf8ToCharset (ustring src, CharsetT charset);

}

#endif
