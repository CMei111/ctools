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

### [Indev 26.9_02] - 2026-09-27
### Added
- Added `sleep()` function.It can let program sleep.
- Added `cppio_optimise()` function.It will optimise (or unoptimise) C++ I/O speed.
- Added `cppio_tied()` function.It can return current C++ input tied to.


# Known Issues
- Windows native CMD (not Terminal) does not support ANSI colors.
- `openshell` only works with default terminal paths (bash/powershell).