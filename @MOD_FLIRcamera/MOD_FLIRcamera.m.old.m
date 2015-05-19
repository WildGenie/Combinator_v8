function returnData = MOD_FLIRcamera(hObject,argument)
%SUB_camera - initializes and uses the camera for stuff
%   argument - a parameter that indicates what is to be done

this = mfilename;
thisModule = str2func(mfilename);

if nargin == 0
   edit(this);
   return
end

if iscell(argument)
    if numel(argument) > 1
        vararg = argument(2:end);
    else
        vararg = {};
    end
    argument = argument{1};
else
   vararg = {}; 
end

switch argument
    %%%%%%%%%%%%%%%%%%%%%
    % STANDARD ROUTINES
    %%%%%%%%%%%%%%%%%%%%%
    case 'getDependencies'
        returnData = {};
    case 'getPublicProperties'
        returnData = [];
    case 'constructGUI'
        handles = guidata(hObject);
        
        % No gui necessary
        
        % Initialize the uimenu
        connectMenu = findobj(hObject,'Type','uimenu','-and','Label','FLIR Camera','-and','Parent',hObject);
        if isempty(connectMenu)
           connectMenu = uimenu(hObject,'Label','FLIR Camera');
        else
           connectMenu = connectMenu(1); 
        end
        uimenu(connectMenu, 'label','Connect FLIR Camera','Callback', @(hObject,eventdata) thisModule(hObject,'callback_connectCamera'));
        uimenu(connectMenu, 'label','Connect Fake FLIR Camera','Callback', @(hObject,eventdata) thisModule(hObject,'callback_connectFakeCamera'));
        uimenu(connectMenu, 'label','Set Frame Rate','Callback', @(hObject,eventdata) thisModule(hObject,'callback_setCameraFrameRate'));
        uimenu(connectMenu, 'label','Set Camera Trigger','Callback', @(hObject,eventdata) thisModule(hObject,'callback_setTrigger'));
        
        
        % Set camera connection variable
        handles.moduleData.(this).cameraConnected = 2;
        
        % Set bad pixel locations variable
        handles.moduleData.(this).badPixelIndcs = [];

        guidata(hObject,handles);
    %%%%%%%%%%%%%%%%%%%%%
    % PUBLIC METHODS
    %%%%%%%%%%%%%%%%%%%%%
    case 'public_acquireSingleImage'
        if numel(vararg) > 0 && strcmp(vararg{1},'rawImage')
           badPixelReplace = 0;
        else
           badPixelReplace = 1; 
        end
        
        handles = guidata(hObject);
        if handles.moduleData.(this).cameraConnected == 1
            handles.size_x = invoke(handles.moduleData.(this).CamCtrl_activeX_h,'GetCameraProperty',66);
            handles.size_y = invoke(handles.moduleData.(this).CamCtrl_activeX_h,'GetCameraProperty',67);
            invoke(handles.moduleData.(this).CamCtrl_activeX_h,'SetCameraProperty',82,int16(0));
            invoke(handles.moduleData.(this).CamCtrl_activeX_h,'SetCameraProperty',93,int32(5000));

            img = invoke(handles.moduleData.(this).CamCtrl_activeX_h,'GetImage',0)';
            handles.imageArray = img;
            guidata(hObject,handles);
            
            if img == -1
                error('Error: Could not display image.');
                return;
            elseif img == 14
                error('Error: Timeout on camera');
                return
            else
                % Replace bad pixels
                if badPixelReplace == 1
                   img(handles.moduleData.(this).badPixelIndcs) = 0;
                end
                returnData = img;
            end
        elseif handles.moduleData.(this).cameraConnected == 2
            returnData = randi(100,256,320);
        else
            returnData = -1;
        end
        
    case 'public_acquireMultipleImages'
        % Get the input
        if isempty(vararg)
           error('The number of images must be specified'); 
        end
        numImages = vararg{1};
        
        handles = guidata(hObject);
        if handles.moduleData.(this).cameraConnected == 1
            handles.size_x = invoke(handles.moduleData.(this).CamCtrl_activeX_h,'GetCameraProperty',66);
            handles.size_y = invoke(handles.moduleData.(this).CamCtrl_activeX_h,'GetCameraProperty',67);
            invoke(handles.moduleData.(this).CamCtrl_activeX_h,'SetCameraProperty',93,int32(5000));
            invoke(handles.moduleData.(this).CamCtrl_activeX_h,'SetCameraProperty',82,int16(0));
            imageTimeout = invoke(handles.moduleData.(this).CamCtrl_activeX_h,'GetCameraProperty',93);
            
            % Preallocate image array
            handles.imageArray = zeros(1,handles.size_x*handles.size_y*numImages);
            handles.imageArray = invoke(handles.moduleData.(this).CamCtrl_activeX_h,'MLGetImages',0, handles.size_x, handles.size_y, numImages);
            
            if numel(handles.imageArray) == 1
                handles.imageArray
                error('Error: Could not acquire image.');
                
                return;
            else
                guidata(hObject,handles);
                returnData = 1;
            end
        elseif handles.moduleData.(this).cameraConnected == 2
            handles.imageArray = randi(100,1,256*320*vararg{1});
            guidata(hObject,handles);
            returnData = 1;
        else
            returnData = -1;
        end

    %%%%%%%%%%%%%%%%%%%%%
    % CALLBACKS
    %%%%%%%%%%%%%%%%%%%%%
    case 'callback_connectFakeCamera'
        handles = guidata(hObject);
        handles.moduleData.(this).cameraConnected = 2;
        guidata(hObject,handles);
    case 'initialize'
        handles.CamCtrl_connected = 0; % No camera is currently connected
        %set(handles.VIPAControlFigure,'doublebuffer','on');
    case 'unload' % Must be designed to handle any figure handle as input
        handles_any = guidata(hObject);
        window = handles_any.mainWindowHandle;
        handles = guidata(window);
        if (handles.moduleData.(this).cameraConnected == 1)
            invoke(handles.moduleData.(this).CamCtrl_activeX_h,'Disconnect');
        end
        if isfield(handles.moduleData.(this),'CamCtrl_figure_h');
            delete(handles.moduleData.(this).CamCtrl_figure_h);
            handles.moduleData.(this) = rmfield(handles.moduleData.(this),'CamCtrl_figure_h');
        end
        guidata(window, handles);
    case 'callback_CameraEvent'
        handles_any = guidata(hObject);
        window = handles_any.mainWindowHandle;
        handles = guidata(window);
        switch double(vararg{1})
        case 2
            %set(handles.eventInfo,'string','Device is connected');
            %set(handles.acquire,'enable','on');
            handles.moduleData.(this).cameraConnected = 1;
            guidata(window,handles);
        case 3
            %set(handles.eventInfo,'string','Device is disconnected');
            handles.moduleData.(this).cameraConnected = 0;
            guidata(window,handles);
        case 4
            %set(handles.eventInfo,'string','Device connection broken');
            handles.moduleData.(this).cameraConnected = 0;
            guidata(window,handles);
        case 5
            %set(handles.eventInfo,'string','Device reconnected from broken connection');
            handles.moduleData.(this).cameraConnected = 1;
            guidata(window,handles);
        case 6
            %set(handles.acquire,'enable','off');
            %set(handles.eventInfo,'string','Device is in disconnecting phase');
            handles.moduleData.(this).cameraConnected = 0;
            guidata(window,handles);
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
    case 'callback_CamCmdReply'
        handles_any = guidata(hObject);
        window = handles_any.mainWindowHandle;
        handles = guidata(window);
    case 'callback_connectCamera'
        % This function will create a new figure as a container
        % for the vipacontrol Active-X, which is initialized
        handles = guidata(hObject);
        disp('Loading FLIR Camera ActiveX Control...');

        % Is the Camera Control figure already open?
        if isfield(handles.moduleData.(this),'CamCtrl_figure_h') && ishandle(handles.moduleData.(this).CamCtrl_figure_h)
            figure(handles.moduleData.(this).CamCtrl_figure_h);
            return;
        else
            
            % Open a figure for the Active-X Control
            cc_fig = figure('Position',[0,0,188,252],'MenuBar','none','name', ...
                            'Active-X Camera Control','tag','CamCtrl_ActiveX', ...
                            'CloseRequestFcn',@(hObject,eventdata) thisModule(hObject,'unload'));

            set(cc_fig,'Color',get(0,'defaultUicontrolBackgroundColor'));
            figure(cc_fig);

            % Launch the Active-X control!
            CamCtrl = actxcontrol('CAMCTRL.LVCamCtrl.3', [0 0 186 252], cc_fig, ...
                {'CameraEvent' @(a,eventid,varargin) thisModule(hObject,{'callback_CameraEvent',varargin{:}}); ...
                'CamCmdReply' @(a,varargin) thisModule(hObject,{'callback_CamCmdReply',varargin{:}})});
            new_handles             = guihandles(cc_fig);
            new_handles.mainWindowHandle     = handles.mainWindowHandle;
            new_handles.CamCtrl_figure_h   = cc_fig;
            guidata(cc_fig, new_handles);

            % Update guidata with handles to control & new figure...
            handles.moduleData.(this).CamCtrl_activeX_h = CamCtrl;
            handles.moduleData.(this).CamCtrl_figure_h = cc_fig;
            guidata(hObject, handles);
            invoke(handles.moduleData.(this).CamCtrl_activeX_h,'SetCameraProperty',61,int16(0));
            invoke(handles.moduleData.(this).CamCtrl_activeX_h,'GetCameraProperty',61)
        end
    case 'callback_setCameraFrameRate'
        handles = guidata(hObject);
        if handles.moduleData.(this).cameraConnected == 1
            response = inputdlg('Desired Camera Frame Rate [Hz]');
            if ~isempty(response) && round(str2double(response{1})) == str2double(response{1})
                invoke(handles.moduleData.(this).CamCtrl_activeX_h,'SetCameraProperty',43,double(str2double(response{1})));
                newFrameRate = invoke(handles.moduleData.(this).CamCtrl_activeX_h,'GetCameraProperty',43);
                msgbox(sprintf('The new frame rate is %f Hz',newFrameRate));
            end
        else
           msgbox('Camera must be connected to set the frame rate'); 
        end
    case 'callback_setTrigger'
        handles = guidata(hObject);
        if handles.moduleData.(this).cameraConnected == 1
            response = inputdlg('Desired camera trigger. 0 is external, 3 is none.');
            if ~isempty(response) && (strcmp(response{1},'0') || strcmp(response{1},'3'))
                invoke(handles.moduleData.(this).CamCtrl_activeX_h,'SetCameraProperty',31,int16(str2double(response{1})));
                newValue = invoke(handles.moduleData.(this).CamCtrl_activeX_h,'GetCameraProperty',31);
                msgbox(sprintf('The new trigger is %f',newValue));
            end
        else
           msgbox('Camera must be connected to set the frame rate'); 
        end
end

end

