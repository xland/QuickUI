"use strict";

var win = new Win();
win.setRootFolder("ui");
win.setSize(960, 800);
win.setPosition(1024, 300);
win.bind("closeThisWindow", function () {
  win.close();
});
win.bind("windowSizeChange", function () {
  win.setSize(800, 600);
});
win.show("index.html");
globalThis.win = win;