/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <AK/StringView.h>

namespace GUI {

#define FOR_EACH_TOKEN_TYPE \
    __TOKEN(Unknown)        \
    __TOKEN(Comment)        \
    __TOKEN(ClassMarker)    \
    __TOKEN(ClassName)      \
    __TOKEN(LeftCurly)      \
    __TOKEN(RightCurly)     \
    __TOKEN(Identifier)     \
    __TOKEN(Colon)          \
    __TOKEN(JsonValue)

struct GMLPosition {
    size_t line;
    size_t column;
};

struct GMLToken {
    enum class Type {
#define __TOKEN(x) x,
        FOR_EACH_TOKEN_TYPE
#undef __TOKEN
    };

    const char* to_string() const
    {
        switch (m_type) {
#define __TOKEN(x) \
    case Type::x:  \
        return #x;
            FOR_EACH_TOKEN_TYPE
#undef __TOKEN
        }
        ASSERT_NOT_REACHED();
    }

    Type m_type { Type::Unknown };
    StringView m_view;
    GMLPosition m_start;
    GMLPosition m_end;
};

class GMLLexer {
public:
    GMLLexer(const StringView&);

    Vector<GMLToken> lex();

private:
    char peek(size_t offset = 0) const;
    char consume();

    StringView m_input;
    size_t m_index { 0 };
    GMLPosition m_previous_position { 0, 0 };
    GMLPosition m_position { 0, 0 };
};

}
