% Compile and run camtest

% Clear old function
clear pleora_acquireMultipleImagesPersistent

%cd H:\Codes&Scripts\Combinator\mexFiles\pleora
% Compile
mex(['-L' pwd],'-lCyCamLib','-lCyUtilsLib','-lCyComLib',['-I' pwd],'pleora_acquireMultipleImagesPersistent.cpp')

% Run
%a = pleora_acquireMultipleImagesPersistent(uint16(64),uint16(4),uint16(1));
b = pleora_acquireMultipleImagesPersistent(uint16(320),uint16(256),uint16(1));
return
%c = pleora_acquireMultipleImagesPersistent(uint16(2),uint16(320),uint16(256),uint16(1));
d = pleora_acquireMultipleImagesPersistent(uint16(3),uint16(320),uint16(256),uint16(1));
size(a)
size(b)