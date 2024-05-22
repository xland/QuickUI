//import * as os from 'os'
import * as std from "std";

let win = new Win();
win.setRootFolder("ui");
win.setSize(800, 600);
win.setPosition(1024, 300);
win.show("index.html");

win.bind("btnId", () => {
  console.log("allen,allen,allen");
});
globalThis.win = win;
