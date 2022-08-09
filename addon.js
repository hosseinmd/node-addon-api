var addon = require("bindings")("addon");

var obj1 = addon("hello");
console.log({ obj1 }); // 'hello world'
