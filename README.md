# StateChange

A lightweight C++ micro-library for detecting boolean state transitions and managing debounced state.

Designed for embedded systems and Arduino-compatible platforms.

---

## Overview

`StateChange` provides small, deterministic primitives for working with boolean signals:

- Edge detection (rising / falling)
- Stateful transition tracking
- Debounced state management
- No dynamic allocation
- No hardware dependencies
- Cross-platform (AVR, ARM, desktop)

This library does **not** manage GPIO.  
It operates purely on boolean values.

---

## Components

### `Edge`

Represents a transition between two boolean states.

```cpp
Edge e(lastState, currentState);

if (e.rising())  { /* low → high */ }
if (e.falling()) { /* high → low */ }
```

---

### `EdgeDetector`

Tracks state over time and reports transitions.

```cpp
EdgeDetector detector;

Edge e = detector.update(currentState);

if (e.rising()) {
    // handle rising edge
}
```

---

### `DebouncedState`

Implements debounced state tracking using timestamps.

```cpp
DebouncedState<50> debounced; // 50ms debounce

if (debounced.update(rawState, millis())) {
    Edge e = debounced.edge();

    if (e.falling()) {
        // button released
    }
}
```

`update()` returns `true` only when the debounced state changes.

---

## Design Goals

- Minimal footprint
- Deterministic behavior
- No hidden timing
- No interrupts required
- No heap usage
- Clear separation between hardware and logic

This library is intended to be wrapped by higher-level input abstractions.

---

## Installation

### Arduino

1. Download the repository
2. Place it in your Arduino `libraries` folder
3. Include:

```cpp
#include <StateChange.h>
```

---

## License

MIT License  
© Nate Taylor