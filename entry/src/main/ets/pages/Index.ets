import testNapi from 'libentry.so';
import EntryAbility from '../entryability/EntryAbility';
import { common } from '@kit.AbilityKit';
import { inputMethod } from '@kit.IMEKit';

@Entry
@Component
struct Index {
  private xcomponentController: XComponentController = new XComponentController();
  private context: common.UIAbilityContext = this.getUIContext().getHostContext() as common.UIAbilityContext;

  build() {
    Stack() {
      XComponent({
        id: 'dosboxXComponent',
        type: XComponentType.SURFACE,
        libraryname: 'entry',
        controller: this.xcomponentController
      })
        .width('100%')
        .height('100%')
        .onLoad(async (context?: object) => {
          // Get surface ID from XComponentController and create NativeWindow in C++
          let surfaceId: string = this.xcomponentController.getXComponentSurfaceId();
          testNapi.setSurfaceId(surfaceId);

          // Register XComponent callbacks for touch events etc.
          if (context) {
            testNapi.registerCallback(context);
          }

          // Wait for shared folder path to be resolved (permission request may be async)
          let sharedPath: string = await EntryAbility.pathReady;
          testNapi.setSharedFolderPath(sharedPath);

          // Register exit callback: when DOSBox exits naturally, terminate the app
          testNapi.registerExitCallback(() => {
            this.context.terminateSelf();
          });

          // Register show keyboard callback: touch event triggers system keyboard
          testNapi.registerShowKeyboardCallback(() => {
            try {
              let inputMethodController = inputMethod.getController();
              inputMethodController.showSoftKeyboard();
            } catch (e) {
              // Ignore errors if keyboard cannot be shown
            }
          });

          testNapi.startEmulator();
        })
        .onDestroy(() => {
          testNapi.stopEmulator();
        })
    }
    .width('100%')
    .height('100%')
    .onKeyEvent((event: KeyEvent) => {
      if (event) {
        let scancode = event.keyCode;
        let down = event.type === KeyType.Down ? 1 : 0;
        testNapi.sendKeyEvent(scancode, down);
      }
    })
  }
}
