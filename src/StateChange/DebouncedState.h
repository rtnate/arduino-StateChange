//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//!  @file DebouncedState.h 
//!  @brief DebouncedState Class Template Header
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


#ifndef STATE_CHANGE_DEBOUNCED_STATE_H_
#define STATE_CHANGE_DEBOUNCED_STATE_H_

#include <stdint.h>
#include "./Edge.h"

/**
 * @brief A Class Template that provides debouncing of a boolean input state 
 *        to get clean output
 * 
 * @tparam DebounceMs - The debounce period in milliseconds
 */
template<uint32_t DebounceMs>
class DebouncedState
{
public:
    DebouncedState(): flags_(0), lastChangeTime_(0){};

    explicit DebouncedState(bool initial):
        flags_(initial ? (DebouncedMask | PrevDebouncedMask | RawMask) : 0),
        lastChangeTime_(0)
        {}

    /**
     * @brief Updates the state machine with a new value, providing
     *        debouncing at the template supplied DebounceMS
     * 
     * @param raw The current raw input value to debounce
     * @param now The current timestamp in milliseconds
     * @return true if the debounced state has changed
     * @return false if not
     */
    bool update(bool raw, uint32_t now)
    {
        uint8_t f = flags_;
        bool lastRaw = f & RawMask;
        bool debounced = f & DebouncedMask;

        if (raw != lastRaw)
        {
            setRaw(raw);
            lastChangeTime_ = now;
            return false;
        }

        if (debounced != raw &&
            elapsed(now, lastChangeTime_))
        {
            setPreviousDebounced(debounced);
            setDebounced(raw);
            return true;
        }

        return false;
    }

    /**
     * @brief The current debounced state
     * 
     * @return true or false - the current debounced state
     */
    bool state() const
    {
        return flags_ & DebouncedMask;
    }

    /**
     * @brief Returns the most recent debounced transition.  This 
     *        Edge is only valid after update() returns true and 
     *        before update() is called again
     * 
     * @return Edge 
     */
    Edge edge() const
    {
        //Edge::fromRaw masks to bits 0,1 internally
        return Edge::fromRaw(flags_);
    }

    /**
     * @brief Calculates if a timer/time period has elapsed
     * 
     * @param now The current time in milliseconds
     * @param start The start time in milliseconds
     * @param interval The test timer interval
     * @return true if it has been interval milliseconds since start
     * @return false if not
     */
    static constexpr inline bool elapsed(uint32_t now,
                               uint32_t start,
                               uint32_t interval)
    {
        return (uint32_t)(now - start) >= interval;
    }

    /**
     * @brief Calculates if a timer/time period has exceeded template DebounceMs
     * 
     * @param now The current time in milliseconds
     * @param start The start time in milliseconds
     * @return true if it has been DebounceMs since start
     * @return false if not
     */
    static constexpr inline bool elapsed(uint32_t now,
                               uint32_t start)
    {
        return (uint32_t)(now - start) >= DebounceMs;
    }
private:
    static constexpr uint8_t RawMask           = 0x4; //!< The Raw State Bit Flag Mask
    static constexpr uint8_t DebouncedMask     = 0x1; //!< The Debounce State Bit Flag Mask
    static constexpr uint8_t PrevDebouncedMask = 0x2; //!< The Prev. Debounce State Bit Flag Mask

    /**
     * @brief Sets the raw state flag
     *  
     * @param v the boolean raw state variable 
     */
    void setRaw(bool v)
    {
        v ? flags_ |= RawMask : flags_ &= ~RawMask;
    }

    /**
     * @brief Sets the debounced state flag
     *  
     * @param v the boolean debounced variable 
     */
    void setDebounced(bool v)
    {
        v ? flags_ |= DebouncedMask : flags_ &= ~DebouncedMask;
    }

    /**
     * @brief Sets the previous debounced state flag
     *  
     * @param v the boolean previous debounced variable 
     */
    void setPreviousDebounced(bool v)
    {
        v ? flags_ |= PrevDebouncedMask : flags_ &= ~PrevDebouncedMask;
    }

    uint8_t  flags_ = 0; //!< Bit flag storage (Bit 0: debounced, Bit 1: prev. debounced, Bit 2: raw state)
    uint32_t lastChangeTime_ = 0; //!< The timestamp at the last point raw state changed
};

#endif /* STATE_CHANGE_DEBOUNCED_STATE_H_ */