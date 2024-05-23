import * as os from "os";
import * as std from "std";

let win = new Win();
win.setRootFolder("ui");
win.setSize(960, 800);
win.setPosition(1024, 300);
win.bind("closeThisWindow", () => {
  win.close();
});
win.bind("windowSizeChange", () => {
  win.setSize(800, 600);
});
win.show("index.html");
globalThis.win = win;
