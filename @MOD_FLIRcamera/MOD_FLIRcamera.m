classdef MOD_FLIRcamera < MOD_BASECLASS
   % write a description of the class here.
       properties (Constant)
           moduleName = 'FLIRcamera';
           dependencies = {};
       end
       properties
           % define the properties of the class here, (like fields of a struct)
           CamCtrl_activeX_h;
           CamCtrl_figure_h;
           cameraConnected = 3; % 1 for FLIR camera, 2 for simulated camera, 3 for MEX
           badPixelIndcs = [];
           collectedImageArray;
           collectedImage_size_x;
           collectedImage_size_y;
           singlePixelI;
           singlePixelJ;
           singlePixelNormI;
           singlePixelNormJ;
       end
       methods
       % methods, including the constructor are defined in self block
           function self = MOD_FLIRcamera()
           end
           function self = initialize(self,hObject)
           end
           function disconnectFLIRcamera(self,hObject,eventdata)
                if (self.cameraConnected == 1)
                    invoke(self.CamCtrl_activeX_h,'Disconnect');
                    self.cameraConnected = 0;
                end
                %if ishandle(self.CamCtrl_activeX_h) & isvalid(self.CamCtrl_activeX_h);
                    delete(self.CamCtrl_activeX_h);
                %end
                if ishandle(self.CamCtrl_figure_h);
                    delete(self.CamCtrl_figure_h);
                end
           end
           function delete(self)
                if (self.cameraConnected == 1)
                    invoke(self.CamCtrl_activeX_h,'Disconnect');
                    pause(1);
                end
                if ishandle(self.CamCtrl_activeX_h) & isvalid(self.CamCtrl_activeX_h);
                    delete(self.CamCtrl_activeX_h);
                end
                %if ishandle(self.CamCtrl_figure_h) & isvalid(self.CamCtrl_figure_h);
                %    delete(self.CamCtrl_figure_h);
                %end
           end
           function self = constructTab(self,hObject)
                handles = guidata(hObject);

                % No gui necessary

                % Initialize the uimenu
                connectMenu = findobj(hObject,'Type','uimenu','-and','Label','FLIR Camera','-and','Parent',hObject);
                if isempty(connectMenu)
                   connectMenu = uimenu(hObject,'Label','FLIR Camera');
                else
                   connectMenu = connectMenu(1); 
                end
                uimenu(connectMenu, 'label','Connect FLIR Camera','Callback', @self.callback_connectCamera);
                uimenu(connectMenu, 'label','Connect FLIR Camera MEX','Callback', @self.callback_connectCameraUsingMEX);
                uimenu(connectMenu, 'label','Connect Fake FLIR Camera','Callback', @self.callback_connectFakeCamera);
                uimenu(connectMenu, 'label','Set Frame Rate','Callback', @self.callback_setCameraFrameRate);
                uimenu(connectMenu, 'label','Set Camera Trigger','Callback', @self.callback_setTrigger);

                % Set bad pixel locations variable
                self.badPixelIndcs = [];

                guidata(hObject,handles);

           end
           function self = callback_connectCameraUsingMEX( self,hObject,eventdata)
               self.cameraConnected = 3;
           end
           function publicProperties = getPublicProperties(obj)
                publicProperties = [];
           end
       end
end