# Cross-Platform Keylogger

This project is a system-wide keylogger that works across multiple platforms: Windows, Linux, and macOS. It captures keystrokes and logs them to a text file (`keystrokes.txt`). The code demonstrates how to interact with low-level keyboard events on each operating system to capture key presses.

## Features

- Supports Windows, Linux, and macOS.
- Logs keystrokes to a file (`keystrokes.txt`).
- **Windows version** uses `SetWindowsHookEx` to capture keyboard events.
- **Linux version** uses `/dev/input` to capture key presses from the keyboard device.
- **macOS version** uses `CGEventTap` to intercept keyboard events.

## Requirements

### For Windows:
- Windows OS.
- A C compiler like GCC or MSVC.
- Necessary permissions to run the keylogger (e.g., administrator privileges).

### For Linux:
- Linux OS (tested on Ubuntu).
- A C compiler like GCC.
- Root permissions to access the keyboard event file (`/dev/input/by-path/platform-i8042-serio-0-event-kbd`).

### For macOS:
- macOS OS.
- Permissions to access system events (e.g., Accessibility or Full Disk Access permissions).

## Important Notes

- **Ethical Use**: This keylogger is intended for educational and research purposes only. Do not use this tool for malicious activities.
- **Legal Considerations**: Unauthorized use of keyloggers is illegal and unethical. Always obtain explicit consent from individuals before capturing keystrokes.
- **Permissions**:
  - On Linux, Windows, and macOS, the program may require elevated permissions to access the keyboard device or system events.
  - Ensure that you have the necessary permissions before running the keylogger.


## Installation

### For Windows:
1. Download the code or clone the repository:
   ```bash
   git clone https://github.com/your-repository/cross-platform-keylogger.git

2. Open the project folder in your preferred C compiler or IDE (e.g., MSVC or Code::Blocks).

        Compile the C code.

3. Run the program with administrator privileges to ensure it has access to system-wide events.

        Right-click the executable and select Run as administrator.


### For Linux:

1. Clone the repository or download the code:

        git clone https://github.com/your-repository/cross-platform-keylogger.git

2. Navigate to the project folder:

        cd cross-platform-keylogger

3. Install the necessary dependencies (GCC compiler and headers):

        sudo apt update
        sudo apt install build-essential

4. Compile the code:

        gcc -o keylogger keylogger.c

5. Run the program with root permissions:

        sudo ./keylogger



### For macOS:

1. Clone the repository or download the code:

        git clone https://github.com/your-repository/cross-platform-keylogger.git

2. Navigate to the project folder:

        cd cross-platform-keylogger

3. Install the necessary dependencies (Xcode command line tools):

        xcode-select --install

4. Compile the code:

        gcc -o keylogger keylogger.c

5. Run the program (you may need to grant Full Disk Access or Accessibility permissions in the System Preferences > Security & Privacy > Privacy tab):

        ./keylogger
