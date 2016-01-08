o = require('./index');
f = o.MyObject();
f.fakeButtonEvent(1, true, 3000);
f.fakeButtonEvent(1, false, 0);
f.fakeKeyEvent(65, true, 0);
f.fakeKeyEvent(65, false, 0);
