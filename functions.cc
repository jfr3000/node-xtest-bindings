#include "functions.h"
#include <X11/extensions/XTest.h>
#include <X11/keysymdef.h>

NAN_METHOD(XTestFakeKeyEvent) {
    auto keyCodeWrapper = info[0].As<v8::Integer>();
    auto keyCode = keyCodeWrapper->Int32Value();
    Display *display = XOpenDisplay(NULL);
    auto shiftKeycode = XKeysymToKeycode(display, XK_Shift_L);
    XTestGrabControl(display, true);

    XTestFakeKeyEvent(display, shiftKeycode, true, 0);

    XTestFakeButtonEvent(display, 1, true, 5000);
    XTestFakeButtonEvent(display, 1, false, 0);

    XTestFakeKeyEvent(display, shiftKeycode, false, 0);

    XSync(display, false);

    XTestGrabControl (display, false);
    XCloseDisplay(display);

    info.GetReturnValue().Set(keyCode);
}
