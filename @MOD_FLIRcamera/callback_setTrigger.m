function self = callback_setTrigger( self,hObject,eventdata)
%CALLBACK_CAMERAEVENT Summary of this function goes here
%   Detailed explanation goes here

    if self.cameraConnected == 1
        response = inputdlg('Desired camera trigger. 0 is external, 3 is none.');
        if ~isempty(response) && (strcmp(response{1},'0') || strcmp(response{1},'3'))
            invoke(self.CamCtrl_activeX_h,'SetCameraProperty',31,int16(str2double(response{1})));
            newValue = invoke(self.CamCtrl_activeX_h,'GetCameraProperty',31);
            msgbox(sprintf('The new trigger is %f',newValue));
        end
    else
       msgbox('Camera must be connected to set the frame rate'); 
    end

end

