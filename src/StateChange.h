//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//!  @file StateChange.h 
//!  @brief StateChange Micro Library Header
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

#ifndef STATE_CHANGE_LIB_H_
#define STATE_CHANGE_LIB_H_

/*
===============================================================================
StateChange Micro Library
-------------------------------------------------------------------------------

Contains:

- Edge           : 2-bit transition value type
- EdgeDetector   : Generic state transition detector
- DebouncedState : Time-based debouncer (templated interval)

Design Goals:
- Extremely small memory footprint
- No hardware dependencies
- No timer objects
- Timestamp injected (ISR friendly)
- Suitable for AVR and Cortex-M

===============================================================================
*/

#include <stdint.h>
#include "StateChange/Edge.h"
#include "StateChange/EdgeDetector.h"
#include "StateChange/DebouncedState.h"

#endif /* STATE_CHANGE_LIB_H_ */