declare global {
  class Win {
    setRootFolder(folder: string): void;
    setSize(w: number, h: number): void;
    setPosition(x: number, y: number): void;
    show(url: string): void;
    bind(id: string, cb: Function): void;
  }
  module std {}
}

export {};
