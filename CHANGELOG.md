# Changelog
All notable changes to this project will be documented in this file.

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
- Update version, opensource to Github.
- Rename function `cmei_version_string()` to `version_string()`.

## [Indev 26.8_03] - 2026-08-29
- Changed function `print_progress_bar()`
- emm.

### Known Issues
- Windows native CMD (not Terminal) does not support ANSI colors.
- `openshell` only works with default terminal paths (bash/powershell).