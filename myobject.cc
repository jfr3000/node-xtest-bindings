#include <nan.h>

#include <X11/extensions/XTest.h>
#include <X11/keysymdef.h>
#include <string>
#include <iostream>

using std::endl;
using std::cout;

class MyObject : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init) {
            v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
            tpl->SetClassName(Nan::New("MyObject").ToLocalChecked());
            tpl->InstanceTemplate()->SetInternalFieldCount(1);

            //SetPrototypeMethod(tpl, "getHandle", GetHandle);
            SetPrototypeMethod(tpl, "fakeKeyEvent", fakeKeyEvent);
            SetPrototypeMethod(tpl, "fakeButtonEvent", fakeButtonEvent);

            constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
            Nan::Set(target, Nan::New("MyObject").ToLocalChecked(),
                    Nan::GetFunction(tpl).ToLocalChecked());
        }

    private:
        explicit MyObject(const char* displayArg) {
            if (displayArg) {
                cout << "Opening display " << displayArg << endl;
            } else {
                cout << "Opening default display " << endl;
            }
            display = XOpenDisplay(displayArg);
            XTestGrabControl(display, true);
        }
        ~MyObject() {
            cout << "Closing display" << endl;
            XTestGrabControl(display, false);
            XCloseDisplay(display);
        }

        static NAN_METHOD(New) {
            if (info.IsConstructCall()) {
                const char * displayArg = NULL;
                if (!info[0]->IsUndefined()) {
                    displayArg = * Nan::Utf8String(info[0]); 
                } 
                MyObject *obj = new MyObject(displayArg);
                obj->Wrap(info.This());
                info.GetReturnValue().Set(info.This());
            } else {
                const int argc = 1;
                v8::Local<v8::Value> argv[argc] = {info[0]};
                v8::Local<v8::Function> cons = Nan::New(constructor());
                info.GetReturnValue().Set(cons->NewInstance(argc, argv));
            }
        }

        static NAN_METHOD(fakeKeyEvent) {
            int keySym = Nan::To<int>(info[0]).FromMaybe('A');
            bool pressed = Nan::To<bool>(info[1]).FromMaybe(true);
            int delay = Nan::To<int>(info[2]).FromMaybe(0);

            MyObject* obj = Nan::ObjectWrap::Unwrap<MyObject>(info.This());
            int keyCode = XKeysymToKeycode(obj->display, keySym);
            cout << "faking key press " << pressed << " keySym: " << keySym << "code: " << keyCode << " delay = " << delay << endl;

            int returnValue = XTestFakeKeyEvent(obj->display, keyCode, pressed, delay);
            XSync(obj->display, false);
            info.GetReturnValue().Set(returnValue);
        }

        /*
         * You can map 8 mouse buttons 
         * (1 – Left, 2 – Middle, 3 – Right, 5 – Scroll,..).
         */
        static NAN_METHOD(fakeButtonEvent) {
            int button = Nan::To<int>(info[0]).FromMaybe(1);
            bool pressed = Nan::To<bool>(info[1]).FromMaybe(true);
            int delay = Nan::To<int>(info[2]).FromMaybe(0);

            MyObject* obj = Nan::ObjectWrap::Unwrap<MyObject>(info.This());
            cout << "faking mouse button press " << pressed << " button: " << button << " delay = " << delay << endl;

            int returnValue = XTestFakeButtonEvent(obj->display, button, pressed, delay);
            XSync(obj->display, false);
            info.GetReturnValue().Set(returnValue);
        }

        static inline Nan::Persistent<v8::Function> & constructor() {
            static Nan::Persistent<v8::Function> my_constructor;
            return my_constructor;
        }

        Display* display;
};

NODE_MODULE(NativeExtension, MyObject::Init)
