SET PATH=C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x86;C:\Program Files\Microsoft SDKs\Windows\v7.1\Lib
Tools\crinkler13\crinkler.exe /OUT:intro.exe /SUBSYSTEM:WINDOWS /COMPMODE:FAST /ORDERTRIES:1000 /PRINT:IMPORTS /PRINT:LABELS kernel32.lib user32.lib winmm.lib d3d10.lib d3dx10d.lib output\Window.obj
copy /B /Y Intro.exe Final\Intro.exe

