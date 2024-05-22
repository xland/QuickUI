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
})(globalThis);
