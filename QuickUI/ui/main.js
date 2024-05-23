import * as os from "os";
let win = new Win();
win.show("<html><script src=\"webui.js\"></script> Hello World! </html>");
os.setTimeout(() => {
    console.log("time out!!!!!!!");
}, 1000);
globalThis.win = win;
webui.wait();