# Changelog
All notable changes to this project will be documented in this file.
Tips:editon string:`<Year><Mouth>_<Version Number>[-EF<Hot Fix Version Number>|-SUB<Sub Version Number>]`

## [Indev 26.8_01] - 2026-08-26
### Added
- Initial public release.
- Core utilities: `Swap`, `Classic_Swap`, `reset_array`, `fill_array`.
- Math helpers: `is_prime`, `is_even`, `Max`, `Min`, `can_exactly_divisible`.
- Terminal colors: `write_warning`, `write_error`, `reset_console` (cross-platform).
- Constants: `PI`, `E`, `DEG_TO_RAD` in `cconst`.
- Control characters: `ctrl::RED`, `ctrl::GREEN`, etc.
- Version macro: `CMEI_HEAD_FILE_VERSION` (`Indev 26.8_01`).

## [Indev 26.8_02] - 2026-08-28
### Changed
- Update version, opensource to Github.
- Rename function `cmei_version_string()` to `version_string()`.
### Added
- Add a Console progress bar function print_progress_bar

## [Indev 26.8_03] - 2026-08-29
### Changed
- Changed function `print_progress_bar()`

## [Indev 26.8_03-EF1]
### Fixed
- Fix README.md's version number bug.

## [Indev 26.8_03-EF2]
### Fixed
- Fix README.md's version badge bug.

## [Indev 26.8_03-SUB1]
### Changed
- Changed CHANGLOG.md.

## [Indev 26.8_04] - 2026-08-30
### Added
- Add WIN_LF and PLATFORM_LF
- Add a toggle_case() function.It can case reversal!Like This:
```cpp
toggle_case(std::string str, letters_class to_letter_class)
``` 

## [Indev 26.8_05] - 2026-08-30
### Added
- Add a choice() function.Call it will show a choice pancel.
- Add a get_keypress function.It will return pressed key's ASCII code.
```cpp
inline char get_keypress()
int choice(const std::vector<std::string>& opt, std::string message = "Enter Your Choice:")
```

## [Indev 26.8_06] - 2026-09-05
### Added
- Add a random_string function.It can make a string at random.
- Add a ascii_code can trun `int` to `char`.
- Add a get_ascii_code can trun `char` to `int`.

## [Indev 26.9_01] - 2026-09-26
### Added
- Added `cconst::charset` constant for default random character generation.
- Added `random_string()` function with default and custom charset overloads.
- Added `ascii_code()` and `get_ascii_code()` for ASCII conversion.
- Added `pause()` function for console interaction.
- Split basic terminal functions (`get_keypress`, `throw_err`) into `lib/basic.hpp`.
### Changed
- Bumped version to `Indev 26.9_01`.

## [Indev 26.9_02] - 2026-09-27
### Added
- Added `sleep()` function.It can let program sleep.
- Added `cppio_optimise()` function.It will optimise (or unoptimise) C++ I/O speed.
- Added `cppio_tied()` function.It can return current C++ input tied to.
### Fixed
- now programs below C++ 17 standard can't be compiled.

## [Indev 26.9_03] - 2026-10-2
### Added
- Added `create_object` function to create object.
- Added `initialized_object` function to create and initialize object.
- Added `del_ptr` function to delete pointer.
- Added `set_nullptr` function to set a a pointer null.
- Added `set_null_and_del` function to delete and set pointer null.
**WARNING! There are template functions!**
### Changed
- Moved enums to namespace `ctools::enums::`.
### Removed
- Removed function `crash_memory`.
- Removed function `never_stop`.

## [Indev 26.10.01] - 2026-10-17
### Added
- Added `COMPILE_PLATFORM` macro. It evaluates to an integer value (1:GCC, 2:Clang, 3:MSVC, 0:Other).
- Added function `sqrt` to calculate the square root of a number.
- Added function `noop` (no operation), which does nothing.
- Added class `auto_ptr` for automatic object deletion and RAII memory management.
- Added function `arrvalue_cnt` to return the number of elements in an array.
- Added enum `bswitch` to indicate switch states.
- Added enum `power_state` to indicate power states.
### Changed
- Renamed function `Swap` to `swap`.
- Renamed function `Max` to `max`.
- Renamed function `Min` to `min`.
### Fixed
- Fixed an issue where function `cpp_version` always returned `199711L` (C++98) when compiled with MSVC, unless the `/Zc:__cplusplus` compiler flag was explicitly added.
### Deprecated
- Deprecated function `Classic_Swap`, because it too slow!

## [Indev 26.10_02] - 2026-10-24
### Added
- Added function `strlen` to calculate length of a char array.
- Added `ctools::errors` enumeration for standardized error handling across the library.
- Added struct `error` to indicate a error.
- Added platform-agnostic device paths: `console_file` and `null_device`.
### Changed
- Renamed the header guard macro from `CMEI_TOOLS_H` to `CMEI_CTOOLS_HPP` to match the file extension.

# Known Issues
- Windows native CMD (not Terminal) does not support ANSI colors.
- `openshell` only works with default terminal paths (bash/powershell).