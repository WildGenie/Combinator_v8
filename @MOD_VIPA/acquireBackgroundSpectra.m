function [returnSpectra,returnImages,returnSpectrumIndcs] = acquireBackgroundSpectra( self, numImages)
%PUBLIC_ACQUIREMULTIPLESPECTRA Summary of this function goes here
%   Detailed explanation goes here

    % Get the input
        if ~isscalar(numImages) || numImages < 0
           error('The number of images must be specified and positive'); 
        end

        % Aquire images
        returnImages = self.dependencyHandles.MOD_ExternalAcquireSync.acquireBackgroundImages(numImages);
        
        % Construct the indices for the image
        imageOffset = repmat(0:(numImages-1),[numel(self.spectrumIdcs) 1]);
        indcs = repmat(self.spectrumIdcs(:),[1 numImages]);
        numElements = self.fringeImageSize(1)*self.fringeImageSize(2);
        spectrumIndcs = imageOffset*numElements + indcs;
        spectrumIndcs = reshape(spectrumIndcs,size(self.spectrumIdcs,1),size(self.spectrumIdcs,2),[]);
        
        returnSpectrumIndcs = self.spectrumIdcs;
        
        % Construct the indices for the image
        imageOffset = repmat(0:(numImages-1),[numel(self.spectrumIdcs) 1]);
        indcs = repmat(self.spectrumIdcs(:)-1,[1 numImages]);
        numElements = self.fringeImageSize(1)*self.fringeImageSize(2);
        spectrumIndcsL = imageOffset*numElements + indcs;
        spectrumIndcsL = reshape(spectrumIndcsL,size(self.spectrumIdcs,1),size(self.spectrumIdcs,2),[]);
        
        % Construct the indices for the image
        imageOffset = repmat(0:(numImages-1),[numel(self.spectrumIdcs) 1]);
        indcs = repmat(self.spectrumIdcs(:)+1,[1 numImages]);
        numElements = self.fringeImageSize(1)*self.fringeImageSize(2);
        spectrumIndcsR = imageOffset*numElements + indcs;
        spectrumIndcsR = reshape(spectrumIndcsR,size(self.spectrumIdcs,1),size(self.spectrumIdcs,2),[]);
%         % Construct averaging over fringe
%         avgNums = -1:1;
%         spectrumIndcsAvg = repmat(spectrumIndcs,[],size(avgNums));
%         spectrumIndcsAvg = spectrumIndcsAvg + ones(size(spectrumIndcs))*avgNums;
        
        % Construct the spectra
        returnSpectra = zeros(size(spectrumIndcs));
        returnSpectra(:) = NaN;
        returnSpectra(~isnan(spectrumIndcs)) = ...
            double(...
            returnImages(round(...
            spectrumIndcs(~isnan(spectrumIndcs))...
            )) + ...
            returnImages(round(...
            spectrumIndcsR(~isnan(spectrumIndcsR))...
            )) + ...
            returnImages(round(...
            spectrumIndcsL(~isnan(spectrumIndcsL))...
            )))/3;
end

