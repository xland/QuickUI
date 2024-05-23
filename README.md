# QuickUI

- Build desktop apps with JavaScript, HTML, and CSS.
- Based on [QuickJs](https://github.com/quickjs-ng/quickjs) and [WebUI](https://github.com/webui-dev/webui).
- Allow you to use any browser as a GUI render engine.
- Light weight (about **1M**) & Small memory footprint.
- Feature rich (clipboard, tray, sqlite...).

# Quick Start

```js
const win = new Win();
win.show("<html><script src=\"webui.js\"></script> Hello World! </html>");
webui.wait();
```

- Save this code in `main.js`.
- Place `main.js` in the same directory as `QuickUI.exe`.
- Start `QuickUI.exe`.

# API


## webui

### wait
```js
// main.js
// If There is one or more browser window,
// wait until all browser window get closed or when calling webui_exit().
// else if the browser did not get started, wait() will break after 30 seconds.
webui.wait();
```

### exit
```js
// main.js
// Try to close all opened windows and make wait return. 
// All WebUI memory resources will be freed, and this will makes WebUI unusable.
webui.exit();
```


### setTimeout
```js
// main.js
// Set wait 10 seconds for the browser to start.
webui.setTimeout(10);
// Now, After 10 seconds, if the browser did not get started, wait() will break.
webui.wait();
```

```js
// main.js
// Set wait forever
webui.setTimeout(0);
// Now, wait() will never end.
webui.wait();
```

## Win

`Win` is a class.

### show
```js
// create window object.
const win = new Win();
// Show a window using embedded HTML.
win.show("<html><script src=\"webui.js\"></script> Hello World! </html>");
webui.wait();
```
```js
// create window object.
const win = new Win();
// Show a window using a file.
win.show("index.html");
webui.wait();
```

### showBrowser
```js
//main.js
// Same as `win.show`. But using a specific web browser.
// 0. No web browser
// 1. Default recommended web browser
// 2. Google Chrome
// 3. Mozilla Firefox
// 4. Microsoft Edge
// 5. Apple Safari
// 6. The Chromium Project
// 7. Opera Browser
// 8. The Brave Browser
// 9. The Vivaldi Browser
// 10. The Epic Browser
// 11. The Yandex Browser
// 12. Any Chromium based browser
win.showBrowser("index.html",2);
```

### setIcon
```js
// main.js
// myIcon = "<svg>...</svg>"
// myIconType = "image/svg+xml"
// 
// myIcon = "data:image/..."
// myIconType = "image/png"
win.setIcon(myIcon,myIconType);
```

### setPosition

### setSize

### navigate

### getUrl

### setKiosk

### setPublic

### setProxy

### setRootFolder

### close

### destroy

### run

### bind



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

# TypeScript Support

The Declaration File : [webui.d.ts](https://github.com/xland/QuickUI/blob/main/QuickUI/ui/main/webui.d.ts)
