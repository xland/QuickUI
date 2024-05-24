declare global {
  class Win {
    setRootFolder(folder: string): void;
    setSize(w: number, h: number): void;
    setPosition(x: number, y: number): void;
    show(val: string): void;
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
    bind(id: string, cb: Function): void;
    run(scriptStr: string): void;
    close(): void;
    getUrl(): string;
  }
}

export {};
