import * as os from "os";
os.setInterval(() => {
  console.log("interval");
}, 1000);
webui.setTimeout(0); //set wait forever.
webui.wait(); //now wait forever.
