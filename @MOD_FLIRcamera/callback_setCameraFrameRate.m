function self = callback_setCameraFrameRate( self,hObject,eventdata)
%CALLBACK_CAMERAEVENT Summary of this function goes here
%   Detailed explanation goes here

    if self.cameraConnected == 1
        response = inputdlg('Desired Camera Frame Rate [Hz]');
        if ~isempty(response) && round(str2double(response{1})) == str2double(response{1})
            invoke(self.CamCtrl_activeX_h,'SetCameraProperty',43,double(str2double(response{1})));
            newFrameRate = invoke(self.CamCtrl_activeX_h,'GetCameraProperty',43);
            msgbox(sprintf('The new frame rate is %f Hz',newFrameRate));
        end
    else
       msgbox('Camera must be connected to set the frame rate'); 
    end

end

