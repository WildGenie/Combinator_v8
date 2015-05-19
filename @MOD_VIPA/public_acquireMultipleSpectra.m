function returnData = public_acquireMultipleSpectra( self, numImages)
%PUBLIC_ACQUIREMULTIPLESPECTRA Summary of this function goes here
%   Detailed explanation goes here

    % Get the input
        if ~isscalar(numImages) || numImages < 0
           error('The number of images must be specified and positive'); 
        end

        % Aquire image
        self.dependencyHandles.MOD_FLIRcamera.public_acquireMultipleImages(numImages);

        if size( self.dependencyHandles.MOD_FLIRcamera.collectedImageArray,1) ~= 1 ||...
                size(self.dependencyHandles.MOD_FLIRcamera.collectedImageArray,2) ~= self.fringeImageSize(1)*self.fringeImageSize(2)*numImages
           error('The collected fringes image is not the same size as the calibration image'); 
        end
        
        % Construct the indices for the image
        imageOffset = repmat(0:(numImages-1),[length(self.spectrumIdcs) 1]);
        indcs = repmat(self.spectrumIdcs,[1 numImages]);
        numElements = self.fringeImageSize(1)*self.fringeImageSize(2);
        spectrumIndcs = imageOffset*numElements + indcs;
        
%         % Construct averaging over fringe
%         avgNums = -1:1;
%         spectrumIndcsAvg = repmat(spectrumIndcs,[],size(avgNums));
%         spectrumIndcsAvg = spectrumIndcsAvg + ones(size(spectrumIndcs))*avgNums;
        
        % Construct the spectra
        returnData = zeros(size(spectrumIndcs));
        returnData(:) = NaN;
        returnData(~isnan(spectrumIndcs)) = ...
            self.dependencyHandles.MOD_FLIRcamera.collectedImageArray(round(...
            spectrumIndcs(~isnan(spectrumIndcs))...
            ));

end

