export const startEmulator: () => boolean;
export const stopEmulator: () => void;
export const sendKeyEvent: (scancode: number, down: number) => void;
export const registerCallback: (context: object) => boolean;
export const setSurfaceId: (surfaceId: string) => void;
export const setSharedFolderPath: (path: string) => void;
export const registerExitCallback: (callback: () => void) => void;
