function returnData = public_acquireMultipleImages_startThread( self, numImages, varargin )
%ACQUIREMULTIPLEIMAGES Summary of this function goes here
%   Detailed explanation goes here
    if ~isscalar(numImages) || numImages < 1
       error('The number of images must be specified and be positive'); 
    end

    if self.cameraConnected == 1
        % No thread to start
        returnData = 1;
    elseif self.cameraConnected == 2
        % No thread to start
        returnData = 1;
    elseif self.cameraConnected == 3
        [~] = pleora_acquireMultipleImagesPersistent_v2(uint16(320),uint16(256),uint16(numImages));
        returnData = 1;
    else
        returnData = -1;
    end
end

