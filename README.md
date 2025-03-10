# Cross-Platform Keylogger

This project is a simple system-wide keylogger that works across multiple platforms: Windows, Linux, and macOS. It records keystrokes and logs them to a text file (keystrokes.txt). The code demonstrates how to interact with low-level keyboard events in each operating system to capture the key presses.

# Features

    Supports Windows, Linux, and macOS.
    Logs keystrokes to a file keystrokes.txt.
    Windows version uses SetWindowsHookEx to capture keyboard events.
    Linux version uses /dev/input to capture keypresses from the keyboard device.
    macOS version uses CGEventTap to intercept keyboard events.

# Requirements
For Windows

    Windows OS.
    A C compiler like GCC or MSVC.
    Necessary permissions to run the keylogger.

For Linux

    Linux OS (tested on Ubuntu).
    A C compiler like GCC.
    Root permissions to access the keyboard event file (/dev/input/by-path/platform-i8042-serio-0-event-kbd).

For macOS

    macOS OS.
    Permissions to access the system events.

# Important Notes

    Ethical Use: This keylogger is intended for educational purposes only. Do not use this tool for malicious activities.
    Unauthorized use of keyloggers is illegal and unethical.
    Permissions:
    On Linux, Windows and macOS, the program may require root permissions to access the keyboard device or system events.
    Make sure you have the necessary permissions before running the keylogger.
