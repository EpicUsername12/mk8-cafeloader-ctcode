@echo off
python compiler_cemu.py files MK8_ALL_Latest_Cemu Turbo_ORIG.rpx
cp Turbo.rpx "F:\WiiU\DATA\EMULATORS\Cemu\BIN\mlc01\usr\title\0005000e\1010ed00\code\Turbo.rpx"
"F:\WiiU\DATA\EMULATORS\Cemu\BIN\Cemu.exe"