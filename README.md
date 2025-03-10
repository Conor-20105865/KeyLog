# Cross-Platform Keylogger

This project is a simple system-wide keylogger that works across multiple platforms: Windows, Linux, and macOS. It records keystrokes and logs them to a text file (keystrokes.txt). The code demonstrates how to interact with low-level keyboard events in each operating system to capture the key presses.

# Features

    Supports Windows, Linux, and macOS.
    Logs keystrokes to a file keystrokes.txt.
    Windows version uses SetWindowsHookEx to capture keyboard events.
    Linux version uses /dev/input to capture keypresses from the keyboard device.
    macOS version uses CGEventTap to intercept keyboard events.
