(function (global) {
    var menuBox = document.getElementById("menuBox");
    menuBox.addEventListener("click", function (e) {
        var ele = e.target;
        if (ele.classList.contains("menuSelected"))
            return;
        var id = ele.id.split("_")[1];
        if (!id)
            return;
        var oldMenu = document.querySelector(".menuSelected");
        oldMenu.classList.remove("menuSelected");
        ele.classList.add("menuSelected");
        var oldBox = document.querySelector(".contentBoxSelected");
        oldBox.classList.remove("contentBoxSelected");
        var box = document.getElementById("box_" + id);
        box.classList.add("contentBoxSelected");
    });
    var closeWindow = document.getElementById("closeWindow");
    closeWindow.addEventListener("click", function (e) {
        var flag = confirm("Debug version can not close window\n Are you sure you want to close this window?");
        if (flag) {
            webui.closeThisWindow();
        }
    });
})(globalThis);
