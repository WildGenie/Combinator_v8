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
sumSpectrum = 0;
imgNum = 101;
avgNums = 1:100;
for i = avgNums
    clear data
    data = load(sprintf('\\\\ftcombdaq\\Mid_IR_Data\\temp\\March11_ODSearch\\ODSearch.csv_%i.mat',i));
    fprintf('Averaging %i\n',i);
    
    imgArray = reshape(data.imgArray,[],300);
    bkgImages = reshape(data.bkgImageA,[],3);
    bkgImage = double(reshape(bkgImages(:,2),320,256));
    bkgImage(nanIndexTranspose(data.badPixelIndcs,256,320)) = NaN;
    refImage = double(reshape(imgArray(:,100),320,256));
    refImage(nanIndexTranspose(data.badPixelIndcs,256,320)) = NaN;
    sigImage = double(reshape(imgArray(:,imgNum),320,256));
    sigImage(nanIndexTranspose(data.badPixelIndcs,256,320)) = NaN;

    fringeIndcs = data.spectrumIndcs;
    numfringes = 39;%2*sum(diff(fringeIndcs) > 10);
    % if round(pixelsPerFringe) ~= pixelsPerFringe
    %    error('Pixels per fringe is not integer') 
    % end
    fringes = reshape(fringeIndcs,[],numfringes);

    image = (refImage-bkgImage);
    spectrumOutRef = zeros(size(fringes));
    for j = 1:numfringes
        % Get the fringe Indices
        [I,J] = ind2sub(size(image),fringes(:,j));
        fringesRounded = sub2ind(size(image),round(I),round(J));
        % Fringe is along I. We'll fit the amplitude first
        Afit = double(image(fringesRounded(~isnan(fringesRounded))));
        ppA = polyfit(J(~isnan(fringesRounded)),Afit,6);
        spectrumOutRef(:,j) = nanindex(image,fringesRounded)./polyval(ppA,J);
    end

    image = (sigImage-bkgImage);
    spectrumOutSig = zeros(size(fringes));
    for j = 1:numfringes
        % Get the fringe Indices
        [I,J] = ind2sub(size(image),fringes(:,j));
        fringesRounded = sub2ind(size(image),round(I),round(J));
        % Fringe is along I. We'll fit the amplitude first
        Afit = double(image(fringesRounded(~isnan(fringesRounded))));
        ppA = polyfit(J(~isnan(fringesRounded)),Afit,6);
        spectrumOutSig(:,j) = nanindex(image,fringesRounded)./polyval(ppA,J);
    end

%     figure;plot(1e4./data.spectrumX,reshape(spectrumOutSig,[],1));
%     hold on;
%     plot(1e4./data.spectrumX,reshape(spectrumOutRef,[],1),'g');
    if sumSpectrum == 0
        sumSpectrum = (1-reshape(spectrumOutSig,[],1)./reshape(spectrumOutRef,[],1));
    else
        sumSpectrum = sumSpectrum + (1-reshape(spectrumOutSig,[],1)./reshape(spectrumOutRef,[],1));
    end
end
%
h=figure;plot(1e4./data.spectrumX,sumSpectrum/numel(avgNums));
title(sprintf('Image Number %i',imgNum));
savefig(h,sprintf('\\\\ftcombdaq\\Mid_IR_Data\\temp\\%i.fig',imgNum))
%figure;plot(1e4./data.spectrumX,1-(nanindex(bkgImage,data.spectrumIndcs) - nanmean(nanmean(bkgImage)))./reshape(spectrumOutRef,[],1));