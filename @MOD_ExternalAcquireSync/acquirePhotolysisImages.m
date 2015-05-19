function images = acquirePhotolysisImages(self,numImages)
    if numImages ~= 53
        error('numImages must be 53 for now');
    end
    self.dependencyHandles.MOD_FLIRcamera.public_acquireMultipleImages_startThread(numImages);
    self.dependencyHandles.MOD_Arduino.excimerProgram(0,1,50,0,[]);
    self.dependencyHandles.MOD_FLIRcamera.public_acquireMultipleImages(numImages);
    images = self.dependencyHandles.MOD_FLIRcamera.collectedImageArray;
    %[I,J] = ind2sub([size(image,1) size(image,2)],self.dependencyHandles.MOD_FLIRcamera.badPixelIndcs);
    %images(I,J,:) = NaN;
end