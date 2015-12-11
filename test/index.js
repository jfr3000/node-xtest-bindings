var nativeExtension = require('../');
var assert = require('assert');


describe('native extension', function() {
  it('should export function that returns a number', function() {
    assert.equal(typeof nativeExtension.XTestFakeKeyEvent(5), 'number');
    assert.equal(nativeExtension.XTestFakeKeyEvent(5), 6);
  });
});
