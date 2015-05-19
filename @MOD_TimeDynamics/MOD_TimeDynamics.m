classdef MOD_TimeDynamics < MOD_BASECLASS
   % write a description of the class here.
       properties (Constant)
           dependencies = {@MOD_VIPA,@MOD_SettingsTab,@MOD_ExternalAcquireSync,@MOD_FLIRcamera};
           moduleName = 'Time Dynamics';
       end
       properties
           % Dependency Handles
           Panel;
           % define the properties of the class here, (like fields of a struct)
           triggerRate = 50;
           acqRateDivFactor = 1;
           numImages = 300;
           excimerPulseImages = [10];
           minTimeBetweenAcquisitions = 0;
           referenceImages = [1];
           arduinoDelayTimeMilliseconds = 100;
           axes;
           singleAcquireButton;
           continuousAcquireButton;
           imageHandle;
           
           %loadSpectraFromFile()
           lastSaveLoadDirectory = pwd;
           loadSpectraFromFiles_filenames = {};
           
           %constructTimeDynamicsPlot()
           constructTimeDynamicsPlot_summedSpectra;
           constructTimeDynamicsPlot_averageNum;
           constructTimeDynamicsPlot_spectrumWavenumber;
           constructTimeDynamicsPlot_relativeAcquireTime;
           constructTimeDynamicsPlot_integrationTime;
           constructTimeDynamicsPlot_chemInfo;
           constructTimeDynamicsPlot_spectrumInfo;
           constructTimeDynamicsPlot_weightedSummedSpectra;
           constructTimeDynamicsPlot_weightSum;
           
           constructTimeDynamicsPlot_simulations = struct([]);
           
       end
       
       %%% BEGIN PROPERTY GRID %%%
       properties (Dependent = true)
            saveRAWimages;
            specNumsToDisplay;
            specOffset;
            specOffsetI;
            refSpecNum;
            spectrumType;
            polydegree;
            noPlotUpdate;
            frameRate;
            integrationTimeUs;
            photolysisImage;
            photolysisTimeOffsetUs;
       end
       properties
            hprop_saveRAWimages;
            hprop_specNumsToDisplay;
            hprop_specOffset;
            hprop_specOffsetI;
            hprop_refSpecNum;
            hprop_spectrumType;
            hprop_polydegree;
            hprop_noPlotUpdate;
            hprop_frameRate;
            hprop_integrationTimeUs;
            hprop_photolysisImage;
            hprop_photolysisTimeOffsetUs;
            PropertyGridProperties = [];
       end
       methods
           function self = set.saveRAWimages(self,value)
                self.hprop_saveRAWimages.Value = value;
           end
           function value = get.saveRAWimages(self)
                value = self.hprop_saveRAWimages.Value;
           end
           function self = set.specNumsToDisplay(self,value)
                self.hprop_specNumsToDisplay.Value = value;
           end
           function value = get.specNumsToDisplay(self)
                value = self.hprop_specNumsToDisplay.Value;
           end
           function self = set.refSpecNum(self,value)
                self.hprop_refSpecNum.Value = value;
           end
           function value = get.refSpecNum(self)
                value = self.hprop_refSpecNum.Value;
           end
           function self = set.spectrumType(self,value)
                self.hprop_spectrumType.Value = value;
           end
           function value = get.spectrumType(self)
                value = self.hprop_spectrumType.Value;
           end
           function self = set.polydegree(self,value)
                self.hprop_polydegree.Value = value;
           end
           function value = get.polydegree(self)
                value = self.hprop_polydegree.Value;
           end
           function self = set.specOffset(self,value)
                self.hprop_specOffset.Value = value;
           end
           function value = get.specOffset(self)
                value = self.hprop_specOffset.Value;
           end
           function self = set.specOffsetI(self,value)
                self.hprop_specOffsetI.Value = value;
           end
           function value = get.specOffsetI(self)
                value = self.hprop_specOffsetI.Value;
           end
           function self = set.noPlotUpdate(self,value)
                self.hprop_noPlotUpdate.Value = value;
           end
           function value = get.noPlotUpdate(self)
                value = self.hprop_noPlotUpdate.Value;
           end
           function self = set.frameRate(self,value)
                self.hprop_frameRate.Value = value;
           end
           function value = get.frameRate(self)
                value = self.hprop_frameRate.Value;
           end
           function self = set.integrationTimeUs(self,value)
                self.hprop_integrationTimeUs.Value = value;
           end
           function value = get.integrationTimeUs(self)
                value = self.hprop_integrationTimeUs.Value;
           end
           function self = set.photolysisImage(self,value)
                self.hprop_photolysisImage.Value = value;
           end
           function value = get.photolysisImage(self)
                value = self.hprop_photolysisImage.Value;
           end
           function self = set.photolysisTimeOffsetUs(self,value)
                self.hprop_photolysisTimeOffsetUs.Value = value;
           end
           function value = get.photolysisTimeOffsetUs(self)
                value = self.hprop_photolysisTimeOffsetUs.Value;
           end
           function self = setProperties(self)
            self.hprop_noPlotUpdate = PropertyGridField('noPlotUpdate', false, ...
                'Category', self.moduleName, ...
                'DisplayName', 'No Plot Update', ...
                'Description', 'Acquire spectra faster without updating the plot.');
            self.hprop_saveRAWimages = PropertyGridField('saveRAWimages', false, ...
                'Category', self.moduleName, ...
                'DisplayName', 'Save RAW Images', ...
                'Description', 'Saves RAW images when acquiring photolysis data.');
            self.hprop_refSpecNum = PropertyGridField('refSpecNum', 100, ...
                'Category', self.moduleName, ...
                'DisplayName', 'Reference Spectrum Number', ...
                'Description', 'Reference Spectrum Number.');
            self.hprop_specNumsToDisplay = PropertyGridField('specNumsToDisplay', [99 101 102], ...
                'Category', self.moduleName, ...
                'DisplayName', 'Spectrum Numbers To Display', ...
                'Description', 'Spectrum Numbers To Display.');
            self.hprop_specOffset = PropertyGridField('specOffset', double(-0.02), ...
                'Category', self.moduleName, ...
                'DisplayName', 'Initial Spectrum Offset', ...
                'Description', 'Offset for first spectrum.');
            self.hprop_specOffsetI = PropertyGridField('specOffsetI', double(0.02), ...
                'Category', self.moduleName, ...
                'DisplayName', 'Offset for each subsequent spectrum', ...
                'Description', 'Offset for each subsequent spectrum.');
            self.hprop_spectrumType = PropertyGridField(sprintf('%s_spectrumType',self.moduleName), '1-SIG/REF', ...
                'Type', PropertyType('char', 'row', {'1-SIG/REF','SIG/REF'}), ...
                'Category', self.moduleName, ...
                'DisplayName', 'Spectrum Type', ...
                'Description', 'Spectrum Type to display.');
            self.hprop_polydegree = PropertyGridField(sprintf('%s_polydegree',self.moduleName), uint16(3), ...
                'Category', self.moduleName, ...
                'DisplayName', 'Polynomial Fit Degree', ...
                'Description', 'Polynomial Fit Degree.');
            self.hprop_frameRate = PropertyGridField(sprintf('%s_frameRate',self.moduleName), double(250), ...
                'Category', self.moduleName, ...
                'DisplayName', 'Camera Frame Rate [Hz]', ...
                'Description', 'Camera Frame Rate [Hz].');
            self.hprop_integrationTimeUs = PropertyGridField(sprintf('%s_integrationTimeUs',self.moduleName), 50, ...
                'Category', self.moduleName, ...
                'DisplayName', 'Camera Integration Time [us]', ...
                'Description', 'Camera Integration Time [us].');
            self.hprop_photolysisImage = PropertyGridField(sprintf('%s_photolysisImage',self.moduleName), uint16(101), ...
                'Category', self.moduleName, ...
                'DisplayName', 'Photolysis Image Number', ...
                'Description', 'Photolysis Image Number.');
            self.hprop_photolysisTimeOffsetUs = PropertyGridField(sprintf('%s_photolysisTimeOffsetUs',self.moduleName), 0, ...
                'Category', self.moduleName, ...
                'DisplayName', 'Photolysis Time Offset [us]', ...
                'Description', 'Photolysis Time Offset [us].');
            self.PropertyGridProperties = [ ...
                    self.hprop_noPlotUpdate ...
                    self.hprop_saveRAWimages ...
                    self.hprop_specNumsToDisplay ...
                    self.hprop_refSpecNum ...
                    self.hprop_spectrumType ...
                    self.hprop_polydegree ...
                    self.hprop_specOffset ...
                    self.hprop_specOffsetI ...
                    self.hprop_frameRate ...
                    self.hprop_integrationTimeUs ...
                    self.hprop_photolysisImage ...
                    self.hprop_photolysisTimeOffsetUs];
           end
       end
       %%% END PROPERTY GRID %%%
       
       methods
       % methods, including the constructor are defined in this block
           function self = MOD_TimeDynamics()
           end
           function self = initialize(self,hObject)
                self.setProperties();
                self.dependencyHandles.MOD_SettingsTab.addProperties(self.PropertyGridProperties);
           end
           function delete(self)
           end
           function self = constructTab(self,hObject)
                handles = guidata(hObject);
                % Construct GUI Framework
                theTab = uiextras.Panel( 'Parent', handles.tabpanel, 'Padding', 5, 'Title', self.moduleName);
                handles.tabpanelNames{end+1} = self.moduleName;
                % Initialize the uimenu
                selfMenu = findobj(hObject,'Type','uimenu','-and','Label',self.moduleName,'-and','Parent',hObject);
                if isempty(selfMenu)
                   selfMenu = uimenu(hObject,'Label',self.moduleName);
                else
                   selfMenu = selfMenu(1); 
                end
                guidata(hObject,handles);

                
                % Save and Load Menu
                saveLoadMenu = uimenu(selfMenu,'label','Save and Load');
                    uimenu(saveLoadMenu, 'label','Load spectra from files','Callback', @self.loadSpectraFromFiles);
                    uimenu(saveLoadMenu, 'label','Save averaged spectra to file','Callback', @self.saveAveragedSpectraToFile);
                    uimenu(saveLoadMenu, 'label','Load averaged spectra from files','Callback', @self.loadAveragedSpectraFromFiles);
                    uimenu(saveLoadMenu, 'label','Load Wavenum Axis from Averaged Spectra File','Callback', @self.loadWavenumAxisFromAveragedSpectraFile);
                fittingMenu = uimenu(selfMenu,'label','Fitting');
                    uimenu(fittingMenu, 'label','Fit Spectrum Wavenumber','Callback', @self.fitSpectrumWavenumber);
                    uimenu(fittingMenu, 'label','Fit Averaged Spectra To Polynomial','Callback', @self.fitAveragedSpectraToPolynomial);
                    uimenu(fittingMenu, 'label','Fit Gaussian Lineshape','Callback', @self.fitGaussianLineshape);
                    uimenu(fittingMenu, 'label','Fit Averaged Spectra To Simulations','Callback', @self.fitAveragedSpectra);
                    uimenu(fittingMenu, 'label','Fit Instrument Lineshape','Callback', @self.fitInstrumentLineshape);
                automationMenu = uimenu(selfMenu,'label','Automation');
                    uimenu(automationMenu, 'label','New Automation Script','Callback', @self.newAutomationScript);
                    uimenu(automationMenu, 'label','Export Module Handle to Workspace Variable','Callback', @self.exportModuleHandleToWorkspaceVariable);
                spectrumParametersMenu = uimenu(selfMenu,'label','Spectrum Parameters');
                    uimenu(spectrumParametersMenu, 'label','Set Relative Acquire Time','Callback', @self.setRelativeAcquireTime);
                simulationsMenu = uimenu(selfMenu, 'label','Spectrum Simulations');
                    uimenu(simulationsMenu, 'label','Add Normalized Simulations','Callback', @self.addNormalizedSimulations);
                    uimenu(simulationsMenu, 'label','Clear Simulations','Callback', @self.clearSimulations);
                uimenu(selfMenu, 'label','Update Plot','Callback', @self.updatePlot);
                uimenu(selfMenu, 'label','New Figure','Callback', @(x,y) self.updatePlot(x,y,'axesHandle',[]));

                vbox = uiextras.VBox( 'Parent', theTab );
                self.axes = axes( 'Parent', vbox );
                hbox = uiextras.HButtonBox( 'Parent', vbox, 'Padding', 5 );
                self.singleAcquireButton = uicontrol( 'Parent', hbox, ...
                    'String', 'Single Acquire' );
                self.continuousAcquireButton = uicontrol( 'Parent', hbox, ...
                   'String', 'Continuous Acquire' );
                set( vbox, 'Sizes', [-1 35] )
                self.imageHandle = imagesc(zeros(100),'Parent',self.axes);

                % Set image context menu
                contextMenu = uicontextmenu('Parent',hObject);
                    uimenu(contextMenu, ...
                        'Label', 'New Figure', ...
                        'Callback', @self.callback_newFigure);
                set(self.imageHandle,'uicontextmenu',contextMenu);

                % Set GUI Callbacks
                set(self.singleAcquireButton,...
                    'Style','pushbutton',...
                    'String','Single Acquire',...
                    'Visible','on',...
                    'Callback',@self.callback_AcquireButton);
                set(self.continuousAcquireButton,...
                    'Style','togglebutton',...
                    'String','Continuous Acquire',...
                    'Visible','on',...
                    'Callback',@self.callback_AcquireButton);
                
                % Set some parameters
                self.callback_setSinglePixelTest({1,1});
                self.callback_setSinglePixelNorm({1,1});

           end
           %%% --- %%%

           function self = callback_setSinglePixelTest(self,vararg)
                    self.dependencyHandles.MOD_FLIRcamera.singlePixelI = vararg{1};
                    self.dependencyHandles.MOD_FLIRcamera.singlePixelJ = vararg{2};
           end
           function self = callback_setSinglePixelNorm(self,vararg)
                    self.dependencyHandles.MOD_FLIRcamera.singlePixelNormI = vararg{1};
                    self.dependencyHandles.MOD_FLIRcamera.singlePixelNormJ = vararg{2};
           end
           function self = callback_newFigure(self,hObject,eventdata)
                    % Construct a new figure
                    h = figure;
                    imagesc(get(self.imageHandle,'CData'));
           end
            function returnData = private_constructXaxis(self,hObject,eventdata)
                    returnData = {'Pixel Number',vararg,[]};
            end
            function returnData = private_constructYaxis(self,hObject,eventdata)
                    returnData = {'Counts',vararg,[]};
            end
           %%% --- %%%
           function publicProperties = getPublicProperties(obj)
                publicProperties = [];
           end
       end
end