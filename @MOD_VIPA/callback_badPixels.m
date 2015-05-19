function self = callback_badPixels( self,hObject,eventdata)
%CALLBACK_BADPIXELS Summary of this function goes here
%   Detailed explanation goes here
        
        % Get image from screen
        fringeImage = get(self.imageHandle,'CData');
        
        % Get bkg Image
                 self.dependencyHandles.MOD_Arduino.public_shutterProgram();
                 self.dependencyHandles.MOD_FLIRcamera.public_acquireMultipleImages(3);
                 
                 bkgImages = reshape(self.dependencyHandles.MOD_FLIRcamera.collectedImageArray,[320 256 3]);
                 bkgImage = bkgImages(:,:,2)';
        
        % Find the indices of the bad pixels
        idx = find(double(bkgImage)<0.75*mean(bkgImage(:)) | double(bkgImage)>1.5*mean(bkgImage(:)));
        [idxX,idxY] = ind2sub(size(bkgImage),idx);
        
        % Plot the image and bad pixels
        figure;
        imagesc(bkgImage); hold on;
        scatter(idxY,idxX,'o');
        
        % Save the bad pixels to MOD_FLIRcamera
        self.dependencyHandles.MOD_FLIRcamera.badPixelIndcs = idx;

end

