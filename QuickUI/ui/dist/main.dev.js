"use strict";

globalThis.win = new Win();
globalThis.win.setRootFolder("ui");
globalThis.win.setSize(800, 600);
globalThis.win.setPosition(1024, 300);
globalThis.win.show("index.html");
globalThis.win.bind("btnId", function () {
  console.log("allen,allen,allen");
});