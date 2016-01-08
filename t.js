var o = require('./index');
var shift = o.keyCodes.XK_Shift_L;
var f = o.MyObject();
f.fakeButtonEvent(1, true, 3000);
f.fakeButtonEvent(1, false, 0);
f.fakeKeyEvent(shift, true, 0);
    f.fakeKeyEvent(65, true, 0);
    f.fakeKeyEvent(65, false, 0);
f.fakeKeyEvent(shift, false, 0);
