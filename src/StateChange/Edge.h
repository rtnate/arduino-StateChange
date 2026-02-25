//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//!  @file Edge.h 
//!  @brief Edge class header
//!
//!  @author Nate Taylor 

//!  Contact: nate@rtelectronix.com
//!  @copyright (C) 2026  Nate Taylor - All Rights Reserved.
//
//    |-----------------------------------------------------------------------|
//    |                                                                       |
//    |         MMMMMMMMMMMMMMMMMMMMMM   NNNNNNNNNNNNNNNNNN                   |
//    |         MMMMMMMMMMMMMMMMMMMMMM   NNNNNNNNNNNNNNNNNN                   |
//    |        MMMMMMMMM    MMMMMMMMMM       NNNNNMNNN                        |
//    |        MMMMMMMM:    MMMMMMMMMM       NNNNNNNN                         |
//    |       MMMMMMMMMMMMMMMMMMMMMMM       NNNNNNNNN                         |
//    |      MMMMMMMMMMMMMMMMMMMMMM         NNNNNNNN                          |
//    |      MMMMMMMM     MMMMMMM          NNNNNNNN                           |
//    |     MMMMMMMMM    MMMMMMMM         NNNNNNNNN                           |
//    |     MMMMMMMM     MMMMMMM          NNNNNNNN                            |
//    |    MMMMMMMM     MMMMMMM          NNNNNNNNN                            |
//    |                MMMMMMMM        NNNNNNNNNN                             |
//    |               MMMMMMMMM       NNNNNNNNNNN                             |
//    |               MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM         |
//    |             MMMMMMM      E L E C T R O N I X         MMMMMM           |
//    |              MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM             |
//    |                                                                       |
//    |-----------------------------------------------------------------------|
//
//    |------------------------------------------------------------------------|
//    |                                                                        |
//    |    [MIT License]                                                       |
//    |                                                                        |
//    |    Copyright (c) 2026 Nate Taylor                                      |
//    |                                                                        |
//    |    Permission is hereby granted, free of charge, to any person         |
//    |    obtaining a copy of this software and associated documentation      |
//    |    files (the "Software"), to deal in the Software without             |
//    |    restriction, including without limitation the rights to use,        |
//    |    copy, modify, merge, publish, distribute, sublicense, and/or sell   |
//    |    copies of the Software, and to permit persons to whom the Software  |
//    |    is furnished to do so, subject to the following conditions:         |
//    |                                                                        |
//    |    The above copyright notice and this permission notice shall be      |
//    |    included in all copies or substantial portions of the Software.     |
//    |                                                                        |
//    |    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,     |
//    |    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES     |
//    |    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND            |
//    |    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS |
//    |    BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN     |
//    |    AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF      |
//    |    OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS     |
//    |    IN THE SOFTWARE.                                                    |
//    |                                                                        |
//    |------------------------------------------------------------------------|
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef STATE_CHANGE_EDGE_H_
#define STATE_CHANGE_EDGE_H_

#include <stdint.h>

class Edge
{
public:
    //Prefer standard enum here so Edge::None, Edge::Rising, and Edge::Falling are 
    //available constants
    enum Type : uint8_t
    {
        None    = 0x0,
        Rising  = 0x1,
        Falling = 0x2
    };

    // Default = no edge
    constexpr Edge() : bits_(0) {}

    // Construct from last/current state
    constexpr Edge(bool last, bool current)
        : bits_((static_cast<uint8_t>(last) << 1)
            | static_cast<uint8_t>(current))
    {}

    // Factory from raw 2-bit encoding
    static constexpr Edge fromRaw(uint8_t raw)
    {
        return Edge(raw & 0x3);
    }

    //Your right about enum as source of truth is icky
    //lets use raw values - encoding meaning is better cpu code 
    //but for avr-gcc i don't want bloat
    //these functions can be the source of truth
    constexpr bool rising() const  { return bits_ == 0x1; }
    constexpr bool falling() const { return bits_ == 0x2; }
    constexpr bool last() const { return (bits_ >> 1) & 0x1; }
    constexpr bool current() const { return bits_ & 0x1; }
    constexpr bool state() const { return current(); }
    constexpr bool changed() const
    {
        return (bits_ ^ (bits_ >> 1)) & 0x01;
    }

    //This is one less branch in c++ 
    //avr should do shift, XOR, AND, SBRC, RET bits_, RET 0x0 similar
    //arm should do shift, XOR, AND, CBZ + 1, RET bits_, RET 0x0 or similar
    constexpr Type type() const
    {
        return changed() ? static_cast<Type>(bits_) : Type::None;
    }

    explicit constexpr operator bool() const
    {
        return changed();
    }

    constexpr uint8_t raw() const
    {
        return bits_;
    }
protected:
    explicit constexpr Edge(uint8_t rawBits)
        : bits_(rawBits & 0x3)
    {}

private:
    uint8_t bits_; // bit1 = last, bit0 = current
};


#endif /* STATE_CHANGE_EDGE_H_ */
