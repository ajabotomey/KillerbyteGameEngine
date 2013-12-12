@echo off
chdir %KILLERBYTE_DROID%
ndk-build clean
ndk-build;
chdir %TESTPROJECT%
ndk-build clean
ndk-build;