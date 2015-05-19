function self = callback_recordReferenceBackground( self, hObject,eventdata )
%CALLBACK_RECORDREFERENCEBACKGROUND Summary of this function goes here
%   Detailed explanation goes here
        self.calibrationImages_referenceBackground = get(self.imageHandle,'CData');
        set(self.menu_recordReferenceBackground,'Checked','on');

end

