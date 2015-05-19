classdef MOD_Spectrum < MOD_BASECLASS
   % write a description of the class here.
       properties (Constant)
           dependencies = {@MOD_VIPA};
           moduleName = 'Spectrum';
       end
       properties
           % Dependency Handles
           Panel;
           % define the properties of the class here, (like fields of a struct)
           Tab;
           button;
           referenceButton;
           dataPlotHandle;
           axes;
           menu_recordReference;
           xAxis;
           yAxis;
           refSpectrumY;
           acquireButton;
           collectFringesButton;
           calibrateButton;
           fitVIPAimageButton;
           imageHandle;
           calibrationImages_reference;
           calibrationImages_referenceBackground;
           calibrationImages_calibrationGas;
           calibrationImages_calibrationGasBackground;
       end
       methods
       % methods, including the constructor are defined in this block
           function self = MOD_Spectrum()
           end
           function self = initialize(self,hObject)
           end
           function delete(self)
               
           end
           function self = constructTab(self,hObject)
                 % Construct GUI Framework
                 handles = guidata(hObject);
                theTab = uiextras.Panel( 'Parent', handles.tabpanel, 'Padding', 5, 'Title', self.moduleName);
                handles.tabpanelNames{end+1} = self.moduleName;
                guidata(hObject,handles);
                
                vbox = uiextras.VBox( 'Parent', theTab );
                self.axes = axes( 'Parent', vbox );
                hbox = uiextras.HButtonBox( 'Parent', vbox, 'Padding', 5 );
                self.button = uicontrol( 'Parent', hbox, ...
                    'String', 'Acquire' );
                self.referenceButton = uicontrol( 'Parent', hbox, ...
                    'String', 'Acquire Reference' );
                set( vbox, 'Sizes', [-1 35] )
                self.dataPlotHandle = plot(1:10,1:10,'Parent',self.axes);

                % Set context menu
                calibMenu = uicontextmenu('Parent',hObject);
                self.menu_recordReference = ...
                    uimenu(calibMenu, ...
                        'Label', 'New Figure', ...
                        'Callback', @self.callback_newFigure);
                 xAxisMenu = uimenu(calibMenu, 'Label', 'X Axis');
                     uimenu(xAxisMenu, ...
                         'Label', 'Pixel Number', ...
                         'Callback', @(hObject,eventdata) self.callback_xAxisMenu({'pixel number'}));
                     uimenu(xAxisMenu, ...
                         'Label', 'Wavelength [\mum]', ...
                         'Callback', @(hObject,eventdata) self.callback_xAxisMenu({'wavelength'}));
                     uimenu(xAxisMenu, ...
                         'Label', 'Wavenumber [cm^{-1}]', ...
                         'Callback', @(hObject,eventdata) self.callback_xAxisMenu({'wavenumber'}));
                     uimenu(xAxisMenu, ...
                         'Label', '(FFT) Etalon Length [mm]', ...
                         'Callback', @(hObject,eventdata) self.callback_bothAxisMenu({'etalon FFT X','etalon FFT Y'}));
                 yAxisMenu = uimenu(calibMenu, 'Label', 'Y Axis');
                     uimenu(yAxisMenu, ...
                         'Label', 'Counts', ...
                         'Callback', @(hObject,eventdata) self.callback_yAxisMenu({'counts'}));
                     uimenu(yAxisMenu, ...
                         'Label', 'Counts w/o Background Subtraction', ...
                         'Callback', @(hObject,eventdata) self.callback_yAxisMenu({'countsWithoutBackgroundSubtraction'}));
                     uimenu(yAxisMenu, ...
                         'Label', 'Attenuation (1-T_{cav})', ...
                         'Callback', @(hObject,eventdata) self.callback_yAxisMenu({'attenuation'}));
                     uimenu(yAxisMenu, ...
                         'Label', 'Absorption Coefficient', ...
                         'Callback', @(hObject,eventdata) self.callback_yAxisMenu({'absorption coefficient'}));
                     uimenu(yAxisMenu, ...
                         'Label', '(FFT) Etalon Amplitude', ...
                         'Callback', @(hObject,eventdata) self.callback_bothAxisMenu({'etalon FFT X','etalon FFT Y'}));
                 calculateMenu = uimenu(calibMenu, 'Label', 'Calculate');
                     uimenu(calculateMenu, ...
                         'Label', 'Standard Deviation', ...
                         'Callback', @(hObject,eventdata) self.callback_calculateMenu({'StDev'}));
                set(self.axes,'uicontextmenu',calibMenu);

                % Set the x and y axes to default
                self.xAxis = '';
                self.yAxis = '';

                % Set reference spectrum variable
                self.refSpectrumY = [];

                % Set GUI Callbacks
                set(self.button,...
                    'Style','togglebutton',...
                    'String','Acquire',...
                    'Visible','on',...
                    'Callback',@self.callback_AcquireButton);
                set(self.referenceButton,...
                    'Style','togglebutton',...
                    'String','Acquire Reference',...
                    'Visible','on');
           end
           %%% --- %%%
           function self = callback_bothAxisMenu(self,vararg)
                    if numel(vararg) > 1
                        self.xAxis = vararg{1};
                        self.yAxis = vararg{2};
                    else
                        self.xAxis = '';
                        self.yAxis = '';
                    end
           end
            function self = callback_xAxisMenu(self,vararg)
                if numel(vararg) > 0
                    self.xAxis = vararg{1};
                else
                    self.xAxis = '';
                end
            end
            function self = callback_yAxisMenu(self,vararg)
                if numel(vararg) > 0
                    self.yAxis = vararg{1};
                else
                    self.yAxis = '';
                end
            end
            function self = callback_calculateMenu(self,vararg)
                if numel(vararg) > 0
                    switch vararg{1}
                        case 'StDev'
                            msgbox(sprintf('The variance of the current plot is: %f',nanvar(get(self.dataPlotHandle,'YData'))));
                        case 'Var'
                            msgbox(sprintf('The variance of the current plot is: %f',nanvar(get(self.dataPlotHandle,'YData'))));
                    end
                end
            end
            function self = callback_newFigure(self,hObject,eventdata)

                % Construct a new figure
                h = figure;
                plot(get(self.dataPlotHandle,'XData'),...
                    get(self.dataPlotHandle,'YData'));
            end
            function self = callback_AcquireButton(self,hObject,eventdata)
                if ~(get(self.button, 'value'))
                    return
                end
                % Live image
                % Continue as long as button is pressed
                imgsPerBackground = 1e6;
                bkgCounter = 0;

                % Set save file if needed
                [filename,filepath] = uiputfile('*.csv','Save Spectra As...');
                if ~isequal(filename,0) && ~isequal(filepath,0)
                   saveFilename = fullfile(filepath,filename);
                   fileCounter = 0;
                else
                   saveFilename = [];
                   fileCounter = 0;
                end

                % Aquire test image
                spectrumY = self.dependencyHandles.MOD_VIPA.acquireSpectra(1);

                % Acquire ref spectrum if needed
                if ~isequal(size(self.refSpectrumY),size(spectrumY))
                    self.refSpectrumY = ones(size(spectrumY));
                end

                while (get(self.button, 'value'))

                    % Check to see if we need a new background
                    if mod(bkgCounter,imgsPerBackground) == 0 || (get(self.referenceButton, 'value'))
                         bkgSpectrum = self.dependencyHandles.MOD_VIPA.acquireBackgroundSpectra(3);
                         bkgSpectrum = bkgSpectrum(:,:,1);
                         bkgCounter = 0;

                        if ~isempty(saveFilename)
                           x = get(self.dataPlotHandle,'XData');
                           y = double(bkgSpectrum);
                           fileToSave = sprintf('%s_%i',saveFilename,fileCounter);
                           saveDate = now;
                           save(sprintf('%s_%i.mat',sprintf('%s_%i_background.mat',saveFilename,fileCounter),fileCounter),'x','y','saveDate');
                           fprintf('Saved ''%s''\n',sprintf('%s_%i',filename,fileCounter));
                        end

                        % Acquire ref spectrum if needed
                        if (get(self.referenceButton, 'value'))
                             self.dependencyHandles.MOD_Arduino.public_oneCameraImage();
                             self.refSpectrumY = self.dependencyHandles.MOD_VIPA.public_acquireSpectrum()-bkgSpectrum;
                             set(self.referenceButton, 'value',0)
                        end
                    end
                    bkgCounter = bkgCounter + 1;
                    
                    % Aquire image
                    spectrumY = self.dependencyHandles.MOD_VIPA.acquireSpectra(1)-bkgSpectrum;
                    spectrumX = self.dependencyHandles.MOD_VIPA.public_getWavelengthAxis();

                    % Construct the x-axis
                    xaxisCell = self.private_constructXaxis({spectrumX(:)});

                    % Construct the y-axis
                    yaxisCell = self.private_constructYaxis({spectrumY(:),self.refSpectrumY(:),bkgSpectrum(:)});

                    % Update the axis labels
                    xlabel(self.axes,xaxisCell{1});
                    ylabel(self.axes,yaxisCell{1});

                    % Display the spectrum
                    set(self.dataPlotHandle,'XData',xaxisCell{2});
                    set(self.dataPlotHandle,'YData',yaxisCell{2});

                    % Update the axis limits if needed
                    if ~isempty(xaxisCell{3})
                        set(self.axes,'XLim',xaxisCell{3});
                    end
                    if ~isempty(yaxisCell{3})
                        set(self.axes,'YLim',yaxisCell{3});
                    end

                    if ~isempty(saveFilename)
                       x = get(self.dataPlotHandle,'XData');
                       y = get(self.dataPlotHandle,'YData');
                       fileToSave = sprintf('%s_%i',saveFilename,fileCounter);
                       saveDate = now;
                       save(sprintf('%s_%i.mat',sprintf('%s_%i.mat',saveFilename,fileCounter),fileCounter),'x','y','saveDate');
                       fprintf('Saved ''%s''\n',sprintf('%s_%i',filename,fileCounter));
                       fileCounter = fileCounter + 1;
                    end

                    pause(0.05);
                end

            end

                %%%%%%%%%%%%%%%%%%   
                % PRIVATE METHODS
                %%%%%%%%%%%%%%%%%%
            function returnData = private_constructXaxis(self,vararg)
                switch self.xAxis
                    case 'pixel number'
                        returnData = {'Pixel Number',1:numel(vararg{1}),[]};
                    case 'wavenumber'
                        returnData = {'Wavenumber [cm^{-1}]',1e4./vararg{1},[]};
                    case 'wavelength'
                        returnData = {'Wavelength [\mum]',vararg{1},[]};
                    case 'etalon FFT X'
                        NFFT = 2^nextpow2(numel(vararg{1})); % Next power of 2 from length of y
                        wavenumDiff = abs(min(diff(1e4./vararg{1})));
                        returnData = {'Etalon Length [mm]',10/(8*wavenumDiff)*linspace(0,1,NFFT/2+1),[]};
                    otherwise
                        returnData = {'Pixel Number',1:numel(vararg{1}),[]};
                end
            end
            function returnData = private_constructYaxis(self,vararg)
                switch self.yAxis
                    case 'counts'
                        returnData = {'Counts',vararg{1},[]};
                    case 'countsWithoutBackgroundSubtraction'
                        returnData = {'Counts w/o Background Subtraction',vararg{1}+vararg{3},[]};
                    case 'attenuation'
                        returnData = {'Attenuation (1-T_{cav})',vararg{1}./vararg{2},[]};
                    case 'transmission'
                        returnData = {'Transmission (T_{cav})',vararg{1}./vararg{2},[]};
                    case 'absorption coefficient'
                        returnData = {'Absorption Coefficient [cm^{-1}]',0,[]};
                    case 'etalon FFT Y'
                        NFFT = 2^nextpow2(numel(vararg{1})); % Next power of 2 from length of y
                        y = vararg{1}./vararg{2};
                        y(isnan(y)) = 1;
                        Y = fft(y,NFFT)/numel(y);
                        %f = Fs/2*linspace(0,1,NFFT/2+1);

                        returnData = {'FFT Amplitude',2*abs(Y(1:NFFT/2+1)),[]};
                    otherwise
                        returnData = {'Counts',vararg{1},[]};
                end
            end

           %%%---%%%
           function publicProperties = getPublicProperties(obj)
                publicProperties = [];
           end
       end
end