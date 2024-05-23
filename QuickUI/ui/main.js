import * as os from "os";
os.setTimeout(() => {
    console.log("time out");
}, 32000);
webui.wait();