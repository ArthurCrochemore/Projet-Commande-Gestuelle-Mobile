@echo off
SetLocal EnableDelayedExpansion
(set PATH=C:\Qt\5.15.18\msvc2019_64\bin;!PATH!)
if defined QT_PLUGIN_PATH (
    set QT_PLUGIN_PATH=C:\Qt\5.15.18\msvc2019_64\plugins;!QT_PLUGIN_PATH!
) else (
    set QT_PLUGIN_PATH=C:\Qt\5.15.18\msvc2019_64\plugins
)
%*
EndLocal
