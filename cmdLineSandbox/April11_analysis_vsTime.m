%%

% handle to MOD_TimeDynamics is h

filebase = '\\\\ftcombdaq\\Mid_IR_Data\\temp\\April5\\Trial10_';
fileext = '.rawSpectra';
wavenumFile = '\\\\ftcombdaq\\Mid_IR_Data\\temp\\April5\\COtests_afterRefresh\\CO_FittedWavenumAxis_April10.avgSpectra';

startNums = 0:30:329;
c = zeros(size(startNums));
fwhm = zeros(size(startNums));
area = zeros(size(startNums));
for i = 1:numel(startNums)
    filenames = {};
    for j = 0:29
       filenames{j+1} = sprintf('%s%i%s',filebase,startNums(i)+j,fileext); 
    end

    h.loadSpectraFromFiles('filenames',filenames);
    h.fitAveragedSpectraToPolynomial('fitNums',26);
    h.loadWavenumAxisFromAveragedSpectraFile('filename',wavenumFile);
    [c(i),fwhm(i),area(i)] = h.fitGaussianLineshape('interactive',true);%false);
end

%% Make Plot 
timeDelay = (0:(numel(startNums)-1))*100+25;
F = 2000;
Leff = 6;
conc = area/2.02e-20/F/Leff*pi;
figure;scatter(timeDelay,conc)
title(sprintf('Line at %f',c(1)))