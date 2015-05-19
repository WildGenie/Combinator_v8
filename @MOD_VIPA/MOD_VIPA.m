classdef MOD_VIPA < MOD_BASECLASS
   % write a description of the class here.
       properties (Constant)
           dependencies = {@MOD_ExternalAcquireSync,@MOD_SettingsTab,@MOD_fitVIPAspectrum};
           moduleName = 'VIPA';
       end
       properties (Transient = true)
           % Dependency Handles
           Panel;
           % define the properties of the class here, (like fields of a struct)
           Tab;
           button;
           referenceButton;
           dataPlotHandle;
           axes;
           acquireButton;
           collectFringesButton;
           calibrateButton;
           fitVIPAimageButton;
           imageHandle;
           menu_recordReferenceBackground;
           menu_recordReference;
           menu_recordCalibrationGas;
           menu_recordCalibrationGasBackground;
       end
       properties
           % Acquire a spectrum
           spectrumX = [];
           spectrumY = [];
           xAxis;
           yAxis;
           refSpectrumY;
           calibrationImages_reference;
           calibrationImages_referenceBackground;
           calibrationImages_calibrationGas;
           calibrationImages_calibrationGasBackground;
           fringeImageSize = 0;
           spectrumIdcs;
           fringeX;
           fringeY;
           fringeXcrop;
           fringeYcrop;
           fringeHeight;
           numFringes;
       end

       %%% BEGIN PROPERTY GRID %%%
       properties (Dependent = true)
            calibrationGas;
            calibrationGasPartialPressure;
            calibrationGasPathLength;
            fringeThreshold;
            imgsPerBackground;
       end
       properties
            hprop_calibrationGas;
            hprop_calibrationGasPartialPressure;
            hprop_calibrationGasPathLength;
            hprop_fringeThreshold;
            hprop_imgsPerBackground;
            PropertyGridProperties = [];
       end
       methods
           function self = set.calibrationGas(self,value)
                self.hprop_calibrationGas.Value = value;
           end
           function value = get.calibrationGas(self)
                value = self.hprop_calibrationGas.Value;
           end
           function self = set.calibrationGasPartialPressure(self,value)
                self.hprop_calibrationGasPartialPressure.Value = value;
           end
           function value = get.calibrationGasPartialPressure(self)
                value = self.hprop_calibrationGasPartialPressure.Value;
           end
           function self = set.calibrationGasPathLength(self,value)
                self.hprop_calibrationGasPathLength.Value = value;
           end
           function value = get.calibrationGasPathLength(self)
                value = self.hprop_calibrationGasPathLength.Value;
           end
           function self = set.fringeThreshold(self,value)
                self.hprop_fringeThreshold.Value = value;
           end
           function value = get.fringeThreshold(self)
                value = self.hprop_fringeThreshold.Value;
           end
           function self = set.imgsPerBackground(self,value)
                self.hprop_imgsPerBackground.Value = value;
           end
           function value = get.imgsPerBackground(self)
                value = self.hprop_imgsPerBackground.Value;
           end
           function self = setProperties(self)
            self.hprop_calibrationGas = PropertyGridField('calibrationGas', 'Methane', ...
                'Type', PropertyType('char', 'row', {'Methane'}), ...
                'Category', self.moduleName, ...
                'DisplayName', 'Calibration Gas', ...
                'Description', 'Calibration gas spectrum to use when calibrating VIPA.');
            self.hprop_calibrationGasPartialPressure = PropertyGridField('calibrationGasPartialPressure', 1, ...
                'Category', self.moduleName, ...
                'DisplayName', 'Cal. Gas Partial Pressure [torr]', ...
                'Description', 'Calibration gas partial pressure, in torr. Used to construct calibration gas spectrum when calibrating VIPA.');
            self.hprop_calibrationGasPathLength = PropertyGridField('calibrationGasPathLength', 1, ...
                'Category', self.moduleName, ...
                'DisplayName', 'Cal. Gas Path Length [m]', ...
                'Description', 'Calibration gas optical path length, in meters. Used to construct calibration gas spectrum when calibrating VIPA.');
            self.hprop_fringeThreshold = PropertyGridField('fringeThreshold', 10, ...
                'Category', self.moduleName, ...
                'DisplayName', 'VIPA Fringe Threshold', ...
                'Description', 'Used when calibrating VIPA.');
            self.hprop_imgsPerBackground = PropertyGridField(sprintf('%s_imgsPerBackground',self.moduleName), uint16(60000), ...
                'Category', self.moduleName, ...
                'DisplayName', 'Signal Images Per Background', ...
                'Description', 'Number of signal images per background image (Continuous Acquire Mode only).');
            self.PropertyGridProperties = [ ...
                    self.hprop_calibrationGas ...
                    self.hprop_calibrationGasPartialPressure ...
                    self.hprop_calibrationGasPathLength ...
                    self.hprop_fringeThreshold,...
                    self.hprop_imgsPerBackground];
           end
       end
       %%% END PROPERTY GRID %%%

       methods
       % methods, including the constructor are defined in self block
%            function self = MOD_VIPA()
%            end
           function self = initialize(self,hObject)
                self.setProperties();
                self.dependencyHandles.MOD_SettingsTab.addProperties(self.PropertyGridProperties);
           end
           function delete(self)
               
           end
           function self = constructTab(self,hObject)
                handles = guidata(hObject);
                self.Tab = uiextras.Panel( 'Parent', handles.tabpanel, 'Padding', 5, 'Title', self.moduleName);
                handles.tabpanelNames{end+1} = self.moduleName;
                % Initialize the uimenu
                selfMenu = findobj(hObject,'Type','uimenu','-and','Label',self.moduleName,'-and','Parent',hObject);
                if isempty(selfMenu)
                   selfMenu = uimenu(hObject,'Label',self.moduleName);
                else
                   selfMenu = selfMenu(1); 
                end
                guidata(hObject,handles);

                vbox = uiextras.VBox( 'Parent', self.Tab );
                self.axes = axes( 'Parent', vbox );
                hbox = uiextras.HButtonBox( 'Parent', vbox, 'Padding', 5 );
                self.acquireButton = uicontrol( 'Parent', hbox, ...
                    'String', 'Acquire' );
                self.collectFringesButton = uicontrol( 'Parent', hbox, ...
                    'String', 'Collect Fringes' );
                self.calibrateButton = uicontrol( 'Parent', hbox, ...
                    'String', 'Calibrate' );
                self.fitVIPAimageButton = uicontrol( 'Parent', hbox, ...
                    'String', 'Fit to Cal. Gas' );
                set( vbox, 'Sizes', [-1 35] )
                self.imageHandle = imagesc(zeros(100),'Parent',self.axes);
                
                uimenu(selfMenu, 'label','Save to file','Callback', @self.saveToFile);
                uimenu(selfMenu, 'label','Load from file','Callback', @self.loadFromFile);
                
               % Set context menu
                calibMenu = uicontextmenu('Parent',hObject);
                recordAsMenu = uimenu(calibMenu, 'Label', 'Record Image As');
                self.menu_recordReference = ...
                    uimenu(recordAsMenu, ...
                        'Label', 'Reference', ...
                        'Callback', @self.callback_recordReference);
                self.menu_recordReferenceBackground = ...
                    uimenu(recordAsMenu, ...
                        'Label', 'Reference Background', ...
                        'Callback', @self.callback_recordReferenceBackground);
                self.menu_recordCalibrationGas = ...
                    uimenu(recordAsMenu, ...
                        'Label', 'Calibration Gas', ...
                        'Callback', @self.callback_recordCalibrationGas);
               self.menu_recordCalibrationGasBackground = ...
                    uimenu(recordAsMenu, ...
                        'Label', 'Calibration Gas Background', ...
                        'Callback', @self.callback_recordCalibrationGasBackground);
                loadImageMenu = uimenu(calibMenu, 'Label', 'Load Image');
                uimenu(loadImageMenu, ...
                        'Label', 'Load Image from Workspace', ...
                        'Callback', @self.callback_loadImageFromWorkspace);
                uimenu(loadImageMenu, ...
                        'Label', 'Calculate Reference - Ref. Bkg', ...
                        'Callback', @self.callback_calculateReferenceMinusRefBkg);
                customSelectionMenu = uimenu(calibMenu, 'Label', 'Custom Selection');
                uimenu(customSelectionMenu, ...
                        'Label', 'Line Profile', ...
                        'Callback', @self.callback_chooseImageProfile);
                uimenu(calibMenu, 'Label', 'Find Bad Pixels', ...
                        'Callback', @self.callback_badPixels);
                uimenu(calibMenu, 'Label', 'Show Selection', ...
                        'Callback', @self.callback_showSelection);
                set(self.imageHandle,'uicontextmenu',calibMenu);


                % Set GUI Callbacks
                set(self.acquireButton,...
                    'Style','togglebutton',...
                    'String','Acquire',...
                    'Visible','on',...
                    'Callback',@self.callback_AcquireButton);
                set(self.collectFringesButton,...
                    'Style','pushbutton',...
                    'String','Collect Fringes',...
                    'Visible','on',...
                    'Callback',@self.callback_collectFringesButton);
                set(self.calibrateButton,...
                    'Style','pushbutton',...
                    'String','Calibrate',...
                    'Visible','on',...
                    'Callback',@self.callback_CalibrateButton);
                set(self.fitVIPAimageButton,...
                    'Style','pushbutton',...
                    'String','Fit to Cal. Gas',...
                    'Visible','on',...
                    'Callback',@self.callback_fitVIPAimage);

                % Set default internal parameters
                self.calibrationImages_reference = [];
                self.calibrationImages_referenceBackground = [];
                self.calibrationImages_calibrationGas = [];
                self.calibrationImages_calibrationGasBackground = [];

           end
           function publicProperties = getPublicProperties(obj)
                publicProperties = [];
           end
           function self = saveToFile(self,hObject,eventdata)
                % Set save file if needed
                [filename,filepath] = uiputfile('*.mat',sprintf('Save %s Settings As...',self.moduleName));
                if ~isequal(filename,0) && ~isequal(filepath,0)
                   saveFilename = fullfile(filepath,filename);
                else
                   return;
                end
                s = self.getstruct();
                save(saveFilename,'-struct','s');
           end
           function self = loadFromFile(self,hObject,eventdata)
                % Set save file if needed
                [filename,filepath] = uigetfile('*.mat',sprintf('Load %s Settings From...',self.moduleName));
                if ~isequal(filename,0) && ~isequal(filepath,0)
                   saveFilename = fullfile(filepath,filename);
                else
                   return;
                end
                s = load(saveFilename);
                self.loadstruct(s);
           end
       end
end