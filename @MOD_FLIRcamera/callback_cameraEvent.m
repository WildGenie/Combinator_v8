function self = callback_cameraEvent( self,a,eventid,eventdata,varargin)
%CALLBACK_CAMERAEVENT Summary of this function goes here
%   Detailed explanation goes here

    switch double(eventdata)
        case 2
            %set(handles.eventInfo,'string','Device is connected');
            %set(handles.acquire,'enable','on');
            self.cameraConnected = 1;
        case 3
            %set(handles.eventInfo,'string','Device is disconnected');
            self.cameraConnected = 0;
        case 4
            %set(handles.eventInfo,'string','Device connection broken');
            self.cameraConnected = 0;
        case 5
            %set(handles.eventInfo,'string','Device reconnected from broken connection');
            self.cameraConnected = 1;
        case 6
            %set(handles.acquire,'enable','off');
            %set(handles.eventInfo,'string','Device is in disconnecting phase');
            self.cameraConnected = 0;
        case 7
            %set(handles.eventInfo,'string','Auto adjust event');
        case 8
            %set(handles.eventInfo,'string','Start of recalibration');
        case 9
            %set(handles.eventInfo,'string','End of recalibration');
        case 10
        %    set(handles.eventInfo,'string','LUT table updated'); % Ignore!
        case 11
            %set(handles.eventInfo,'string','Record conditions changed');
        case 12
            %set(handles.eventInfo,'string','Image captured');
        case 13
            %set(handles.eventInfo,'string','Init completed');
        case 14
            %set(handles.eventInfo,'string','Frame rate table available');
        case 15
            %set(handles.eventInfo,'string','Frame rate change completed');
        case 16
            %set(handles.eventInfo,'string','Range table available');
        case 17
            %set(handles.eventInfo,'string','Range change completed');
        case 18
            %set(handles.eventInfo,'string','Image size changed');
    end

end

