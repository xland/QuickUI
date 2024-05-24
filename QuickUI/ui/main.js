const win = new Win();
win.bind("btn", (e) => {
    console.log(e.bindId);
    console.log(e.windowId);
    console.log(e.elementId);
    console.log(e.eventNumber);
    console.log(e.eventType);
    console.log(e.bindId);
});
win.show("<html><script src=\"webui.js\"></script><button id='btn'>click me</button></html>");
webui.wait();
