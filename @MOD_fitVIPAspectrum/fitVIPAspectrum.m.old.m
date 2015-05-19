function returnData = MOD_fitVIPAspectrum(hObject,argument)
%SUB_calibration - initializes and calibrates spectra
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
end

switch argument
    
    %%%%%%%%%%%%%%%%%%%%%
    % STANDARD ROUTINES
    %%%%%%%%%%%%%%%%%%%%%
    case 'getDependencies'
       % Check for MOD_camera
        returnData = {};
        
    case 'getPublicProperties'
        returnData = [...
            PropertyGridField('guessFSR', 55, ...
                'Category', 'VIPA Spectrum Fitting', ...
                'DisplayName', 'VIPA FSR Estimate [GHz]', ...
                'Description', 'Estimate of the VIPA FSR. Used when calibrating VIPA.') ...
            PropertyGridField('guessLambda', 3.92, ...
                'Category', 'VIPA Spectrum Fitting', ...
                'DisplayName', 'Center Wavelength Estimate [um]', ...
                'Description', 'Estimate of the VIPA FSR. Used when calibrating VIPA.') ...
                ];
        
    case 'constructGUI'
        % no gui
        
    case 'initialize'
        handles = guidata(hObject);
        handles.moduleData.(this).xAxisFitted = [];
        guidata(hObject,handles);
        
    %%%%%%%%%%%%%%%%%
    % PUBLIC METHODS
    %%%%%%%%%%%%%%%%%
    case 'setCalibSpectrumYaxis'
        % This method needs 3 arguments:
        %  1: the y axis array
        %  2: fringe vertical extent (number of pixels vertically
        %  3: fringe horizontal extent (number of fringes)
        
        handles = guidata(hObject);
        
        if numel(vararg) == 3
            handles.moduleData.(this).calibSpectrumYaxis = vararg{1};
            handles.moduleData.(this).imageFringeVertExtent = vararg{2};
            handles.moduleData.(this).imageFringeNumFringes = vararg{3};
        else
            error('setCalibSpectrumYaxis requires 3 arguments');
        end
        guidata(hObject,handles);
        
    case 'fitFrequencyAxis'
        handles = guidata(hObject);
        
        % Clear the previously fitted x axis
        handles.moduleData.(this).xAxisFitted = [];
        
        load('Icons');
        % Create a uipushtool in the toolbar
        handles.moduleData.(this).fitFrequencyAxisFigureHandle = figure;
        handles.moduleData.(this).expPlotHandle = plot(1:10,1:10); hold on;
        handles.moduleData.(this).simPlotHandle = plot(1:10,1:10,'r'); hold off;
        xlabel('Wavelength [\mum]');
        
        ht = uitoolbar(handles.moduleData.(this).fitFrequencyAxisFigureHandle);
        uipushtool(ht,'CData',icons.leftIcon,...
                 'TooltipString','Shift Frequency Left',...
                 'ClickedCallback',...
                 @(~,eventdata) thisModule(hObject,'fitFrequencyAxisFigureShiftLeft'));
        uipushtool(ht,'CData',icons.setWavelengthIcon,...
                 'TooltipString','Set Reference Wavelength',...
                 'ClickedCallback',...
                 @(~,eventdata) thisModule(hObject,'fitFrequencyAxisFigureShiftSet'));
        uipushtool(ht,'CData',icons.rightIcon,...
                 'TooltipString','Shift Frequency Right',...
                 'ClickedCallback',...
                 @(~,eventdata) thisModule(hObject,'fitFrequencyAxisFigureShiftRight'));
        uipushtool(ht,'CData',icons.peakPickIcon,...
                 'TooltipString','Start Peak Picker',...
                 'ClickedCallback',...
                 @(~,eventdata) thisModule(hObject,'fitFrequencyAxisPickFreqPoints'));
        
        guidata(hObject,handles);
        thisModule(hObject,'fitFrequencyAxisFigureUpdateSpectrum');
        returnData = handles.moduleData.(this).fitFrequencyAxisFigureHandle;
        
    case 'getFittedXaxis'
        handles = guidata(hObject);
        returnData = handles.moduleData.(this).xAxisFitted;
        
    case 'fitFrequencyAxisFigureShiftLeft'
        handles = guidata(hObject);
        handles.properties.Properties.FindByName('guessLambda').Value = handles.properties.Properties.FindByName('guessLambda').Value - 0.001;
        guidata(hObject,handles);
        thisModule(hObject,'fitFrequencyAxisFigureUpdateSpectrum');
        
    case 'fitFrequencyAxisFigureShiftSet'
        handles = guidata(hObject);
        x = inputdlg('Enter spectrum center wavelength [um]:', 'Set Spectrum Center Wavelength', [1 50],...
            {num2str(handles.properties.Properties.FindByName('guessLambda').Value)});
        handles.properties.Properties.FindByName('guessLambda').Value = str2double(x{1});
        guidata(hObject,handles);
        thisModule(hObject,'fitFrequencyAxisFigureUpdateSpectrum');
        
    case 'fitFrequencyAxisFigureShiftRight'
        handles = guidata(hObject);
        handles.properties.Properties.FindByName('guessLambda').Value = handles.properties.Properties.FindByName('guessLambda').Value + 0.001;
        guidata(hObject,handles);
        thisModule(hObject,'fitFrequencyAxisFigureUpdateSpectrum');
        
    case 'fitFrequencyAxisFigureUpdateSpectrum'
        handles = guidata(hObject);
        
        % Get the necessary parameters
        imageFringeVertExtent = handles.moduleData.(this).imageFringeVertExtent;
        imageFringeNumFringes = handles.moduleData.(this).imageFringeNumFringes;
        centerlambda = handles.properties.Properties.FindByName('guessLambda').Value;
        fsr = handles.properties.Properties.FindByName('guessFSR').Value;
        
        % Convert center lambda to reflambda
        reflambda = 1/(1/centerlambda + fsr*1e9*imageFringeNumFringes/2/299792458*(1e-6));
        
        % Construct the new x-axis for the spectrum (in microns)
        handles.moduleData.(this).calibSpectrumXaxis = zeros(imageFringeVertExtent,imageFringeNumFringes);
        for k = 1:imageFringeNumFringes
            deltaLambda = fsr * 1e9 * ((reflambda/10^6)^2)/3e8 * 1e6;
            handles.moduleData.(this).calibSpectrumXaxis(:,k) = reflambda + deltaLambda*(k-1) + ...
                deltaLambda/imageFringeVertExtent*((1:imageFringeVertExtent)-1);
        end
        handles.moduleData.(this).calibSpectrumXaxis = handles.moduleData.(this).calibSpectrumXaxis(:);
        
        % Construct the spectrum to fit to
        load('06_hit04.mat'); % CH4
        fun = @(params,x) 1-calculate_CH4_midIRcavity_spectrum_fixedGaussian(s,x, 30, params(1)*1e-3, params(2)*1e9);
        simulationWavenumber = min(1e4./handles.moduleData.(this).calibSpectrumXaxis):0.01:max(1e4./handles.moduleData.(this).calibSpectrumXaxis);
        figure(handles.moduleData.(this).fitFrequencyAxisFigureHandle);

        % Actually plot the spectra
        set(handles.moduleData.(this).expPlotHandle,'XData',handles.moduleData.(this).calibSpectrumXaxis);
        set(handles.moduleData.(this).expPlotHandle,'YData',handles.moduleData.(this).calibSpectrumYaxis);
        set(handles.moduleData.(this).simPlotHandle,'XData',1e4./simulationWavenumber);
        set(handles.moduleData.(this).simPlotHandle,'YData',fun([0.1 1],simulationWavenumber)-0.5);
        
        guidata(hObject,handles);
        
    case 'fitFrequencyAxisPickFreqPoints'
        handles = guidata(hObject);
        
        % Load spectrum values from MOD_constructSpectrum
        polydegree = 3;
        numPoints = 5;

        HITRANx = get(handles.moduleData.(this).simPlotHandle,'XData');
        HITRANy = get(handles.moduleData.(this).simPlotHandle,'YData');
        EXPx = get(handles.moduleData.(this).expPlotHandle,'XData');
        EXPy = get(handles.moduleData.(this).expPlotHandle,'YData');

        hfig = figure; hEXPplot = plot(EXPx,EXPy); hold on; hHITRANplot = plot(HITRANx,HITRANy,'r'); hpointsPlot = scatter(mean(EXPx),mean(EXPy),'k*');
        set(hpointsPlot,'XData',[]);
        set(hpointsPlot,'YData',[]);

        HITRANpickedX = zeros(1,numPoints);
        HITRANpickedY = zeros(1,numPoints);
        EXPpickedX = zeros(1,numPoints);
        EXPpickedY = zeros(1,numPoints);

        % Scaling parameters for choosing points
        deltaX = max(EXPx)-min(EXPx);
        deltaY = max(EXPy)-min(EXPy);

        for i = 1:numPoints
            [x,y]=ginput(1);

            [~,b]=min(((EXPx-x)/deltaX).^2+((EXPy-y)/deltaY).^2);
            EXPpickedX(i) = EXPx(b(1));
            EXPpickedY(i) = EXPy(b(1));
            [x,y]=ginput(1);
            [~,b]=min(((HITRANx-x)/deltaX).^2+((HITRANy-y)/deltaY).^2);
            HITRANpickedX(i) = HITRANx(b(1));
            HITRANpickedY(i) = HITRANy(b(1));

            set(hpointsPlot,'XData',[EXPpickedX(1:i) HITRANpickedX(1:i)]);
            set(hpointsPlot,'YData',[EXPpickedY(1:i) HITRANpickedY(1:i)]);
        end

        close(hfig);

        %  Actually Fit the freq axis
        p = polyfit(EXPpickedX,HITRANpickedX,2);
        EXPxFitted = polyval(p,EXPx);
        EXPpickedXFitted = polyval(p,EXPpickedX);
        polyX = min(EXPpickedX):0.0001:max(EXPpickedX);
        figure; scatter(EXPpickedX,HITRANpickedX); hold on; plot(polyX,polyval(p,polyX),'r');

        hfig = figure; hEXPplot = plot(EXPxFitted,EXPy); hold on; hHITRANplot = plot(HITRANx,HITRANy,'r'); hpointsPlot = scatter(mean(EXPx),mean(EXPy),'k*');
        set(hpointsPlot,'XData',[EXPpickedXFitted HITRANpickedX]);
        set(hpointsPlot,'YData',[EXPpickedY HITRANpickedY]);
        
        handles.moduleData.(this).xAxisFitted = EXPxFitted;
        guidata(hObject,handles);
        
    case 'calibrationSettings'
        % Set calibration parameters
        x = inputdlg('Set pixel threshold [counts]', 'Calibration Settings', [1 50],...
            {'10'});
        handles.MOD_constructSpectrum.thresh = str2double(x{1});
end
end