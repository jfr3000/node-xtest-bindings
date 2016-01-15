var NativeExtension = require('bindings')('NativeExtension');
module.exports = function(display) {
    var ret = NativeExtension.MyObject(display);
    ret.keySyms = require('./keysymdef');
    return ret;
};
