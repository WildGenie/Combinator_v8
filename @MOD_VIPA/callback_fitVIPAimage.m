function self = callback_fitVIPAimage( self,hObject,eventdata)
%CALLBACK_FITVIPAIMAGE Summary of this function goes here
%   Detailed explanation goes here

        % Get images
        img = get(self.imageHandle,'CData')';
        imgRef = self.calibrationImages_reference;
        imgDiv = 1-img./imgRef;

        % Check to see if the image has the correct dimensions
        if size(imgDiv') ~= self.fringeImageSize
            imgDiv
           error('The collected fringes image is not the same size as the calibration image'); 
        end
        
        % Construct the spectrum
        fitSpectrum = zeros(size(self.spectrumIdcs));
        fitSpectrum(:) = NaN;
        fitSpectrum(~isnan(self.spectrumIdcs(:))) = ...
            imgDiv(round(...
            self.spectrumIdcs(~isnan(self.spectrumIdcs(:)))...
            ));
        
        % Fit the spectrum
        self.dependencyHandles.MOD_fitVIPAspectrum.setCalibSpectrumYaxis(fitSpectrum(:),self.fringeHeight,self.numFringes);
        uiwait(self.dependencyHandles.MOD_fitVIPAspectrum.fitFrequencyAxis());
        spectrumX = self.dependencyHandles.MOD_fitVIPAspectrum.xAxisFitted;

        if ~isempty(spectrumX)
            self.spectrumX = reshape(spectrumX,size(self.spectrumIdcs));
            disp('Calibration saved');
        else
            disp('Note: Fitting aborted');
        end
        
end

