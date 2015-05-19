function returnData = public_acquireSingleImage( self, varargin )
%ACQUIRESINGLEIMAGE Summary of this function goes here
%   Detailed explanation goes here

% Options
%    'bkgSubtract','on'/'off'

    if numel(varargin) > 1 && strcmp(varargin{1},'rawImage')
       badPixelReplace = 0;
    else
       badPixelReplace = 1;
    end

    if self.cameraConnected == 1
        handles.size_x = invoke(self.CamCtrl_activeX_h,'GetCameraProperty',66);
        handles.size_y = invoke(self.CamCtrl_activeX_h,'GetCameraProperty',67);
        invoke(self.CamCtrl_activeX_h,'SetCameraProperty',82,int16(0));
        invoke(self.CamCtrl_activeX_h,'SetCameraProperty',93,int32(5000));

        img = invoke(self.CamCtrl_activeX_h,'GetImage',0)';

        if img == -1
            error('Error: Could not display image.');
            return;
        elseif img == 14
            error('Error: Timeout on camera');
            return
        else
            % Replace bad pixels
            if badPixelReplace == 1
               img(self.badPixelIndcs) = 0;
            end
            returnData = img;
        end
    elseif self.cameraConnected == 2
        returnData = randi(100,256,320);
    elseif self.cameraConnected == 3
        returnData = pleora_acquireMultipleImages(uint16(320),uint16(256),uint16(1))';
    else
        returnData = -1;
    end
end

