function returnData = public_acquireMultipleImages( self, numImages, varargin )
%ACQUIREMULTIPLEIMAGES Summary of this function goes here
%   Detailed explanation goes here
    if ~isscalar(numImages) || numImages < 1
       error('The number of images must be specified and be positive'); 
    end

    if self.cameraConnected == 1
        self.collectedImage_size_x = invoke(self.CamCtrl_activeX_h,'GetCameraProperty',66);
        self.collectedImage_size_y = invoke(self.CamCtrl_activeX_h,'GetCameraProperty',67);
        invoke(self.CamCtrl_activeX_h,'SetCameraProperty',93,int32(5000));
        invoke(self.CamCtrl_activeX_h,'SetCameraProperty',82,int16(0));
        imageTimeout = invoke(self.CamCtrl_activeX_h,'GetCameraProperty',93);
        
        % Preallocate image array
        self.collectedImageArray = zeros(1,self.collectedImage_size_x*self.collectedImage_size_y*numImages);
        self.collectedImageArray = invoke(self.CamCtrl_activeX_h,'MLGetImages',0, self.collectedImage_size_x, self.collectedImage_size_y, numImages);
        
        if numel(self.collectedImageArray) == 1
            error('Error: Could not acquire image.');
        else
            self.collectedImageArray = reshape(self.collectedImageArray,self.collectedImage_size_x,self.collectedImage_size_y,[]);
            returnData = 1;
        end
    elseif self.cameraConnected == 2
        self.collectedImageArray = randi(100,1,256*320*numImages);
        self.collectedImageArray = reshape(self.collectedImageArray,320,256,[]);
        returnData = 1;
    elseif self.cameraConnected == 3
        try
            self.collectedImageArray = pleora_acquireMultipleImagesPersistent_v2();
        catch ME
            self.collectedImageArray = zeros(1,320*256*numImages);
        end
        self.collectedImageArray = reshape(self.collectedImageArray,320,256,[]);
    else
        returnData = -1;
    end
end

