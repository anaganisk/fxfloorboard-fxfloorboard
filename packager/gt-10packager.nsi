; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "GT-10FxFloorBoard"
!define PRODUCT_VERSION "20090131"
!define PRODUCT_PUBLISHER "Gumtownbassman"
!define PRODUCT_WEB_SITE "http://gtx.tinfoilmusic.net"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\GT-10FxFloorBoard.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor lzma

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\orange-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\orange-uninstall.ico"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "license.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\GT-10FxFloorBoard.exe"
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\readme.txt"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"

; Reserve files
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "GT-10FxFloorBoard_Setup.exe"
InstallDir "$PROGRAMFILES\GT-10FxFloorBoard"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  Delete "$INSTDIR\preferences.xml"
  SetOverwrite ifnewer
  File "GT-10FxFloorBoard.exe"
  CreateDirectory "$SMPROGRAMS\GT-10FxFloorBoard"
  CreateShortCut "$SMPROGRAMS\GT-10FxFloorBoard\GT-10FxFloorBoard.lnk" "$INSTDIR\GT-10FxFloorBoard.exe"
  CreateShortCut "$DESKTOP\GT-10FxFloorBoard.lnk" "$INSTDIR\GT-10FxFloorBoard.exe"
  File "mingwm10.dll"
  File "license.txt"
  File "preferences.xml.dist"
  File "readme.txt"
  File "GT-10FxFloorBoard_Operation_Manual.pdf"
  File "GT-10FxFloorBoard_help.html"
  SetOutPath "$INSTDIR\GT-10FxFloorBoard_help_files"
  SetOverwrite try
  File "GT-10FxFloorBoard_help_files\image001.gif"
  File "GT-10FxFloorBoard_help_files\image002.gif"
  File "GT-10FxFloorBoard_help_files\image003.gif"
  File "GT-10FxFloorBoard_help_files\image004.gif"
  File "GT-10FxFloorBoard_help_files\image005.gif"
  File "GT-10FxFloorBoard_help_files\image006.gif"
  File "GT-10FxFloorBoard_help_files\image007.gif"
  File "GT-10FxFloorBoard_help_files\image008.gif"
  File "GT-10FxFloorBoard_help_files\image009.gif"
  File "GT-10FxFloorBoard_help_files\image010.gif"
  File "GT-10FxFloorBoard_help_files\image011.gif"
  File "GT-10FxFloorBoard_help_files\image013.jpg"
  File "GT-10FxFloorBoard_help_files\image014.jpg"
  File "GT-10FxFloorBoard_help_files\image015.jpg"
  File "GT-10FxFloorBoard_help_files\image016.jpg"
  File "GT-10FxFloorBoard_help_files\image016.gif"
  File "GT-10FxFloorBoard_help_files\image018.jpg"
  File "GT-10FxFloorBoard_help_files\image019.jpg"
  File "GT-10FxFloorBoard_help_files\image020.gif"
  SetOutPath "$INSTDIR\Init Patches"
  File "Init Patches\ACDC.syx"
  File "Init Patches\AndySummers.syx"
  File "Init Patches\Anthrax.syx"
  File "Init Patches\Antony.syx"
  File "Init Patches\BBKing.syx"
  File "Init Patches\BD_Clean.syx"
  File "Init Patches\BD_Clean_2.syx"
  File "Init Patches\BD_Crunch.syx"
  File "Init Patches\BD_Crunch_2.syx"
  File "Init Patches\BD_Lead.syx"
  File "Init Patches\BD_Lead_2.syx"
  File "Init Patches\BD_Marshall.syx"
  File "Init Patches\BD_Marshall_2.syx"
  File "Init Patches\Egin_1st.syx"
  File "Init Patches\dave's clean.syx"
  File "Init Patches\Dave's Lead.syx"
  File "Init Patches\EJ_1.syx"
  File "Init Patches\EJ_2.syx"
  File "Init Patches\eXPERIMENT.syx"
  File "Init Patches\EX_Marshall.syx"
  File "Init Patches\First_Blood.syx"
  File "Init Patches\GT-8_patch.syx"
  File "Init Patches\GT10patch.syx"
  File "Init Patches\Heavy_Scoop.syx"
  File "Init Patches\HR-HU_A(F_m)4-6.syx"
  File "Init Patches\JesseJ 001.syx"
  File "Init Patches\JesseJ 002.syx"
  File "Init Patches\John_J_Clean.syx"
  File "Init Patches\John_J_Crunch.syx"
  File "Init Patches\John_J_Drive.syx"
  File "Init Patches\John_J_Lead.syx"
  File "Init Patches\Marshall_MK_II_50W_combo.syx"
  File "Init Patches\Micycle.syx"
  File "Init Patches\MS_Hi_Gain_Brite.syx"
  File "Init Patches\MS_Hi_Gain_Normal.syx"
  File "Init Patches\NEWKILL.syx"
  File "Init Patches\Parrish Echos.syx"
  File "Init Patches\S-R_Endless_Sustain.syx"
  File "Init Patches\Scooped_and_Heavy.syx"
  File "Init Patches\Shimmer.syx"
  File "Init Patches\Spy_Knot.syx"
  File "Init Patches\super dooper.syx"
  File "Init Patches\tube screamer.syx"
  File "Init Patches\ugly.syx"
  File "Init Patches\Van_Halen.syx"
SectionEnd

Section -AdditionalIcons
  SetOutPath $INSTDIR
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\GT-10FxFloorBoard\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\GT-10FxFloorBoard\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\GT-10FxFloorBoard.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\GT-10FxFloorBoard.exe"
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
  Delete "$INSTDIR\Init Patches\Van_Halen.syx"
  Delete "$INSTDIR\Init Patches\ugly.syx"
  Delete "$INSTDIR\Init Patches\tube screamer.syx"
  Delete "$INSTDIR\Init Patches\super dooper.syx"
  Delete "$INSTDIR\Init Patches\Spy_Knot.syx"
  Delete "$INSTDIR\Init Patches\Shimmer.syx"
  Delete "$INSTDIR\Init Patches\Scooped_and_Heavy.syx"
  Delete "$INSTDIR\Init Patches\S-R_Endless_Sustain.syx"
  Delete "$INSTDIR\Init Patches\Parrish Echos.syx"
  Delete "$INSTDIR\Init Patches\NEWKILL.syx"
  Delete "$INSTDIR\Init Patches\MS_Hi_Gain_Normal.syx"
  Delete "$INSTDIR\Init Patches\MS_Hi_Gain_Brite.syx"
  Delete "$INSTDIR\Init Patches\Micycle.syx"
  Delete "$INSTDIR\Init Patches\Marshall_MK_II_50W_combo.syx"
  Delete "$INSTDIR\Init Patches\John_J_Lead.syx"
  Delete "$INSTDIR\Init Patches\John_J_Drive.syx"
  Delete "$INSTDIR\Init Patches\John_J_Crunch.syx"
  Delete "$INSTDIR\Init Patches\John_J_Clean.syx"
  Delete "$INSTDIR\Init Patches\JesseJ 002.syx"
  Delete "$INSTDIR\Init Patches\JesseJ 001.syx"
  Delete "$INSTDIR\Init Patches\HR-HU_A(F_m)4-6.syx"
  Delete "$INSTDIR\Init Patches\Heavy_Scoop.syx"
  Delete "$INSTDIR\Init Patches\GT10patch.syx"
  Delete "$INSTDIR\Init Patches\GT-8_patch.syx"
  Delete "$INSTDIR\Init Patches\First_Blood.syx"
  Delete "$INSTDIR\Init Patches\EX_Marshall.syx"
  Delete "$INSTDIR\Init Patches\eXPERIMENT.syx"
  Delete "$INSTDIR\Init Patches\EJ_2.syx"
  Delete "$INSTDIR\Init Patches\EJ_1.syx"
  Delete "$INSTDIR\Init Patches\Egin_1st.syx"
  Delete "$INSTDIR\Init Patches\dave's clean.syx"
  Delete "$INSTDIR\Init Patches\Dave's Lead.syx"
  Delete "$INSTDIR\Init Patches\BD_Marshall_2.syx"
  Delete "$INSTDIR\Init Patches\BD_Marshall.syx"
  Delete "$INSTDIR\Init Patches\BD_Lead_2.syx"
  Delete "$INSTDIR\Init Patches\BD_Lead.syx"
  Delete "$INSTDIR\Init Patches\BD_Crunch_2.syx"
  Delete "$INSTDIR\Init Patches\BD_Crunch.syx"
  Delete "$INSTDIR\Init Patches\BD_Clean_2.syx"
  Delete "$INSTDIR\Init Patches\BD_Clean.syx"
  Delete "$INSTDIR\Init Patches\BBKing.syx"
  Delete "$INSTDIR\Init Patches\Antony.syx"
  Delete "$INSTDIR\Init Patches\Anthrax.syx"
  Delete "$INSTDIR\Init Patches\AndySummers.syx"
  Delete "$INSTDIR\Init Patches\ACDC.syx"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image020.gif"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image019.jpg"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image018.jpg"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image016.gif"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image016.jpg"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image015.jpg"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image014.jpg"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image013.jpg"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image011.gif"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image010.gif"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image009.gif"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image008.gif"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image007.gif"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image006.gif"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image005.gif"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image004.gif"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image003.gif"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image002.gif"
  Delete "$INSTDIR\GT-10FxFloorBoard_help_files\image001.gif"
  Delete "$INSTDIR\GT-10FxFloorBoard_help.html"
  Delete "$INSTDIR\GT-10FxFloorBoard_Operation_Manual.pdf"
  Delete "$INSTDIR\readme.txt"
  Delete "$INSTDIR\preferences.xml.dist"
  Delete "$INSTDIR\license.txt"
  Delete "$INSTDIR\mingwm10.dll"
  Delete "$INSTDIR\GT-10FxFloorBoard.exe"
  Delete "$INSTDIR\preferences.xml"

  Delete "$SMPROGRAMS\GT-10FxFloorBoard\Uninstall.lnk"
  Delete "$SMPROGRAMS\GT-10FxFloorBoard\Website.lnk"
  Delete "$DESKTOP\GT-10FxFloorBoard.lnk"
  Delete "$SMPROGRAMS\GT-10FxFloorBoard\GT-10FxFloorBoard.lnk"

  RMDir "$SMPROGRAMS\GT-10FxFloorBoard"
  RMDir "$INSTDIR\Init Patches"
  RMDir "$INSTDIR\GT-10FxFloorBoard_help_files"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd