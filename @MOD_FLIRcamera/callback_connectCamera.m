function self = callback_connectCamera( self,hObject,eventdata)
%CALLBACK_CAMERAEVENT Summary of this function goes here
%   Detailed explanation goes here
    % This function will create a new figure as a container
    % for the vipacontrol Active-X, which is initialized
    disp('Loading FLIR Camera ActiveX Control...');

    % Is the Camera Control figure already open?
    if ishandle(self.CamCtrl_figure_h)
        figure(self.CamCtrl_figure_h);
        return;
    else
        % Open a figure for the Active-X Control
        cc_fig = figure('Position',[0,0,188,252],'MenuBar','none','name', ...
                        'Active-X Camera Control','tag','CamCtrl_ActiveX', ...
                        'CloseRequestFcn',@self.disconnectFLIRcamera);

        set(cc_fig,'Color',get(0,'defaultUicontrolBackgroundColor'));
        figure(cc_fig);

        % Launch the Active-X control!
        CamCtrl = actxcontrol('CAMCTRL.LVCamCtrl.3', [0 0 186 252], cc_fig, ...
            {'CameraEvent', @(a,eventid,eventdata,varargin) self.callback_cameraEvent(a,eventid,eventdata,varargin{:}), ...
            'CamCmdReply', @(a,varargin) self.callback_CamCmdReply(a,varargin{:})});

        % Update guidata with handles to control & new figure...
        self.CamCtrl_activeX_h = CamCtrl;
        self.CamCtrl_figure_h = cc_fig;
        invoke(self.CamCtrl_activeX_h,'SetCameraProperty',61,int16(0));
        invoke(self.CamCtrl_activeX_h,'GetCameraProperty',61)
    end
end

