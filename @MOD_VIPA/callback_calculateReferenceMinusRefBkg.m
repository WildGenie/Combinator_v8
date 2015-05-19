function self = callback_calculateReferenceMinusRefBkg( self, hObject, eventdata)
%CALLBACK_CALCULATEREFERENCEMINUSREFBKG Summary of this function goes here
%   Detailed explanation goes here

        % Calculate Image
        img = self.calibrationImages_reference -...
            self.calibrationImages_referenceBackground;
        
        % Display image
        set(self.imageHandle,'CData',img);
        set(self.axes,'XLim',[0 size(img,2)]);
        set(self.axes,'YLim',[0 size(img,1)]);

end

