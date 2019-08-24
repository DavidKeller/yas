
// Copyright (c) 2010-2019 niXman (i dot nixman dog gmail dot com). All
// rights reserved.
//
// This file is part of YAS(https://github.com/niXman/yas) project.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <yas/serialize.hpp>
#include <yas/std_types.hpp>

#undef NDEBUG
#include <cassert>

/***************************************************************************/

struct type {
    type()
        :i(33)
        ,d(.34)
        ,s("35")
        ,v({36, 37, 38})
    {}

    std::uint32_t i;
    double d;
    std::string s;
    std::vector<int> v;
};

// separated free-functions for save/load

// save
template<typename Ar>
void serialize(Ar &ar, const type &t) {
    ar & YAS_OBJECT_NVP(
        "type"
        ,("i", t.i)
        ,("d", t.d)
        ,("s", t.s)
        ,("v", t.v)
    );
}

// load
template<typename Ar>
void serialize(Ar &ar, type &t) {
    ar & YAS_OBJECT_NVP(
        "type"
        ,("i", t.i)
        ,("d", t.d)
        ,("s", t.s)
        ,("v", t.v)
    );
}

/***************************************************************************/

int main() {
    type t1, t2;
    t2.i = 0;
    t2.d = 0;
    t2.s.clear();
    t2.v.clear();

    constexpr std::size_t flags = yas::mem|yas::json;

    auto buf = yas::save<flags>(t1);

    yas::load<flags>(buf, t2);

    // TODO: stackoverflow.com/questions/17333
    assert(t1.i == t2.i && t1.d == t2.d && t1.s == t2.s && t1.v == t2.v);
}

/***************************************************************************/
