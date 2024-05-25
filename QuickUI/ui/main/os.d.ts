declare module "os" {
  export function setTimeout(cb: () => void, time: number): number;
  export function setInterval(cb: () => void, time: number): number;
}
