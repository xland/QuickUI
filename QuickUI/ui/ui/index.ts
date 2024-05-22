((global) => {
  let menuBox = document.getElementById("menuBox") as HTMLElement;
  menuBox.addEventListener("click", (e) => {
    let ele = e.target as HTMLElement;
    if (ele.classList.contains("menuSelected")) return;
    let id = ele.id.split("_")[1];
    if (!id) return;
    let oldMenu = document.querySelector(".menuSelected") as HTMLElement;
    oldMenu.classList.remove("menuSelected");
    ele.classList.add("menuSelected");
    let oldBox = document.querySelector(".contentBoxSelected") as HTMLElement;
    oldBox.classList.remove("contentBoxSelected");
    let box = document.getElementById("box_" + id) as HTMLElement;
    box.classList.add("contentBoxSelected");
  });
  let closeWindow = document.getElementById("closeWindow") as HTMLElement;
  closeWindow.addEventListener("click", (e) => {
    let flag = confirm("Debug version can not close window\n Are you sure you want to close this window?");
    if (flag) {
      webui.close();
    }
  });
})(globalThis);
