const win = new Win();
win.bind("btn", (e) => {
    console.log(e.bindId);
    console.log(e.windowId);
    console.log(e.elementId);
    console.log(e.eventNumber);
    console.log(e.eventType);
    console.log(e.bindId);
});
win.bind("btn2", (e) => {
    console.log(e.bindId);
    console.log(e.windowId);
    console.log(e.elementId);
    console.log(e.eventNumber);
    console.log(e.eventType);
    console.log(e.bindId);
});
win.show("<html><script src=\"webui.js\"></script><button id='btn'>click me</button><button id='btn2'>click me</button></html>");
webui.wait();
