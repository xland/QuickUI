const win = new Win();
win.setKiosk(true);
win.show("<html><script src=\"webui.js\"></script> Hello World! </html>");

webui.wait();
