function returnData = public_acquireSpectrum( self, hObject, eventdata )
%PUBLIC_ACQUIRESPECTRUM Summary of this function goes here
%   Detailed explanation goes here

        % Aquire image
        img = double(self.dependencyHandles.MOD_FLIRcamera.public_acquireSingleImage());
        img(self.dependencyHandles.MOD_FLIRcamera.badPixelIndcs) = NaN;
        img = img';

        % Check to see if the image has the correct dimensions
        if size(img') ~= self.fringeImageSize
           error('The collected fringes image is not the same size as the calibration image'); 
        end
        
        % Construct the spectrum
        returnData = NaN*zeros(size(self.spectrumIdcs));
        returnData(~isnan(self.spectrumIdcs)) = ...
            mean(img(round(...
            self.spectrumIdcs(~isnan(self.spectrumIdcs))...
            )),2);

end

