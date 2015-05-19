function self = callback_recordReference( self,hObject,eventdata)
%CALLBACK_RECORDREFERENCE Summary of this function goes here
%   Detailed explanation goes here
        self.calibrationImages_reference = get(self.imageHandle,'CData');
        set(self.menu_recordReference,'Checked','on');

end

