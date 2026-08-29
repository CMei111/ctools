# ctools.hpp - Lightweight C++ Utility Headers

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Version](https://img.shields.io/badge/version-Indev_26.8_02-blue)](.)

**Status: 🚧 Experimental / Indev**  
A single-header, cross-platform C++ utility library for terminal manipulation, math constants, and basic algorithms.

## ✨ Features
- 🖥️ **Terminal Control**: Colored warnings/errors (ANSI/VT for Win/Linux) with automatic fallback.
- 🔢 **Math Helpers**: `is_prime`, `is_even`, `Max/Min`, and constants (PI, E).
- 🔄 **Efficient Swap**: Move-aware `Swap` implementation.
- 📦 **Header-only**: Just `#include "ctools.hpp"` and go.
- 📊 **Progress Bar**: Console Progressbar!

## 📦 Version
**Current:** `Indev 26.8_02` (API subject to breaking changes).  
Check [CHANGELOG.md](./CHANGELOG.md) for details.

## 🚀 Quick Start
```cpp
#include "ctools.hpp"
#include <iostream>

int main() {
    std::cout << "ctools version: " << ctools::version_string() << std::endl;
    ctools::write_warning("Hello, this is a warning!");
    return 0;
}
```

## 📋 Requirements
C++11 (or higher)

Cross-platform: Linux (bash/terminal) & Windows (PowerShell / Windows Terminal)

## 📜 License
Distributed under the MIT License.