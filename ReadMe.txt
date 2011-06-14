winps

written by chroma

[説明]
Linuxのpsもどきプログラム
Windows XPでは手軽にコマンドで調べられなかった気がするので作ったと思う。
PSだけじゃナンなので、プロセスが使っているモジュールも出すようにして、
モジュールのフルパスも出すようにした。ちゃんとしたDLLを読んでるかチェックに使えるかも。

[使い方]
winps -p
現在走っているプロレスのリストを取得
PID 親PID スレッド数 イメージ名 の順で出る。
例；

C:\>winps -p
pid      ppid      ths     fname
       0        0        2 [System Process]
       4        0      128 System
     460        4        4 smss.exe
     528      516       11 csrss.exe
     580      516        3 wininit.exe
     592      572       11 csrss.exe
     624      580        5 services.exe
     640      580       11 lsass.exe
     648      580       10 lsm.exe
     724      572        3 winlogon.exe


winps -m PID
PIDに指定されたプロセスIDが使っているDLLやらを表示する
マップアドレス サイズ イメージ名 イメージのフルパス の順で出る。
例；
C:\>winps -m 3156
4AC20000 00050000 cmd.exe C:\Windows\System32\cmd.exe
77CB0000 00128000 ntdll.dll C:\Windows\system32\ntdll.dll
771C0000 000DC000 kernel32.dll C:\Windows\system32\kernel32.dll
772A0000 000C6000 ADVAPI32.dll C:\Windows\system32\ADVAPI32.dll
77500000 000C3000 RPCRT4.dll C:\Windows\system32\RPCRT4.dll
778E0000 000AA000 msvcrt.dll C:\Windows\system32\msvcrt.dll
76180000 0002C000 apphelp.dll C:\Windows\system32\apphelp.dll


