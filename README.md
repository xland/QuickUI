# QuickUI

- Build desktop apps with JavaScript, HTML, and CSS.
- Based on [QuickJs](https://github.com/quickjs-ng/quickjs) and [WebUI](https://github.com/webui-dev/webui).
- Allow you to use any browser as a GUI render engine.
- Light weight (about **1M**) & Small memory footprint.
- Feature rich (clipboard, tray, sqlite...)

# Quick Start

```js
const win = new Win();
win.show("<html><script src=\"webui.js\"></script> Hello World! </html>");
webui.wait();
```

- Save this code in `main.js`
- Place `main.js` in the same directory as `QuickUI.exe`
- Start `QuickUI.exe`

# API

## webui

### clean
```js

```

### wait
```js
//main.js
// If There is one or more browser window,
// wait until all browser window get closed or when calling webui_exit().
// else if the browser did not get started, wait() will break after 30 seconds.
webui.wait();
```

### exit
```js
//main.js
// Try to close all opened windows and make wait return. 
// All WebUI memory resources will be freed, and this will makes WebUI unusable
webui.exit();
```


### setTimeout
```js
//main.js
//Set wait 10 seconds for the browser to start.
webui.setTimeout(10);
// Now, After 10 seconds, if the browser did not get started, wait() will break.
webui.wait();
```

```js
//main.js
//Set wait forever
webui.setTimeout(0);
// Now, wait() will never end.
webui.wait();
```

## global

QuickJs doesn't have `console.log` but QuickUI do.

```js
//main.js
console.log("hello world!");
webui.setTimeout(0); //set wait forever.
webui.wait(); //now wait forever.
```

## os

QuickJs sets the `setTimeout` and `setInterval` methods inside the `os` module.

### setTimeout

```js
//main.js
import * as os from "os";
os.setTimeout(() => {
    console.log("time out");
}, 1000);
webui.setTimeout(0); //set wait forever.
webui.wait(); //now wait forever.
```

### setInterval

```js
//main.js
import * as os from "os";
os.setInterval(() => {
    console.log("interval");
}, 1000);
webui.setTimeout(0); //set wait forever.
webui.wait(); //now wait forever.
```


