classdef MOD_ExternalAcquireSync < MOD_BASECLASS
   % write a description of the class here.
       properties (Constant)
           moduleName = 'ExternalAcquireSync';
           dependencies = {@MOD_FLIRcamera,@MOD_Arduino};
       end
       properties
           % define the properties of the class here, (like fields of a struct)
       end
       methods
       % methods, including the constructor are defined in self block
       
           % Synchronization Profiles
           function images = acquireImages(self,numImages)
                if numImages ~= 1
                    error('numImages must be 1 for now');
                end
                self.dependencyHandles.MOD_FLIRcamera.public_acquireMultipleImages_startThread(numImages);
                self.dependencyHandles.MOD_Arduino.public_oneCameraImage();
                self.dependencyHandles.MOD_FLIRcamera.public_acquireMultipleImages(numImages);
                images = self.dependencyHandles.MOD_FLIRcamera.collectedImageArray;
                %[I,J] = ind2sub([size(image,1) size(image,2)],self.dependencyHandles.MOD_FLIRcamera.badPixelIndcs);
                %images(I,J,:) = NaN;
           end
           function images = acquireBackgroundImages(self,numImages)
                if numImages ~= 3
                   error('numImages must be 3 for now'); 
                end
                self.dependencyHandles.MOD_FLIRcamera.public_acquireMultipleImages_startThread(numImages);
                self.dependencyHandles.MOD_Arduino.public_shutterProgram();
                self.dependencyHandles.MOD_FLIRcamera.public_acquireMultipleImages(numImages);
                images = self.dependencyHandles.MOD_FLIRcamera.collectedImageArray;
                %[I,J] = ind2sub([size(image,1) size(image,2)],self.dependencyHandles.MOD_FLIRcamera.badPixelIndcs);
                %images(I,J,:) = NaN;
           end
           % Required Methods
           function self = initialize(self,hObject)
           end
           function delete(self)
           end
           function self = constructTab(self,hObject)
           end
           function publicProperties = getPublicProperties(obj)
                publicProperties = [];
           end
       end
end