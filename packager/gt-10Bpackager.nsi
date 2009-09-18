; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "GT-10BFxFloorBoard"
!define PRODUCT_VERSION "20090918"
!define PRODUCT_PUBLISHER "gumtownbassman"
!define PRODUCT_WEB_SITE "http://gtx.tinfoilmusic.net"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\GT-10Bfxfloorboard.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "license.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\GT-10Bfxfloorboard.exe"
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\readme.txt"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "GT-10BFxFloorBoard-Setup.exe"
InstallDir "$PROGRAMFILES\GT-10BFxFloorBoard"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File "readme.txt"
  File "preferences.xml.dist"
  File "mingwm10.dll"
  File "license.txt"
  File "GT-10BFxFloorBoard_help.html"
  File "GT-10Bfxfloorboard.exe"
  CreateDirectory "$SMPROGRAMS\GT-10BFxFloorBoard"
  CreateShortCut "$SMPROGRAMS\GT-10BFxFloorBoard\GT-10BFxFloorBoard.lnk" "$INSTDIR\GT-10Bfxfloorboard.exe"
  CreateShortCut "$DESKTOP\GT-10BFxFloorBoard.lnk" "$INSTDIR\GT-10Bfxfloorboard.exe"
  SetOutPath "$INSTDIR\GT-10BFxFloorBoard_help_files"
  SetOverwrite try
  File "GT-10BFxFloorBoard_help_files\filelist.xml"
  File "GT-10BFxFloorBoard_help_files\image001.gif"
  File "GT-10BFxFloorBoard_help_files\image002.gif"
  File "GT-10BFxFloorBoard_help_files\image003.gif"
  File "GT-10BFxFloorBoard_help_files\image004.gif"
  File "GT-10BFxFloorBoard_help_files\image005.gif"
  File "GT-10BFxFloorBoard_help_files\image006.gif"
  File "GT-10BFxFloorBoard_help_files\image007.gif"
  File "GT-10BFxFloorBoard_help_files\image007.jpg"
  File "GT-10BFxFloorBoard_help_files\image008.gif"
  File "GT-10BFxFloorBoard_help_files\image008.jpg"
  File "GT-10BFxFloorBoard_help_files\image009.gif"
  File "GT-10BFxFloorBoard_help_files\image009.jpg"
  File "GT-10BFxFloorBoard_help_files\image010.gif"
  File "GT-10BFxFloorBoard_help_files\image011.gif"
  File "GT-10BFxFloorBoard_help_files\image012.gif"
  File "GT-10BFxFloorBoard_help_files\image012.jpg"
  File "GT-10BFxFloorBoard_help_files\image013.gif"
  File "GT-10BFxFloorBoard_help_files\image013.jpg"
  File "GT-10BFxFloorBoard_help_files\image014.jpg"
  File "GT-10BFxFloorBoard_help_files\image015.jpg"
  File "GT-10BFxFloorBoard_help_files\image016.gif"
  File "GT-10BFxFloorBoard_help_files\image017.gif"
  File "GT-10BFxFloorBoard_help_files\image018.gif"
  File "GT-10BFxFloorBoard_help_files\image019.gif"
  File "GT-10BFxFloorBoard_help_files\image020.gif"
  File "GT-10BFxFloorBoard_help_files\image021.gif"
  File "GT-10BFxFloorBoard_help_files\image022.gif"
  File "GT-10BFxFloorBoard_help_files\image023.gif"
  File "GT-10BFxFloorBoard_help_files\image024.jpg"
  File "GT-10BFxFloorBoard_help_files\image025.gif"
  File "GT-10BFxFloorBoard_help_files\image026.jpg"
  File "GT-10BFxFloorBoard_help_files\image027.jpg"
  File "GT-10BFxFloorBoard_help_files\image028.gif"
  File "GT-10BFxFloorBoard_help_files\image030.jpg"
  File "GT-10BFxFloorBoard_help_files\image031.gif"
  File "GT-10BFxFloorBoard_help_files\image033.gif"
  File "GT-10BFxFloorBoard_help_files\image034.gif"
  File "GT-10BFxFloorBoard_help_files\image035.gif"
  File "GT-10BFxFloorBoard_help_files\image038.gif"
  SetOutPath "$INSTDIR\Init Patches"
  File "Init Patches\001_Super Flat.syx"
  File "Init Patches\002_Flip Top.syx"
  File "Init Patches\003_Fender BassMan.syx"
  File "Init Patches\004_Concert 810.syx"
  File "Init Patches\005_Bass 360.syx"
  File "Init Patches\006_Trace Elliot.syx"
  File "Init Patches\007_Session.syx"
  File "Init Patches\008_AC Bass.syx"
  File "Init Patches\009_Guitar Clean.syx"
  File "Init Patches\010_Guitar Crunch.syx"
  File "Init Patches\011_Guitar Drive.syx"
  File "Init Patches\012_Guitar Metal.syx"
  File "Init Patches\My 810.syx"
  File "Init Patches\SansAmp SVT.syx"
  File "Init Patches\SGX NGTBASS.syx"
  File "Init Patches\StoneBlue drive.syx"
  SetOutPath "$INSTDIR\Mid Patches"
  File "mid patches\DoubleSoundHold.mid"
  File "mid patches\Quadravox.mid"
  File "mid patches\the lone ranger.mid"
  File "mid patches\Tornado3DFeedback.mid"
  SetOutPath "$INSTDIR\Saved Patches"
  File "saved_patches\!AutoOrgan_v1.syx"
  File "saved_patches\!AutoSensWAH_v1.syx"
  File "saved_patches\!BassMurf_v1.syx"
  File "saved_patches\!FartBender_v1.syx"
  File "saved_patches\AC Bass.syx"
  File "saved_patches\Don't Stop.syx"
  File "saved_patches\GEDDY YYZ CC Patch.syx"
  File "saved_patches\Lets Groove.syx"
  File "saved_patches\mad scientist.syx"
  File "saved_patches\My 810.syx"
  File "saved_patches\ONE OF THES DAYS.syx"
  File "saved_patches\pluckylightphase.syx"
  SetOutPath "$INSTDIR\Saved Patches\Quick FX"
  File "saved_patches\Quick FX\QuickFX_001.syx"
  File "saved_patches\Quick FX\QuickFX_002.syx"
  File "saved_patches\Quick FX\QuickFX_003.syx"
  File "saved_patches\Quick FX\QuickFX_004.syx"
  File "saved_patches\Quick FX\QuickFX_005.syx"
  File "saved_patches\Quick FX\QuickFX_006.syx"
  File "saved_patches\Quick FX\QuickFX_007.syx"
  File "saved_patches\Quick FX\QuickFX_008.syx"
  File "saved_patches\Quick FX\QuickFX_009.syx"
  File "saved_patches\Quick FX\QuickFX_010.syx"
  SetOutPath "$INSTDIR\Saved Patches"
  File "saved_patches\SansAmp Fat Tube.syx"
  File "saved_patches\SansAmp SVT.syx"
  File "saved_patches\SansSamp Bassman.syx"
  File "saved_patches\scoop slap.syx"
  File "saved_patches\sequencer circus.syx"
  File "saved_patches\SGX NGTBASS.syx"
  File "saved_patches\SOB SPACE S HOLD.syx"
  File "saved_patches\spacebar.syx"
  File "saved_patches\Stadium_Drive.syx"
  File "saved_patches\StoneBlue Chorus.syx"
  File "saved_patches\StoneBlue drive.syx"
  File "saved_patches\StoneBlue_Fuzzy.syx"
  File "saved_patches\super dooper.syx"
  File "saved_patches\synthdrive venus.syx"
  File "saved_patches\Talker_Twah_v1.syx"
  File "saved_patches\the_Lone_Ranger.syx"
  File "saved_patches\Tool.syx"
  File "saved_patches\venuspedal.syx"
  File "saved_patches\vintage synth.syx"
SectionEnd

Section -AdditionalIcons
  SetOutPath $INSTDIR
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\GT-10BFxFloorBoard\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\GT-10BFxFloorBoard\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\GT-10Bfxfloorboard.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\GT-10Bfxfloorboard.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\Saved Patches\vintage synth.syx"
  Delete "$INSTDIR\Saved Patches\venuspedal.syx"
  Delete "$INSTDIR\Saved Patches\Tool.syx"
  Delete "$INSTDIR\Saved Patches\the_Lone_Ranger.syx"
  Delete "$INSTDIR\Saved Patches\Talker_Twah_v1.syx"
  Delete "$INSTDIR\Saved Patches\synthdrive venus.syx"
  Delete "$INSTDIR\Saved Patches\super dooper.syx"
  Delete "$INSTDIR\Saved Patches\StoneBlue_Fuzzy.syx"
  Delete "$INSTDIR\Saved Patches\StoneBlue drive.syx"
  Delete "$INSTDIR\Saved Patches\StoneBlue Chorus.syx"
  Delete "$INSTDIR\Saved Patches\Stadium_Drive.syx"
  Delete "$INSTDIR\Saved Patches\spacebar.syx"
  Delete "$INSTDIR\Saved Patches\SOB SPACE S HOLD.syx"
  Delete "$INSTDIR\Saved Patches\SGX NGTBASS.syx"
  Delete "$INSTDIR\Saved Patches\sequencer circus.syx"
  Delete "$INSTDIR\Saved Patches\scoop slap.syx"
  Delete "$INSTDIR\Saved Patches\SansSamp Bassman.syx"
  Delete "$INSTDIR\Saved Patches\SansAmp SVT.syx"
  Delete "$INSTDIR\Saved Patches\SansAmp Fat Tube.syx"
  Delete "$INSTDIR\Saved Patches\Quick FX\QuickFX_010.syx"
  Delete "$INSTDIR\Saved Patches\Quick FX\QuickFX_009.syx"
  Delete "$INSTDIR\Saved Patches\Quick FX\QuickFX_008.syx"
  Delete "$INSTDIR\Saved Patches\Quick FX\QuickFX_007.syx"
  Delete "$INSTDIR\Saved Patches\Quick FX\QuickFX_006.syx"
  Delete "$INSTDIR\Saved Patches\Quick FX\QuickFX_005.syx"
  Delete "$INSTDIR\Saved Patches\Quick FX\QuickFX_004.syx"
  Delete "$INSTDIR\Saved Patches\Quick FX\QuickFX_003.syx"
  Delete "$INSTDIR\Saved Patches\Quick FX\QuickFX_002.syx"
  Delete "$INSTDIR\Saved Patches\Quick FX\QuickFX_001.syx"
  Delete "$INSTDIR\Saved Patches\pluckylightphase.syx"
  Delete "$INSTDIR\Saved Patches\ONE OF THES DAYS.syx"
  Delete "$INSTDIR\Saved Patches\My 810.syx"
  Delete "$INSTDIR\Saved Patches\mad scientist.syx"
  Delete "$INSTDIR\Saved Patches\Lets Groove.syx"
  Delete "$INSTDIR\Saved Patches\GEDDY YYZ CC Patch.syx"
  Delete "$INSTDIR\Saved Patches\Don't Stop.syx"
  Delete "$INSTDIR\Saved Patches\AC Bass.syx"
  Delete "$INSTDIR\Saved Patches\!FartBender_v1.syx"
  Delete "$INSTDIR\Saved Patches\!BassMurf_v1.syx"
  Delete "$INSTDIR\Saved Patches\!AutoSensWAH_v1.syx"
  Delete "$INSTDIR\Saved Patches\!AutoOrgan_v1.syx"
  Delete "$INSTDIR\Mid Patches\Tornado3DFeedback.mid"
  Delete "$INSTDIR\Mid Patches\the lone ranger.mid"
  Delete "$INSTDIR\Mid Patches\Quadravox.mid"
  Delete "$INSTDIR\Mid Patches\DoubleSoundHold.mid"
  Delete "$INSTDIR\Init Patches\StoneBlue drive.syx"
  Delete "$INSTDIR\Init Patches\SGX NGTBASS.syx"
  Delete "$INSTDIR\Init Patches\SansAmp SVT.syx"
  Delete "$INSTDIR\Init Patches\My 810.syx"
  Delete "$INSTDIR\Init Patches\012_Guitar Metal.syx"
  Delete "$INSTDIR\Init Patches\011_Guitar Drive.syx"
  Delete "$INSTDIR\Init Patches\010_Guitar Crunch.syx"
  Delete "$INSTDIR\Init Patches\009_Guitar Clean.syx"
  Delete "$INSTDIR\Init Patches\008_AC Bass.syx"
  Delete "$INSTDIR\Init Patches\007_Session.syx"
  Delete "$INSTDIR\Init Patches\006_Trace Elliot.syx"
  Delete "$INSTDIR\Init Patches\005_Bass 360.syx"
  Delete "$INSTDIR\Init Patches\004_Concert 810.syx"
  Delete "$INSTDIR\Init Patches\003_Fender BassMan.syx"
  Delete "$INSTDIR\Init Patches\002_Flip Top.syx"
  Delete "$INSTDIR\Init Patches\001_Super Flat.syx"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\Thumbs.db"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image038.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image035.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image034.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image033.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image031.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image030.jpg"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image028.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image027.jpg"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image026.jpg"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image025.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image024.jpg"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image023.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image022.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image021.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image020.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image019.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image018.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image017.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image016.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image015.jpg"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image014.jpg"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image013.jpg"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image013.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image012.jpg"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image012.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image011.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image010.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image009.jpg"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image009.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image008.jpg"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image008.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image007.jpg"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image007.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image006.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image005.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image004.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image003.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image002.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\image001.gif"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help_files\filelist.xml"
  Delete "$INSTDIR\GT-10Bfxfloorboard.exe"
  Delete "$INSTDIR\GT-10BFxFloorBoard_help.html"
  Delete "$INSTDIR\license.txt"
  Delete "$INSTDIR\mingwm10.dll"
  Delete "$INSTDIR\preferences.xml.dist"
  Delete "$INSTDIR\readme.txt"

  Delete "$SMPROGRAMS\GT-10BFxFloorBoard\Uninstall.lnk"
  Delete "$SMPROGRAMS\GT-10BFxFloorBoard\Website.lnk"
  Delete "$DESKTOP\GT-10BFxFloorBoard.lnk"
  Delete "$SMPROGRAMS\GT-10BFxFloorBoard\GT-10BFxFloorBoard.lnk"

  RMDir "$SMPROGRAMS\GT-10BFxFloorBoard"
  RMDir "$INSTDIR\Saved Patches\Quick FX"
  RMDir "$INSTDIR\Saved Patches"
  RMDir "$INSTDIR\Mid Patches"
  RMDir "$INSTDIR\Init Patches"
  RMDir "$INSTDIR\GT-10BFxFloorBoard_help_files"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd