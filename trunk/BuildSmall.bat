SET PATH=C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x86;C:\Program Files\Microsoft SDKs\Windows\v6.1\Lib
Tools\crinkler.exe /OUT:intro.exe /SUBSYSTEM:WINDOWS /COMPMODE:SLOW /ORDERTRIES:1000 /VERBOSE:IMPORTS /VERBOSE:LABELS kernel32.lib user32.lib winmm.lib d3d10.lib d3dx10d.lib output\Window.obj
copy /B /Y Intro.exe Final\Intro.exe

