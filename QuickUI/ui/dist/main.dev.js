"use strict";

var win = new Win();
win.showBrowser('<html><script src="webui.js"></script> Hello World! </html>', 2);
win.setIcon("<svg t=\"1716465666965\" class=\"icon\" viewBox=\"0 0 1024 1024\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" p-id=\"2089\" width=\"200\" height=\"200\"><path d=\"M102.4 125.15555556v750.93333334h819.2V125.15555556H102.4zM34.13333333 56.8888889h955.73333334v887.46666666H34.13333333V56.8888889z\" fill=\"#333333\" p-id=\"2090\"></path><path d=\"M477.86666667 466.4888889V227.55555556h68.26666666V466.4888889H785.06666667v68.26666666H546.13333333v238.93333334h-68.26666666V534.75555556H238.93333333V466.4888889h238.93333334z\" fill=\"#333333\" p-id=\"2091\"></path></svg>", "image/svg+xml");
webui.wait();