%%

% handle to MOD_TimeDynamics is h

filebase = '\\\\ftcombdaq\\Mid_IR_Data\\temp\\April5\\COtests_afterRefresh\\Try1_';
fileext = '.rawSpectra';
wavenumFile = '\\\\ftcombdaq\\Mid_IR_Data\\temp\\April5\\COtests_afterRefresh\\CO_FittedWavenumAxis_April10.avgSpectra';

startNums = 0:100:4000;
c = zeros(size(startNums));
fwhm = zeros(size(startNums));
area = zeros(size(startNums));
for i = 1%:numel(startNums)
    filenames = {};
    for j = 0:29
       filenames{j+1} = sprintf('%s%i%s',filebase,startNums(i)+j,fileext); 
    end

    h.loadSpectraFromFiles('filenames',filenames);
    h.fitAveragedSpectraToPolynomial('fitNums',26);
    h.loadWavenumAxisFromAveragedSpectraFile('filename',wavenumFile);
    [c(i),fwhm(i),area(i)] = h.fitGaussianLineshape();%'interactive',false);
end

%% Get dates
filebase = 'H:\temp\April5\COtests_afterRefresh\Try1_';
fileext = '.rawSpectra';
dates = zeros(size(startNums));
for i = 1:numel(startNums)
   filename = sprintf('%s%i%s',filebase,startNums(i),fileext);
   fileInfo = dir(filename);
   dates(i) = fileInfo.datenum;
end

%% Get data from log file
DateString = '01-Jan-1904 00:00:00';
formatIn = 'dd-mmm-yyyy HH:MM:SS';
labviewDateBase = datenum(DateString,formatIn)-6/24;
data = dlmread('\\\\ftcombdaq\\Mid_IR_Data\\temp\\April3_0.dat','\t');
ozoneTime = data(:,1)/3600/24 + labviewDateBase; % Convert labview time to days
ozoneValue = data(:,3);

%% Get interpolated ozone values
ozoneValueInterp = interp1(ozoneTime,ozoneValue,dates);

%% Plot it
figure;plot(dates,ozoneValueInterp);
figure;plot(ozoneValueInterp,area/2.02e-20/2000/6*pi);
figure;hax = plotyy((dates-min(dates))*24*60,area/5.3e-17,(dates-min(dates))*24*60,ozoneValueInterp*3.22e16);