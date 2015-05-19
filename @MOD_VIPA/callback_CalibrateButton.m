function self = callback_CalibrateButton( self, hObject, eventdata )
%CALLBACK_CALIBRATEBUTTON Summary of this function goes here
%   Detailed explanation goes here

        DEBUG_MODE = 0;
        if DEBUG_MODE == 1
            debugfprintf = @(varargin) fprintf(varargin{:});
        else
            debugfprintf = @NOP;
        end

        % Get image from screen
        fringeImage = get(self.imageHandle,'CData')';
        fringeImage = fringeImage./self.calibrationImages_reference;
        
        % Check to make sure that the dimensions of the image are correct
        if size(fringeImage') ~= self.fringeImageSize
           error('The collected fringes image is not the same size as the calibration image'); 
        end
        
        % Construct fringe image from indices
        fringeImageIdcs = sub2ind(size(fringeImage),...
            self.fringeX,...
            self.fringeY);
        
        collectedFringes = fringeImageIdcs;
        collectedFringes(~isnan(fringeImageIdcs)) = fringeImage(round(fringeImageIdcs(~isnan(fringeImageIdcs))));
        
        %figure;imagesc(collectedFringes);
        
        % Crop to an FSR
        cropArgsFringes = CropImageGUI(collectedFringes);
        
        % Crop indices to an FSR
        self.fringeXcrop = CropImageGUI_doCrop(self.fringeX,cropArgsFringes);
        self.fringeYcrop = CropImageGUI_doCrop(self.fringeY,cropArgsFringes);
        
        % Save indices as indices
        fringeImageIdcsCrop = sub2ind(size(fringeImage),...
            self.fringeXcrop,...
            self.fringeYcrop);
        
        % Flip the fringe indices
        fringeImageIdcsCrop = flipud(fringeImageIdcsCrop);
        
        self.fringeHeight = size(fringeImageIdcsCrop,1);
        self.numFringes = size(fringeImageIdcsCrop,2);
        self.spectrumIdcs = fringeImageIdcsCrop;
        debugfprintf('%s: Size(self.spectrumIndcs) = [%d %d]\n',size(self.spectrumIdcs,1),size(self.spectrumIdcs,1));
        
        % Save spectrumX
        self.spectrumX = reshape(1:numel(self.spectrumIdcs),size(self.spectrumIdcs));
        self.spectrumX = zeros(size(self.spectrumIdcs));
        reflambda = 3.725;
        fsr = 55;
        for k = 1:size(self.spectrumIdcs,2)
            deltaLambda = fsr * 1e9 * ((reflambda/10^6)^2)/3e8 * 1e6;
            self.spectrumX(:,k) = reflambda + deltaLambda*(k-1) + ...
                deltaLambda/size(self.spectrumIdcs,1)*((1:size(self.spectrumIdcs,1))-1);
        end
        
        % Save the relevant data
        %handles.MOD_constructSpectrum.imageFringeX = imageFringeX;
        %handles.MOD_constructSpectrum.imageFringeY = imageFringeY;
        %handles.MOD_constructSpectrum.imageFringeNumFringes = imageFringeNumFringes;
        %handles.MOD_constructSpectrum.imageFringeVertExtent = imageFringeVertExtent;

end

