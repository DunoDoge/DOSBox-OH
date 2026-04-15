import { AbilityConstant, ConfigurationConstant, UIAbility, Want, abilityAccessCtrl, Permissions, PermissionRequestResult } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { window } from '@kit.ArkUI';
import { fileIo, Environment } from '@kit.CoreFileKit';

const DOMAIN = 0xFF00;
const DOWNLOAD_PERMISSION: Permissions = 'ohos.permission.READ_WRITE_DOWNLOAD_DIRECTORY';

export default class EntryAbility extends UIAbility {
  static sharedFolderPath: string = '';
  static pathReady: Promise<string> = new Promise(() => {});
  private static pathResolve: ((path: string) => void) | null = null;
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    try {
      this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_NOT_SET);
    } catch (err) {
      hilog.error(DOMAIN, 'testTag', 'Failed to set colorMode. Cause: %{public}s', JSON.stringify(err));
    }
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onCreate');
  }

  onDestroy(): void {
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onDestroy');
  }

  // Request Download directory permission and resolve shared folder path
  private async resolveSharedFolderPath(): Promise<string> {
    // Step 1: Try to request Download directory permission
    let downloadDirGranted = false;
    try {
      const atManager = abilityAccessCtrl.createAtManager();
      const grantResult: PermissionRequestResult =
        await atManager.requestPermissionsFromUser(this.context, [DOWNLOAD_PERMISSION]);
      // authResults[0] === 0 means PERMISSION_GRANTED
      if (grantResult.authResults[0] === 0) {
        downloadDirGranted = true;
        hilog.info(DOMAIN, 'testTag', 'Download permission granted');
      } else {
        hilog.warn(DOMAIN, 'testTag', 'Download permission denied: %{public}d', grantResult.authResults[0]);
      }
    } catch (err) {
      const errMsg: string = (err as Error).message;
      hilog.warn(DOMAIN, 'testTag', 'Failed to request Download permission: %{public}s', errMsg);
    }

    // Step 2: Try Download directory first, fall back to filesDir
    let sharedDir: string = '';
    if (downloadDirGranted) {
      try {
        let downloadDir: string = Environment.getUserDownloadDir();
        sharedDir = downloadDir + '/DOSBox-OH';
        hilog.info(DOMAIN, 'testTag', 'Download dir: %{public}s', downloadDir);
      } catch (err) {
        const errMsg: string = (err as Error).message;
        hilog.warn(DOMAIN, 'testTag', 'Failed to get Download dir: %{public}s', errMsg);
      }
    }

    if (sharedDir.length === 0) {
      // Fall back to app filesDir (always accessible, no permission needed)
      try {
        let filesDir: string = this.context.filesDir;
        sharedDir = filesDir + '/DOSBox-OH';
        hilog.info(DOMAIN, 'testTag', 'Fallback to filesDir: %{public}s', filesDir);
      } catch (err) {
        const errMsg: string = (err as Error).message;
        hilog.error(DOMAIN, 'testTag', 'Failed to get filesDir: %{public}s', errMsg);
        return '';
      }
    }

    // Step 3: Create directory if not exists
    try {
      if (!fileIo.accessSync(sharedDir)) {
        fileIo.mkdirSync(sharedDir, true);
      }
      hilog.info(DOMAIN, 'testTag', 'Shared folder path: %{public}s', sharedDir);
      return sharedDir;
    } catch (err) {
      const errMsg: string = (err as Error).message;
      hilog.warn(DOMAIN, 'testTag', 'Failed to create shared dir: %{public}s', errMsg);
      return '';
    }
  }

  onWindowStageCreate(windowStage: window.WindowStage): void {
    // Main window is created, set main page for this ability
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onWindowStageCreate');

    // Resolve shared folder path asynchronously (request permission + create dir)
    EntryAbility.pathReady = new Promise<string>((resolve) => {
      EntryAbility.pathResolve = resolve;
    });
    this.resolveSharedFolderPath().then((path: string) => {
      EntryAbility.sharedFolderPath = path;
      hilog.info(DOMAIN, 'testTag', 'Final sharedFolderPath: %{public}s', EntryAbility.sharedFolderPath);
      if (EntryAbility.pathResolve) {
        EntryAbility.pathResolve(path);
      }
    }).catch((err: Error) => {
      hilog.error(DOMAIN, 'testTag', 'resolveSharedFolderPath failed: %{public}s', err.message);
      EntryAbility.sharedFolderPath = '';
      if (EntryAbility.pathResolve) {
        EntryAbility.pathResolve('');
      }
    });

    windowStage.loadContent('pages/Index', (err) => {
      if (err.code) {
        hilog.error(DOMAIN, 'testTag', 'Failed to load the content. Cause: %{public}s', JSON.stringify(err));
        return;
      }
      hilog.info(DOMAIN, 'testTag', 'Succeeded in loading the content.');
    });

    // Set status bar and navigation bar to black with immersive mode
    let windowClass: window.Window | null = null;
    windowStage.getMainWindow((err, data) => {
      if (err.code) {
        hilog.error(DOMAIN, 'testTag', 'Failed to get main window. Cause: %{public}s', JSON.stringify(err));
        return;
      }
      windowClass = data;
      // Set immersive mode for full screen
      windowClass.setWindowLayoutFullScreen(true);
      // Set status bar and navigation bar background to black
      windowClass.setWindowSystemBarProperties({
        statusBarColor: '#000000',
        navigationBarColor: '#000000'
      });
    });
  }

  onWindowStageDestroy(): void {
    // Main window is destroyed, release UI related resources
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onWindowStageDestroy');
  }

  onForeground(): void {
    // Ability has brought to foreground
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onForeground');
  }

  onBackground(): void {
    // Ability has back to background
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onBackground');
  }
}