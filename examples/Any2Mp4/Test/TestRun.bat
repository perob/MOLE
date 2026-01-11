@echo off
set input="..\..\..\media\samples\sample.wav"
set voice="..\..\..\media\voice\voice-16b-1c-16000hz.wav"
set any2mp4="..\Builds\VisualStudio2022\x64\Debug\ConsoleApp\Any2Mp4.exe"

%any2mp4% --mp4 %input% sample.m4a
%any2mp4% --mp3 %input% sample.mp3
%any2mp4% --mp2 %input% sample.mp2
%any2mp4% --mp1 %input% sample.mp1
%any2mp4% --flac %input% sample.flac.mp4
%any2mp4% --wma8 %input% sample.wma8.wma
%any2mp4% --wma9 %input% sample.wma9.wma
%any2mp4% --wmal %input% sample.wmaL.wma
%any2mp4% --wmsp %voice% sample.wmsp.wma
rem %any2mp4% --ac3 %input% sample.ac3
