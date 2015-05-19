% Compile and run camtest

%cd H:\Codes&Scripts\Combinator\mexFiles\pleora
% Compile
mex(['-L' pwd],'-lCyCamLib','-lCyUtilsLib','-lCyComLib',['-I' pwd],'pleora_acquireSingleImage.cpp')

% Run
a = pleora_acquireSingleImage(1,2);
size(a)