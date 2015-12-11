#include "functions.h"

using v8::FunctionTemplate;

// NativeExtension.cc represents the top level of the module.
// C++ constructs that are exposed to javascript are exported here

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, Nan::New("XTestFakeKeyEvent").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(XTestFakeKeyEvent)).ToLocalChecked());
}

NODE_MODULE(NativeExtension, InitAll)
