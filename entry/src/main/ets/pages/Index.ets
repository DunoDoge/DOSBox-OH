import testNapi from 'libentry.so';
import EntryAbility from '../entryability/EntryAbility';
import { common } from '@kit.AbilityKit';
import { deviceInfo } from '@kit.BasicServicesKit';
import { inputMethod } from '@kit.IMEKit';
import { window } from '@kit.ArkUI';

@Entry
@Component
struct Index {
  private xcomponentController: XComponentController = new XComponentController();
  private context: common.UIAbilityContext = this.getUIContext().getHostContext() as common.UIAbilityContext;
  @State private keyboardVisible: boolean = false;
  @State private showKeyboardButton: boolean = true;
  private keyboardAttached: boolean = false;
  private inputMethodController: inputMethod.InputMethodController | null = null;
  private mainWindow: window.Window | null = null;

  aboutToAppear() {
    try {
      const dt: string = deviceInfo.deviceType;
      if (dt === '2in1') {
        this.showKeyboardButton = false;
      }
    } catch (e) {
      console.error('Failed to get device type');
    }
  }

  build() {
    Stack({ alignContent: Alignment.TopEnd }) {
      XComponent({
        id: 'dosboxXComponent',
        type: XComponentType.SURFACE,
        libraryname: 'entry',
        controller: this.xcomponentController
      })
        .width('100%')
        .height('100%')
        .onLoad(async (context?: object) => {
          let surfaceId: string = this.xcomponentController.getXComponentSurfaceId();
          testNapi.setSurfaceId(surfaceId);

          if (context) {
            testNapi.registerCallback(context);
          }

          let sharedPath: string = await EntryAbility.pathReady;
          testNapi.setSharedFolderPath(sharedPath);

          testNapi.registerExitCallback(() => {
            this.context.terminateSelf();
          });

          testNapi.registerShowKeyboardCallback(() => {
            this.toggleKeyboard();
          });

          testNapi.startEmulator();
          
          this.setupKeyboardListener();
        })
        .onDestroy(() => {
          testNapi.stopEmulator();
          this.cleanupInputMethod();
          this.removeKeyboardListener();
        })

      if (this.showKeyboardButton) {
        Button() {
          Row() {
            Text('⌨')
              .fontSize(24)
              .fontColor(Color.White)
            Text(this.keyboardVisible ? 'ON' : 'OFF')
              .fontSize(12)
              .fontColor(this.keyboardVisible ? '#4CAF50' : '#FF5252')
              .margin({ left: 4 })
          }
        }
        .width(80)
        .height(48)
        .backgroundColor(this.keyboardVisible ? '#E6333333' : '#CC333333')
        .borderRadius(8)
        .shadow({ radius: 6, color: '#80000000', offsetX: 2, offsetY: 2 })
        .margin({ top: 48, right: 16 })
        .onClick(() => {
          this.toggleKeyboard();
        })
      }
    }
    .width('100%')
    .height('100%')
    .focusable(true)
    .defaultFocus(true)
    .onKeyEvent((event: KeyEvent) => {
      if (event) {
        let scancode = event.keyCode;
        let down = event.type === KeyType.Down ? 1 : 0;
        testNapi.sendKeyEvent(scancode, down);
      }
    })
  }

  private setupKeyboardListener() {
    window.getLastWindow(this.context).then((currentWindow) => {
      this.mainWindow = currentWindow;
      this.mainWindow.on('keyboardHeightChange', (height: number) => {
        console.info('keyboardHeightChange: height=' + height);
        if (height > 0) {
          this.keyboardVisible = true;
          console.info('键盘已弹出 (ON)');
        } else {
          this.keyboardVisible = false;
          console.info('键盘已收起 (OFF)');
        }
      });
    }).catch((err: Error) => {
      console.error('setupKeyboardListener error: ' + JSON.stringify(err));
    });
  }

  private removeKeyboardListener() {
    if (this.mainWindow) {
      this.mainWindow.off('keyboardHeightChange');
      this.mainWindow = null;
    }
  }

  private toggleKeyboard() {
    try {
      if (!this.inputMethodController) {
        this.inputMethodController = inputMethod.getController();
      }

      if (!this.keyboardAttached) {
        this.attachInputMethod(true);
      } else if (this.keyboardVisible) {
        this.inputMethodController.hideTextInput();
      } else {
        this.inputMethodController.showTextInput();
      }
    } catch (e) {
      console.error('toggleKeyboard error:', JSON.stringify(e));
      this.keyboardVisible = false;
    }
  }

  private async attachInputMethod(showKeyboard: boolean) {
    try {
      if (!this.inputMethodController) {
        this.inputMethodController = inputMethod.getController();
      }

      const textConfig: inputMethod.TextConfig = {
        inputAttribute: {
          textInputType: inputMethod.TextInputType.TEXT,
          enterKeyType: inputMethod.EnterKeyType.NONE
        },
        cursorInfo: {
          left: 0,
          top: 0,
          width: 1,
          height: 1
        }
      };

      await this.inputMethodController.attach(showKeyboard, textConfig);
      this.keyboardAttached = true;
      this.registerInputMethodListeners();

      if (showKeyboard) {
        this.keyboardVisible = true;
      }
    } catch (e) {
      console.error('attachInputMethod error:', JSON.stringify(e));
      this.keyboardVisible = false;
      this.keyboardAttached = false;
    }
  }

  private registerInputMethodListeners() {
    if (!this.inputMethodController) {
      return;
    }

    this.inputMethodController.on('insertText', (text: string) => {
      this.handleInsertText(text);
    });

    this.inputMethodController.on('deleteLeft', (length: number) => {
      this.handleDeleteLeft(length);
    });

    this.inputMethodController.on('deleteRight', (length: number) => {
      this.handleDeleteRight(length);
    });

    this.inputMethodController.on('sendFunctionKey', (functionKey: inputMethod.FunctionKey) => {
      this.handleFunctionKey(functionKey);
    });

    this.inputMethodController.on('sendKeyboardStatus', (status: inputMethod.KeyboardStatus) => {
      this.handleKeyboardStatus(status);
    });
  }

  private handleInsertText(text: string) {
    for (let i = 0; i < text.length; i++) {
      const char = text[i];
      const keyCode = this.charToKeyCode(char);
      if (keyCode > 0) {
        testNapi.sendKeyEvent(keyCode, 1);
        testNapi.sendKeyEvent(keyCode, 0);
      }
    }
  }

  private charToKeyCode(char: string): number {
    const code = char.charCodeAt(0);

    if (code >= 65 && code <= 90) {
      return 2017 + (code - 65);
    }

    if (code >= 97 && code <= 122) {
      return 2017 + (code - 97);
    }

    if (char >= '0' && char <= '9') {
      return 2000 + parseInt(char);
    }

    switch (char) {
      case ',': return 2043;
      case '.': return 2044;
      case '`': return 2056;
      case '-': return 2057;
      case '=': return 2058;
      case '[': return 2059;
      case ']': return 2060;
      case '\\': return 2061;
      case ';': return 2062;
      case '\'': return 2063;
      case '/': return 2064;
      case '!': return 2047;
      case '@': return 2047;
      case '#': return 2047;
      case '$': return 2047;
      case '%': return 2047;
      case '^': return 2047;
      case '&': return 2047;
      case '*': return 2047;
      case '(': return 2047;
      case ')': return 2047;
      case '_': return 2057;
      case '+': return 2058;
      case '{': return 2059;
      case '}': return 2060;
      case '|': return 2061;
      case ':': return 2062;
      case '"': return 2063;
      case '<': return 2043;
      case '>': return 2044;
      case '?': return 2064;
      case '~': return 2056;
      case ' ': return 2050;
      default: return 0;
    }
  }

  private handleDeleteLeft(length: number) {
    for (let i = 0; i < length; i++) {
      testNapi.sendKeyEvent(2055, 1);
      testNapi.sendKeyEvent(2055, 0);
    }
  }

  private handleDeleteRight(length: number) {
    for (let i = 0; i < length; i++) {
      testNapi.sendKeyEvent(2071, 1);
      testNapi.sendKeyEvent(2071, 0);
    }
  }

  private handleFunctionKey(functionKey: inputMethod.FunctionKey) {
    switch (functionKey.enterKeyType) {
      case inputMethod.EnterKeyType.GO:
      case inputMethod.EnterKeyType.NEXT:
      case inputMethod.EnterKeyType.DONE:
      case inputMethod.EnterKeyType.PREVIOUS:
      case inputMethod.EnterKeyType.SEARCH:
      case inputMethod.EnterKeyType.SEND:
      case inputMethod.EnterKeyType.NEWLINE:
        testNapi.sendKeyEvent(2054, 1);
        testNapi.sendKeyEvent(2054, 0);
        break;
      case inputMethod.EnterKeyType.UNSPECIFIED:
      case inputMethod.EnterKeyType.NONE:
      default:
        break;
    }
  }

  private handleKeyboardStatus(status: inputMethod.KeyboardStatus) {
    console.info('handleKeyboardStatus: status=' + status);
    if (status === inputMethod.KeyboardStatus.SHOW) {
      this.keyboardVisible = true;
      console.info('Keyboard is now visible (ON)');
    } else if (status === inputMethod.KeyboardStatus.HIDE) {
      this.keyboardVisible = false;
      console.info('Keyboard is now hidden (OFF)');
    } else {
      console.warn('Unknown keyboard status: ' + status);
    }
  }

  private cleanupInputMethod() {
    try {
      if (this.inputMethodController) {
        this.inputMethodController.off('insertText');
        this.inputMethodController.off('deleteLeft');
        this.inputMethodController.off('deleteRight');
        this.inputMethodController.off('sendFunctionKey');
        this.inputMethodController.off('sendKeyboardStatus');

        if (this.keyboardVisible) {
          this.inputMethodController.hideTextInput();
        }

        if (this.keyboardAttached) {
          this.inputMethodController.detach();
        }

        this.keyboardAttached = false;
        this.keyboardVisible = false;
      }
    } catch (e) {
      console.error('cleanupInputMethod error:', JSON.stringify(e));
    }
  }
}
