function self = callback_recordCalibrationGas( self,hObject,eventdata )
%CALLBACK_RECORDCALIBRATIONGAS Summary of this function goes here
%   Detailed explanation goes here
        self.calibrationImages_calibrationGas = get(self.imageHandle,'CData');
        set(self.menu_recordCalibrationGas,'Checked','on');

end

