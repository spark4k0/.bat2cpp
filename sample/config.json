

@echo off
title Ultra Fortnite FPS Boost 2024
echo ================================================
echo         Ultra Fortnite FPS Boost     
echo ================================================
echo Dieses Skript wird Ihr Fortnite System optimieren.
pause

:: =========================
:: Prozess-Priorität erhöhen
:: =========================
echo Setze Fortnite.exe auf hohe Priorität
wmic process where name="FortniteClient-Win64-Shipping.exe" CALL setpriority "high priority"

:: =========================
:: Visuelle Effekte minimieren
:: =========================
echo Minimierung der visuellen Effekte

reg add "HKCU\Control Panel\Desktop" /v DragFullWindows /t REG_SZ /d 0 /f
reg add "HKCU\Control Panel\Desktop" /v FontSmoothing /t REG_SZ /d 2 /f
reg add "HKCU\Control Panel\Desktop" /v MenuShowDelay /t REG_SZ /d 0 /f
reg add "HKCU\Control Panel\Desktop" /v SmoothScroll /t REG_SZ /d 0 /f
reg add "HKCU\Control Panel\Desktop" /v UserPreferencesMask /t REG_BINARY /d 9012038080000000 /f
reg add "HKCU\Control Panel\Desktop" /v CursorShadow /t REG_SZ /d 0 /f

:: Deaktivieren der Transparenzeffekte
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Themes\Personalize" /v EnableTransparency /t REG_DWORD /d 0 /f

:: Deaktivieren von Animationen
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced" /v DisablePreviewWindow /t REG_DWORD /d 1 /f

:: Schatten unter Fenstern deaktivieren
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced" /v ListviewShadow /t REG_DWORD /d 0 /f

:: Aero Peek deaktivieren
reg add "HKCU\Software\Microsoft\Windows\DWM" /v EnableAeroPeek /t REG_DWORD /d 0 /f

:: =========================
:: Energieoptionen optimieren
:: =========================
echo Setze Energieoptionen auf Höchstleistung
powercfg -duplicatescheme e9a42b02-d5df-448d-aa00-03f14749eb61

:: CPU-Performance-Modus aktivieren
reg add "HKLM\SYSTEM\CurrentControlSet\Control\Power\PowerThrottling" /v PowerThrottlingOff /t REG_DWORD /d 1 /f

:: Festplatten-Ruhemodus deaktivieren
powercfg -change -disk-timeout-ac 0
powercfg -change -disk-timeout-dc 0

:: Energieoptionen für PCI Express anpassen
powercfg -setacvalueindex SCHEME_CURRENT SUB_PCIE EXPRESSV 0

:: =========================
:: Unnötige Dienste deaktivieren
:: =========================
echo Deaktivierung unnötiger Dienste

:: SysMain (Superfetch)
sc config "SysMain" start=disabled
sc stop "SysMain"

:: Windows-Suche
sc config "WSearch" start=disabled
sc stop "WSearch"

:: Windows Update
sc config "wuauserv" start=disabled
sc stop "wuauserv"

:: Remote Desktop Services
sc config "TermService" start=disabled
sc stop "TermService"

:: Xbox-Dienste
sc config "XblAuthManager" start=disabled
sc stop "XblAuthManager"
sc config "XblGameSave" start=disabled
sc stop "XblGameSave"
sc config "XboxNetApiSvc" start=disabled
sc stop "XboxNetApiSvc"

:: DiagTrack
sc config "DiagTrack" start=disabled
sc stop "DiagTrack"

:: Print Spooler (wenn kein Drucker verwendet wird)
sc config "Spooler" start=disabled
sc stop "Spooler"

:: Windows Defender (nicht empfohlen, wenn kein alternativer Schutz vorhanden ist)
reg add "HKLM\SOFTWARE\Policies\Microsoft\Windows Defender" /v DisableAntiSpyware /t REG_DWORD /d 1 /f

:: Windows Error Reporting deaktivieren
sc config "WerSvc" start=disabled
sc stop "WerSvc"

:: Geolocation-Dienst deaktivieren
sc config "lfsvc" start=disabled
sc stop "lfsvc"

:: Bluetooth deaktivieren (falls nicht verwendet)
sc config "bthserv" start=disabled
sc stop "bthserv"

:: Dienste für Windows-Medienfreigabe deaktivieren
sc config "WMPNetworkSvc" start=disabled
sc stop "WMPNetworkSvc"

:: Hyper-V deaktivieren (falls nicht verwendet)
dism.exe /Online /Disable-Feature:Microsoft-Hyper-V-All

:: Remote Registry deaktivieren
sc config "RemoteRegistry" start=disabled
sc stop "RemoteRegistry"

:: Offline Files deaktivieren
sc config "CscService" start=disabled
sc stop "CscService"

:: Geplanten Aufgaben für Leistung optimieren
schtasks /Change /TN "\Microsoft\Windows\UpdateOrchestrator\Schedule Scan" /Disable
schtasks /Change /TN "\Microsoft\Windows\Customer Experience Improvement Program\Consolidator" /Disable
schtasks /Change /TN "\Microsoft\Windows\DiskDiagnostic\Microsoft-Windows-DiskDiagnosticDataCollector" /Disable
schtasks /Change /TN "\Microsoft\Windows\Application Experience\AitAgent" /Disable
schtasks /Change /TN "\Microsoft\Windows\Application Experience\ProgramDataUpdater" /Disable
schtasks /Change /TN "\Microsoft\Windows\Autochk\Proxy" /Disable
schtasks /Change /TN "\Microsoft\Windows\Customer Experience Improvement Program\UsbCeip" /Disable

:: =========================
:: Netzwerkoptimierungen
:: =========================
echo Netzwerkoptimierungen werden angewendet

:: Autotuning deaktivieren
netsh interface tcp set global autotuninglevel=disabled

:: TCP Chimney Offload deaktivieren
netsh int tcp set global chimney=disabled

:: TCP Timestamps deaktivieren
netsh int tcp set global timestamps=disabled

:: TCP Ack Frequency anpassen
netsh int tcp set global ackfrequency=1

:: RSS (Receive Side Scaling) aktivieren
netsh int tcp set global rss=enabled

:: Direct Cache Access (DCA) aktivieren
netsh int tcp set global dca=enabled

:: Windows Update Bandbreitenbeschränkung einstellen
reg add "HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\DeliveryOptimization\Config" /v MaxDownloadLimit /t REG_DWORD /d 10 /f

:: DNS-Cache leeren
ipconfig /flushdns

:: Alte Netzwerktreiber löschen
pnputil.exe /delete-driver * /uninstall /force

:: Netzwerkadapter neu starten
netsh interface set interface name="Ethernet" admin=disable
netsh interface set interface name="Ethernet" admin=enable

:: =========================
:: Speicheroptimierungen
:: =========================
echo Speicheroptimierungen werden angewendet

:: Virtuellen Speicher anpassen
wmic computersystem where name="%computername%" set AutomaticManagedPagefile=False
wmic pagefileset where name="C:\\pagefile.sys" set InitialSize=4096,MaximumSize=4096

:: Prefetch deaktivieren
reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management\PrefetchParameters" /v EnablePrefetcher /t REG_DWORD /d 0 /f
reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management\PrefetchParameters" /v EnableSuperfetch /t REG_DWORD /d 0 /f

:: Auslagerungsdatei deaktivieren (falls genügend RAM vorhanden ist)
reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" /v PagingFiles /t REG_MULTI_SZ /d "" /f

:: Speicherverdichtung deaktivieren
reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" /v DisablePagingExecutive /t REG_DWORD /d 1 /f

:: ClearPageFileAtShutdown deaktivieren
reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" /v ClearPageFileAtShutdown /t REG_DWORD /d 0 /f

:: LargeSystemCache deaktivieren
reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" /v LargeSystemCache /t REG_DWORD /d 0 /f

:: =========================
:: Windows-Explorer-Optimierungen
:: =========================
echo Windows-Explorer-Optimierungen werden angewendet

:: Thumbnails deaktivieren
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced" /v DisableThumbnailCache /t REG_DWORD /d 1 /f

:: Quick Access deaktivieren
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced" /v LaunchTo /t REG_DWORD /d 1 /f

:: Recent Items deaktivieren
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced" /v Start_TrackDocs /t REG_DWORD /d 0 /f

:: Datei-Explorer optimieren
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced" /v SeparateProcess /t REG_DWORD /d 1 /f
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced" /v ShowSyncProviderNotifications /t REG_DWORD /d 0 /f

:: =========================
:: Temporäre Dateien bereinigen
:: =========================
echo Bereinigen von temporären Dateien

del /q /s %temp%\*

:: Windows-Temp-Ordner leeren
del /q /s C:\Windows\Temp\*

:: =========================
:: Registry-Optimierungen
:: =========================
echo Registry-Optimierungen werden angewendet

:: Desktop Cleanup Wizard deaktivieren
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\Desktop\CleanupWiz" /v NoRun /t REG_DWORD /d 1 /f

:: Automatische Neustarts deaktivieren
reg add "HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\WindowsUpdate\Auto Update" /v NoAutoRebootWithLoggedOnUsers /t REG_DWORD /d 1 /f

:: Prefetch und Superfetch deaktivieren
reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management\PrefetchParameters" /v EnablePrefetcher /t REG_DWORD /d 0 /f
reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management\PrefetchParameters" /v EnableSuperfetch /t REG_DWORD /d 0 /f

:: Wartezeit beim Herunterfahren reduzieren
reg add "HKLM\SYSTEM\CurrentControlSet\Control" /v WaitToKillServiceTimeout /t REG_SZ /d 2000 /f

:: Benutzerkontensteuerung (UAC) deaktivieren
reg add "HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System" /v EnableLUA /t REG_DWORD /d 0 /f

:: =========================
:: Explorer neu starten
:: =========================
echo Neustart des Explorers
taskkill /f /im explorer.exe
start explorer.exe

echo Optimierungen abgeschlossen! Fortnite sollte jetzt besser laufen.
pause
exit
