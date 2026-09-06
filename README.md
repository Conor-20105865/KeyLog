# Cross-Platform Keylogger

An educational **C-based cybersecurity proof-of-concept** exploring system-wide keyboard event handling across **Windows, Linux, and macOS**.

The project demonstrates how different operating systems expose low-level keyboard events and how platform-specific APIs can be used to monitor and process those events. It also explores system permissions, background processes, keyboard input handling, and the security and privacy implications of input monitoring.

> **Educational Project:** This software is intended for controlled environments, personal systems, and authorised security research only.

## Features

* Cross-platform implementation for **Windows, Linux, and macOS**
* Low-level keyboard event monitoring
* Platform-specific operating system APIs
* Local keystroke logging
* Background/daemon process handling on Linux and macOS
* Written entirely in **C**

### Platform Implementations

#### Windows

Uses the Windows API:

* `SetWindowsHookEx(WH_KEYBOARD_LL)` for low-level keyboard hooks
* `GetKeyboardState` for keyboard state information
* `MapVirtualKeyA` for virtual-key translation
* `ToAscii` for converting keyboard events into characters
* Windows message loop for processing keyboard events

Captured characters are written to:

```text
Documents\keystrokes.txt
```

#### Linux

Uses the Linux input subsystem:

* Reads keyboard events from `/dev/input`
* Processes Linux `input_event` structures
* Filters `EV_KEY` events
* Records keyboard input as key codes
* Uses a daemon process to continue running in the background

The current implementation writes to:

```text
/tmp/keystrokes.txt
```

> **Note:** The Linux implementation currently uses a specific keyboard device path and may require modification depending on the system's hardware and configuration.

#### macOS

Uses Apple's event APIs:

* `CGEventTap` for keyboard event monitoring
* Core Graphics event handling
* Keyboard layout translation
* Run loop for processing keyboard events
* Background/daemon process handling

The current implementation writes to:

```text
/tmp/keystrokes.txt
```

macOS may require appropriate **Accessibility permissions** for keyboard event monitoring.

---

## Technologies

* **C**
* Windows API
* Linux Input Subsystem
* macOS Core Graphics / `CGEventTap`
* GCC
* MSVC
* Platform-specific system APIs

---

## Requirements

### Windows

* Windows OS
* C compiler such as GCC or MSVC
* Appropriate permissions for low-level keyboard event monitoring

### Linux

* Linux operating system
* GCC or another C compiler
* Access to the keyboard input device
* Root privileges may be required

### macOS

* macOS
* C compiler
* Accessibility permissions for system event monitoring

---

## Building

The source code uses conditional compilation to provide platform-specific implementations.

The appropriate section of `logger.c` is compiled depending on the target operating system.

A C compiler such as **GCC** or **MSVC** is required.

> Build and compilation requirements may vary between operating systems due to differences in system APIs and permissions.

---

## Learning Objectives

This project was developed to explore:

* Low-level keyboard event handling
* Operating-system-specific APIs
* Cross-platform C development
* Windows keyboard hooks
* Linux input devices and `input_event`
* macOS event taps
* Process and daemon management
* System permissions and access controls
* Platform differences in keyboard input handling
* Security and privacy implications of input monitoring

---

## Security & Ethical Considerations

Keylogging technology can be used for legitimate security research as well as malicious purposes.

**Only use this software on systems you own or have explicit permission to test.**

Do not use this project for:

* Unauthorised surveillance
* Credential theft
* Capturing passwords or authentication codes
* Monitoring another person's activity without their knowledge
* Deploying software on systems without authorisation

Unauthorised interception or monitoring of keyboard input may violate applicable laws and regulations.

For experimentation, use a **dedicated test system or isolated virtual machine** whenever possible.

---

## Limitations

This project is intended as a **proof-of-concept and learning exercise**, rather than a production-ready monitoring system.

Current limitations include:

* The Linux implementation relies on a specific keyboard device path.
* Linux keyboard input is recorded as numeric key codes rather than translated characters.
* Keyboard character translation differs between operating systems.
* Platform-specific permissions are required.
* The implementations depend on operating-system-specific APIs.
* The project does not provide a unified installation or build system.

These limitations are intentional opportunities for further development and learning.

---

## Future Improvements

Potential improvements include:

* More robust Linux keyboard-device detection
* Improved cross-platform character translation
* Cleaner platform-specific build configurations
* Improved error handling
* Expanded documentation
* Additional testing across different hardware and operating-system versions

---

## Disclaimer

This repository is provided **solely for educational and authorised cybersecurity research purposes**.

The author does not condone the use of this software for unauthorised surveillance, credential theft, privacy violations, or other malicious activities.

Use responsibly and only on systems where you have explicit permission to perform testing.
