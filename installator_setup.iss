; This setup script is compiled with Inno Setup Compiler version 5.5.9
; See: http://www.jrsoftware.org/

#define AppVersion    "1.0.0"
#define AppName       "JPEGXL-WIC"
#define AppPublisher  "Mirillis"

[Setup]
AppName =                           "{#AppName}"
AppVerName =                        "{#AppName} {#AppVersion}"
AppCopyright =                      ""
AppPublisher =                      "{#AppPublisher}"
AppPublisherURL =                   ""
AppVersion =                        "{#AppVersion}"
DefaultDirName =                    "{commonpf}\{#AppPublisher}\{#AppName}"
DirExistsWarning =                  no
DisableStartupPrompt =              yes
DisableWelcomePage =                yes
DisableDirPage =                    yes
DisableProgramGroupPage =           yes
SourceDir =                         ".\release\bin\x86_64"
OutputBaseFilename =                "jpegxl_wic_setup"
OutputDir =                         "."
UninstallDisplayIcon =              "{app}\jxlwic.dll"
UninstallDisplayName =              "{#AppName}"
MinVersion =                        6.1
ArchitecturesAllowed =              x64
ArchitecturesInstallIn64BitMode =   x64
PrivilegesRequired =                admin
ChangesAssociations =               yes

[Files]
; x64
Source: "jxlwic.dll"; DestDir: "{app}"; Flags: ignoreversion regserver restartreplace uninsrestartdelete
Source: "jxl.dll"; DestDir: "{app}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "jxl_threads.dll"; DestDir: "{app}"; Flags: ignoreversion restartreplace uninsrestartdelete

[Registry]
; WIC Registry Entries
; - https://msdn.microsoft.com/en-us/library/windows/desktop/ee719880(v=vs.85).aspx

;------------------------------------------------------------
; WIC DECODER - X86
;------------------------------------------------------------
Root: HKCR; Subkey: "CLSID\{{7ED96837-96F0-4812-B211-F13C24117ED3}\Instance\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}"; Flags: uninsdeletekey
Root: HKCR; Subkey: "CLSID\{{7ED96837-96F0-4812-B211-F13C24117ED3}\Instance\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}"; ValueType: string; ValueName: "CLSID"; ValueData: "{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}";
Root: HKCR; Subkey: "CLSID\{{7ED96837-96F0-4812-B211-F13C24117ED3}\Instance\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}"; ValueType: string; ValueName: "FriendlyName"; ValueData: "Mirillis JPEG XL Decoder";

Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}"; Flags: uninsdeletekey
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}"; ValueType: string; ValueName: ""; ValueData: "Mirillis JPEG XL Decoder";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}"; ValueType: string; ValueName: "Author"; ValueData: "{#AppPublisher}";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}"; ValueType: string; ValueName: "Description"; ValueData: "Mirillis JPEG XL Decoder";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}"; ValueType: string; ValueName: "FileExtensions"; ValueData: ".jxl";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}"; ValueType: string; ValueName: "FriendlyName"; ValueData: "Mirillis JPEG XL Decoder";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}"; ValueType: string; ValueName: "ContainerFormat"; ValueData: "{{32FEBF67-29D8-4643-BE1E-5F279F6BD7C6}";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}"; ValueType: string; ValueName: "Vendor"; ValueData: "{{8897BFED-CDE6-40AA-9571-4883EF4208B5}";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}"; ValueType: string; ValueName: "Version"; ValueData: "{#AppVersion}";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}"; ValueType: string; ValueName: "MimeTypes"; ValueData: "image/jxl";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}"; ValueType: dword;  ValueName: "SupportAnimation";  ValueData: "0";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}"; ValueType: dword;  ValueName: "SupportChromaKey";  ValueData: "0";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}"; ValueType: dword;  ValueName: "SupportLossless";   ValueData: "1";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}"; ValueType: dword;  ValueName: "SupportMultiframe"; ValueData: "0";

Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}\Formats\{{F5C7AD2D-6A8D-43DD-A7A8-A29935261AE9}";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}\Formats\{{9C215C5D-1ACC-4F0E-A4BC-70FB3AE8FD28}";

Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}\InprocServer32";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}\InprocServer32"; ValueType: string; ValueName: ""; ValueData: "{app}\jxlwic.dll";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}\InprocServer32"; ValueType: string; ValueName: "ThreadingModel"; ValueData: "Both";

Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}\Patterns\0";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}\Patterns\0"; ValueType: dword; ValueName: "Position"; ValueData: "0";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}\Patterns\0"; ValueType: dword; ValueName: "Length"; ValueData: "2";
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}\Patterns\0"; ValueType: binary; ValueName: "Pattern"; ValueData: "FF 0A"
Root: HKCR; Subkey: "CLSID\{{0AF8C503-8682-4FBD-AA76-22F7E5567A4F}\Patterns\0"; ValueType: binary; ValueName: "Mask"; ValueData: "FF FF";

;------------------------------------------------------------
; INTEGRTION WITH WINDOWS EXPLORER
;------------------------------------------------------------
Root: HKCR; Subkey: ".jxl"; Flags: uninsdeletekeyifempty
Root: HKCR; Subkey: ".jxl"; ValueType: string; ValueName: ""; ValueData: "mirillisjxl"; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".jxl"; ValueType: string; ValueName: "Content Type"; ValueData: "image/jxl"; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".jxl"; ValueType: string; ValueName: "PerceivedType"; ValueData: "image"; Flags: uninsdeletevalue

;-- INTEGRATION WITH THE WINDOWS PHOTO GALLERY
Root: HKCR; Subkey: ".jxl\OpenWithProgids"; Flags: uninsdeletekeyifempty
Root: HKCR; Subkey: ".jxl\OpenWithProgids"; ValueType: string; ValueName: "mirillisjxl"; ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".jxl\OpenWithList\PhotoViewer.dll"; Flags: uninsdeletekeyifempty
Root: HKCR; Subkey: ".jxl\shellex\ContextMenuHandlers\ShellImagePreview"; Flags: uninsdeletekeyifempty
Root: HKCR; Subkey: ".jxl\shellex\ContextMenuHandlers\ShellImagePreview"; ValueType: string; ValueName: ""; ValueData: "{{FFE2A43C-56B9-4bf5-9A79-CC6D4285608A}"; Flags: uninsdeletevalue
Root: HKCR; Subkey: "SystemFileAssociations\.jxl\OpenWithList\PhotoViewer.dll"; Flags: uninsdeletekeyifempty
Root: HKCR; Subkey: "SystemFileAssociations\.jxl\shellex\ContextMenuHandlers\ShellImagePreview"; Flags: uninsdeletekeyifempty
Root: HKCR; Subkey: "SystemFileAssociations\.jxl\shellex\ContextMenuHandlers\ShellImagePreview"; ValueType: string; ValueName: ""; ValueData: "{{FFE2A43C-56B9-4bf5-9A79-CC6D4285608A}"; Flags: uninsdeletevalue
Root: HKCR; Subkey: "mirillisjxl"; Flags: uninsdeletekey
Root: HKCR; Subkey: "mirillisjxl"; ValueType: string; ValueName: ""; ValueData: "JpegXL Image"
Root: HKCR; Subkey: "mirillisjxl\shell\open";
Root: HKCR; Subkey: "mirillisjxl\shell\open"; ValueType: expandsz; ValueName: "MuiVerb"; ValueData: "@%ProgramFiles%\Windows Photo Viewer\photoviewer.dll,-3043"
Root: HKCR; Subkey: "mirillisjxl\shell\open\command";
Root: HKCR; Subkey: "mirillisjxl\shell\open\command"; ValueType: expandsz; ValueName: ""; ValueData: "%SystemRoot%\System32\rundll32.exe ""%ProgramFiles%\Windows Photo Viewer\PhotoViewer.dll"", ImageView_Fullscreen %1"
Root: HKCR; Subkey: "mirillisjxl\shell\open\DropTarget";
Root: HKCR; Subkey: "mirillisjxl\shell\open\DropTarget"; ValueType: string; ValueName: "Clsid"; ValueData: "{{FFE2A43C-56B9-4bf5-9A79-CC6D4285608A}";

;-- INTERGRATION WITH THE WINDOWS THUMBNAIL CACHE (WINDOWS PHOTO GALLERY)
Root: HKCR; Subkey: ".jxl\shellex\{{e357fccd-a995-4576-b01f-234630154e96}"; Flags: uninsdeletekeyifempty
Root: HKCR; Subkey: ".jxl\shellex\{{e357fccd-a995-4576-b01f-234630154e96}"; ValueType: string; ValueName: ""; ValueData: "{{C7657C4A-9F68-40fa-A4DF-96BC08EB3551}"; Flags: uninsdeletevalue
Root: HKCR; Subkey: "SystemFileAssociations\.jxl\shellex\{{e357fccd-a995-4576-b01f-234630154e96}"; Flags: uninsdeletekeyifempty
Root: HKCR; Subkey: "SystemFileAssociations\.jxl\shellex\{{e357fccd-a995-4576-b01f-234630154e96}"; ValueType: string; ValueName: ""; ValueData: "{{C7657C4A-9F68-40fa-A4DF-96BC08EB3551}"; Flags: uninsdeletevalue

;-- REGISTERING PROPERTY HANDLER
Root: HKCR; Subkey: "CLSID\{{5CC0FB5D-9564-4BE6-A6FD-8BA365D813EB}"; Flags: uninsdeletekey
Root: HKCR; Subkey: "CLSID\{{5CC0FB5D-9564-4BE6-A6FD-8BA365D813EB}"; ValueType: string; ValueName: ""; ValueData: "PropertyHandler";
Root: HKCR; Subkey: "CLSID\{{5CC0FB5D-9564-4BE6-A6FD-8BA365D813EB}"; ValueType: dword; ValueName: "ManualSafeSave"; ValueData: "1";
Root: HKCR; Subkey: "CLSID\{{5CC0FB5D-9564-4BE6-A6FD-8BA365D813EB}\InprocServer32";
Root: HKCR; Subkey: "CLSID\{{5CC0FB5D-9564-4BE6-A6FD-8BA365D813EB}\InprocServer32"; ValueType: string; ValueName: ""; ValueData: "{app}\jxlwic.dll";
Root: HKCR; Subkey: "CLSID\{{5CC0FB5D-9564-4BE6-A6FD-8BA365D813EB}\InprocServer32"; ValueType: string; ValueName: "ThreadingModel"; ValueData: "Apartment";
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Windows\CurrentVersion\PropertySystem\PropertyHandlers\.jxl"; ValueType: string; ValueName: ""; ValueData: "{{5CC0FB5D-9564-4BE6-A6FD-8BA365D813EB}"; Flags: uninsdeletekey

;-- INTEGRATION WITH WINDOWS EXPLORER KIND PROPERTY
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\KindMap"; ValueType: string; ValueName: ".jxl"; ValueData: "picture";
