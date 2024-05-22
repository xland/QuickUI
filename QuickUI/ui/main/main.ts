import * as os from "os";
import * as std from "std";

let win = new Win();
win.setRootFolder("ui");
win.setSize(960, 800);
win.setPosition(1024, 300);
win.show("index.html");

win.bind("windowSizeChange", () => {
  win.setSize(800, 600);
});
win.bind("closeWindow", () => {
  win.close();
});
win.bind("close", () => {
  win.close();
});
globalThis.win = win;