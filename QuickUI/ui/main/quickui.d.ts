declare global {
  class webui {
    static setTimeout(second: number): void;
    static exit(): void;
    static wait(): void;
  }
  class Win {
    setRootFolder(folder: string): void;
    setSize(w: number, h: number): void;
    setPosition(x: number, y: number): void;
    show(val: string): void;
    navigate(url: string): void;
    /**
     * @param val
     *
     * @param browserType
        0. No web browser
        1. Default recommended web browser
        2. Google Chrome
        3. Mozilla Firefox
        4. Microsoft Edge
        5. Apple Safari
        6. The Chromium Project
        7. Opera Browser
        8. The Brave Browser
        9. The Vivaldi Browser
        10. The Epic Browser
        11. The Yandex Browser
        12. Any Chromium based browser
     */
    showBrowser(val: string, browserType: number): void;
    setIcon(icon: string, iconType: string): void;
    bind(id: string, cb: (e: { windowId: number; eventType: number; elementId: string; eventNumber: number; bindId: number }) => void): void;
    run(scriptStr: string): void;
    close(): void;
    destroy(): void;
    getUrl(): string;
    setKiosk(flag: boolean): void;
    setPublic(flag: boolean): void;
    setProxy(proxyServer: string): void;
  }
}

export {};
