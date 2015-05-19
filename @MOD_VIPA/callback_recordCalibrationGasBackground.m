function self = callback_recordCalibrationGasBackground( self,hObject,eventdata )
%PUBLIC_RECORDCALIBRATIONGASBACKGROUND Summary of this function goes here
%   Detailed explanation goes here
        self.calibrationImages_calibrationGasBackground = get(self.imageHandle,'CData');
        set(self.menu_recordCalibrationGasBackground,'Checked','on');

end

