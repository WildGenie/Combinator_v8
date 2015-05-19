% VIPA image smoothing test
clear all
data = load('H:\Mid_IR_Data\temp\March11_ODSearch\ODSearch.csv_50.mat');

imgArray = reshape(data.imgArray,[],300);
bkgImages = reshape(data.bkgImageA,[],3);
bkgImage = double(reshape(bkgImages(:,2),320,256));
bkgImage(nanIndexTranspose(data.badPixelIndcs,256,320)) = NaN;
refImage = double(reshape(imgArray(:,100),320,256));
refImage(nanIndexTranspose(data.badPixelIndcs,256,320)) = NaN;
sigImage = double(reshape(imgArray(:,101),320,256));
sigImage(nanIndexTranspose(data.badPixelIndcs,256,320)) = NaN;
theImage = sigImage - bkgImage;
for i = 1:size(theImage,1)
   theImage(i,:) = smooth(theImage(i,:),5);
end
a = (theImage-(sigImage-bkgImage))./theImage;
b = (refImage-sigImage)./refImage;
figure;plot(1e4./data.spectrumX,nanindex(a,data.spectrumIndcs));
figure;plot(1e4./data.spectrumX,nanindex(b,data.spectrumIndcs));

%%
plotIndcsOnImage(refImage-bkgImage,data.spectrumIndcs);
refCollapse = VIPAcollapse(refImage-bkgImage,data.spectrumIndcs,2,0);
sigCollapse = VIPAcollapse(sigImage-bkgImage,data.spectrumIndcs,2,0);
c = sigCollapse./refCollapse;
figure;plot(1e4./data.spectrumX,nanindex(b,data.spectrumIndcs));

%%
d = (sigImage-bkgImage)./(refImage-bkgImage);
figure;plot(1e4./data.spectrumX,nanindex(b,data.spectrumIndcs));

%%
[filename,filepath] = uigetfile('*.mat',sprintf('Load files...'),'MultiSelect', 'on');
if ~isequal(filename,0) && ~isequal(filepath,0)
   filenames = fullfile(filepath,filename);
else
    error('You must pick a file')
end
%filenames = filenames(1);

% Sort out the filenames of spectra
spectrumFilenames = struct([]);
for i = 1:numel(filenames)
    if isempty(findstr(filenames{i},'_RAWimages'))
        spectrumFilenames{end+1} = filenames{i};
    end
end
%
%filenames = {'H:\temp\March20_ODdata\odsearch4.csv_0.mat'};
%
%
sumSpectrum = 0;
avgNums = 0;
imgNums = [99 101 102];
for i = 1:numel(spectrumFilenames)
    data = load(spectrumFilenames{i});
    fprintf('Averaging Number %i\n',i);
    
    if i == 1
       spectrumX = data.spectrumX; 
    end
    
    bkgSpectrum = data.bkgSpectra(:,:,1);
    bkgSpectrum(bkgSpectrum > 1.25*nanmean(bkgSpectrum(:))) = NaN;
    bkgSpectrum(bkgSpectrum < 0.75*nanmean(bkgSpectrum(:))) = NaN;
    
     theSpectraMinusBKG = double(data.theSpectra) - double(repmat(bkgSpectrum,[1 1 size(data.theSpectra,3)]));
     theSpectraMinusBKG(theSpectraMinusBKG < 50) = NaN;

     for j = 1:numel(imgNums)
         specOutA = 1-contructNormSpectrumV4(theSpectraMinusBKG,100,imgNums(j),3);
         if i == 1
             specOut = zeros(numel(specOutA),numel(imgNums));
         end
         specOut(:,j) = specOutA(:);
     end

    if sumSpectrum == 0
        sumSpectrum = zeros(size(specOut));
        avgNums = zeros(size(specOut));
    end
    %sumSpectrum(~isnan(specOut)) = sumSpectrum(~isnan(specOut)) + specOut(~isnan(specOut));
    sumSpectrum = sumSpectrum + specOut;
    avgNums = avgNums + 1;%~isnan(specOut);
end
%
offset = 0.02;
spacing = 0.02;
h=figure;
colors = {'b','r','g'};
for j = 1:numel(imgNums)
    plot(1e4./spectrumX(:),sumSpectrum(:,j)./avgNums(:,j)+spacing*(j-2)+offset,colors{j});
    if j == 1
       hold on; 
    end
end
legend('8 ms Before YAG','Right After YAG','4 ms After YAG');