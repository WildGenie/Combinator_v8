function returnData = acquireSpectra( self, numImages)
%PUBLIC_ACQUIREMULTIPLESPECTRA Summary of this function goes here
%   Detailed explanation goes here

    % Get the input
        if ~isscalar(numImages) || numImages < 0
           error('The number of images must be specified and positive'); 
        end

        % Aquire images
        images = self.dependencyHandles.MOD_ExternalAcquireSync.acquireImages(numImages);
        
        % Construct the indices for the image
        imageOffset = repmat(0:(numImages-1),[numel(self.spectrumIdcs) 1]);
        indcs = repmat(self.spectrumIdcs(:),[1 numImages]);
        numElements = self.fringeImageSize(1)*self.fringeImageSize(2);
        spectrumIndcs = imageOffset*numElements + indcs;
        spectrumIndcs = reshape(spectrumIndcs,size(self.spectrumIdcs,1),size(self.spectrumIdcs,2),[]);
        
%         % Construct averaging over fringe
%         avgNums = -1:1;
%         spectrumIndcsAvg = repmat(spectrumIndcs,[],size(avgNums));
%         spectrumIndcsAvg = spectrumIndcsAvg + ones(size(spectrumIndcs))*avgNums;
        
        % Construct the spectra
        returnData = zeros(size(spectrumIndcs));
        returnData(:) = NaN;
        returnData(~isnan(spectrumIndcs)) = ...
            images(round(...
            spectrumIndcs(~isnan(spectrumIndcs))...
            ));

end
