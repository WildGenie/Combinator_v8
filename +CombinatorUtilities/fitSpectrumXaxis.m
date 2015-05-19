classdef fitSpectrumXaxis < MOD_BASECLASS
   % write a description of the class here.
       properties (Constant)
           moduleName = 'fitVIPAspectrum';
           dependencies = {};
       end
       properties
           simFilename = '06_hit04.mat';
           
           % Acquire a spectrum
           spectrumX = [1 2 3 4];
           spectrumY = [1 1 1 1];
           
           simPlotHandle;
           expPlotHandle;
           fitFrequencyAxisFigureHandle;
           
           containerHandle;
           expAxis;
           simAxis;
           EXPpickedXFitted
           
           % Simulation parameters
           simMinWavenumber = 2500;
           simMaxWavenumber = 2800;
           wavenumMin = 2500;
           wavenumMax = 2800;
           P = 1; % in atm
           Pa = 1e-9; % in atm
           T = 300;
           AbsorptionLength = 0.5488;
           
           % Dependency Handles
           xAxisFitted = [];
           expScatterHandle;
           simScatterHandle;
           
           p;
           EXPpickedIDX = [];
           SIMpickedX = [];
           SIMpickedY = [];
           polydegree = 3;
           % Spectrum Parameters
           calibSpectrumXaxis = [1 2 3 4];
           calibSpectrumYaxis = [1 1 1 1];
       end
       methods
       % methods, including the constructor are defined in self block
           function self = fitSpectrumXaxis()
           end
           function self = initialize(self,hObject)
                self.xAxisFitted = [];
           end
           function self = setCalibSpectrumYaxis(self,yaxis,vertExtent,horizExtent)
                % self method needs 3 arguments:
                %  1: the y axis array
                %  2: fringe vertical extent (number of pixels vertically
                %  3: fringe horizontal extent (number of fringes)

                self.calibSpectrumYaxis = yaxis;
                self.imageFringeVertExtent = vertExtent;
                self.imageFringeNumFringes = horizExtent;
           end
           function fitFrequencyAxisFigureHandle = fitFrequencyAxis(self,spectrum,spectrumWavenumber)
               self.calibSpectrumYaxis = spectrum;
               self.calibSpectrumXaxis = spectrumWavenumber;
               
                % Clear the previously fitted x axis
                self.xAxisFitted = [];

                load('Icons');
                % Create a uipushtool in the toolbar
                self.fitFrequencyAxisFigureHandle = figure;
                self.expAxis = subplot(2,1,1);
                self.simAxis = subplot(2,1,2);
                set(self.expAxis,'OuterPosition',[0 0.5 1 0.5]);
                set(self.expAxis,'Position',[0.13 0.543 0.775 0.42]);
                set(self.simAxis,'OuterPosition',[0 0.017 1 0.5]);
                set(self.simAxis,'Position',[0.13 0.11 0.775 0.385]);
                
                self.expPlotHandle = plot(self.expAxis,[1],[1]); hold(self.expAxis,'on');
                self.expScatterHandle = scatter(self.expAxis,[1],[1],'k*'); hold(self.expAxis,'off');
                set(self.expScatterHandle,'XData',[]);
                set(self.expScatterHandle,'YData',[]);
                self.simPlotHandle = plot(self.simAxis,[1],[1],'r'); hold(self.simAxis,'on');
                self.simScatterHandle = scatter(self.simAxis,[1],[1],'k*'); hold(self.simAxis,'off');
                set(self.simScatterHandle,'XData',[]);
                set(self.simScatterHandle,'YData',[]);
                linkaxes([self.expAxis self.simAxis],'x');
                set(self.expAxis,'XTickLabel',[])
                set(self.expAxis,'XTick',[]);
                xlabel(self.simAxis,'Wavenumber [cm^{-1}]');
                ht = uitoolbar(self.fitFrequencyAxisFigureHandle);
                uipushtool(ht,'CData',icons.leftIcon,...
                         'TooltipString','Shift Frequency Left',...
                         'ClickedCallback',...
                         @self.fitFrequencyAxisFigureShiftLeft);
                uipushtool(ht,'CData',icons.setWavelengthIcon,...
                         'TooltipString','Set Reference Wavelength',...
                         'ClickedCallback',...
                         @self.fitFrequencyAxisFigureShiftSet);
                uipushtool(ht,'CData',icons.rightIcon,...
                         'TooltipString','Shift Frequency Right',...
                         'ClickedCallback',...
                         @self.fitFrequencyAxisFigureShiftRight);
                uipushtool(ht,'CData',icons.peakPickIcon,...
                         'TooltipString','Start Peak Picker',...
                         'ClickedCallback',...
                         @self.pickPeak);
                uipushtool(ht,'CData',icons.peakPickIcon,...
                         'TooltipString','Clear Picked Peaks',...
                         'ClickedCallback',...
                         @self.clearPeaks);
                
                self.fitFrequencyAxisFigureUpdateSpectrum();
                fitFrequencyAxisFigureHandle = self.fitFrequencyAxisFigureHandle;
           end
        function returnData = getFittedXaxis(self)
            returnData = self.xAxisFitted;
        end
        function self = fitFrequencyAxisFigureShiftLeft(self,hObject,eventdata)
            self.calibSpectrumXaxis = self.calibSpectrumXaxis - 0.001;
            self.fitFrequencyAxisFigureUpdateSpectrum();
        end
        function self = fitFrequencyAxisFigureShiftSet(self,hObject,eventdata)
            x = inputdlg('Enter spectrum center wavenumber [cm-1]:', 'Set Spectrum Center Wavenumber', [1 50],...
                {num2str(self.centerWavenum)});
            self.centerWavenum = str2double(x{1});
            self.fitFrequencyAxisFigureUpdateSpectrum();
        end
        function self = fitFrequencyAxisFigureShiftRight(self,hObject,eventdata)
            self.calibSpectrumXaxis = self.calibSpectrumXaxis + 0.001;
            self.fitFrequencyAxisFigureUpdateSpectrum();
        end
        function self = clearPeaks(self,hObject,eventdata)
             self.EXPpickedIDX = [];
             self.SIMpickedX = [];
             self.SIMpickedY = [];
             self.fitFrequencyAxisFigureUpdateSpectrum();
        end
        function self = pickPeak(self,hObject,eventdata)
            % Scaling parameters for choosing points
            SIMx = get(self.simPlotHandle,'XData');
            SIMy = get(self.simPlotHandle,'YData');
            EXPx = get(self.expPlotHandle,'XData');
            EXPy = get(self.expPlotHandle,'YData');
            
            deltaX = -diff(get(self.expAxis,'XLim'));
            deltaY = -diff(get(self.expAxis,'XLim'));

            [x,y]=ginput(1);
            deltaX = max(EXPx)-min(EXPx);
            deltaY = max(EXPy)-min(EXPy);
            [~,b]=min(((EXPx-x)/deltaX).^2+((EXPy-y)/deltaY).^2);
            self.EXPpickedIDX(end+1) = b(1);
            
            % Get sim point
            [x,y]=ginput(1);
            deltaX = -diff(get(self.simAxis,'XLim'));
            deltaY = -diff(get(self.simAxis,'YLim'));
            [~,b]=min(((SIMx-x)/deltaX).^2+((SIMy-y)/deltaY).^2);
            self.SIMpickedX(end+1) = SIMx(b(1));
            self.SIMpickedY(end+1) = SIMy(b(1));

            self.fitFrequencyAxisFigureUpdateSpectrum();
        end
        function self = fitFrequencyAxisFigureUpdateSpectrum(self)
            
            %self.calibSpectrumXaxis = self.centerWavenum+self.deltaWavenum*numel(self.calibSpectrumYaxis)*linspace(-1,1,numel(self.calibSpectrumYaxis));
            if numel(self.EXPpickedIDX) >= 2
                %  Actually Fit the freq axis
                self.p = polyfit(self.EXPpickedIDX,self.SIMpickedX,min(numel(self.EXPpickedIDX)-1,self.polydegree));
                self.xAxisFitted = polyval(self.p,1:numel(self.calibSpectrumYaxis));
                self.EXPpickedXFitted = polyval(self.p,1:numel(self.calibSpectrumYaxis));

                set(self.expPlotHandle,'XData',self.xAxisFitted);
                set(self.expPlotHandle,'YData',self.calibSpectrumYaxis(:));
                set(self.expAxis,'XLim',[min(self.xAxisFitted) max(self.xAxisFitted)]);
                set(self.expScatterHandle,'XData',self.xAxisFitted(self.EXPpickedIDX));
                set(self.expScatterHandle,'YData',self.calibSpectrumYaxis(self.EXPpickedIDX));
            else
                % Construct the new x-axis for the spectrum
                set(self.expPlotHandle,'XData',self.calibSpectrumXaxis);
                set(self.expPlotHandle,'YData',self.calibSpectrumYaxis(:));
                set(self.expAxis,'XLim',[min(self.calibSpectrumXaxis) max(self.calibSpectrumXaxis)]);
                set(self.expScatterHandle,'XData',self.calibSpectrumXaxis(self.EXPpickedIDX));
                set(self.expScatterHandle,'YData',self.calibSpectrumYaxis(self.EXPpickedIDX));
                self.EXPpickedXFitted = [];
            end
                set(self.simScatterHandle,'XData',self.SIMpickedX);
                set(self.simScatterHandle,'YData',self.SIMpickedY);
            
            % Construct the spectrum to fit to
            [~,~,ext] = fileparts(self.simFilename);
            
            if strcmp(ext,'.mat')
                simulationWavenumber = (self.wavenumMin-10):0.01:(self.wavenumMax+10);
                sigma = self.calculateCrossSection(self.simFilename,self.wavenumMin,self.wavenumMax,self.P,self.Pa,self.T);
                atmToPa = 101325;
                boltzmannK = 1.38e-23;
                Absorbance = 1-exp(-sigma*self.Pa*atmToPa/boltzmannK/self.T*self.AbsorptionLength);
            elseif strcmp(ext,'.simSpec')
                data = load(self.simFilename,'-mat');
                simulationWavenumber = data.wavenumber;
                Absorbance = data.crossSection;
            else
                error('not implemented')
                data = csvread(self.simFilename);
                simulationWavenumber = data(:,1);
                Absorbance = data(:,2);
            end
                
            % Actually plot the spectra
            set(self.simPlotHandle,'XData',simulationWavenumber);
            set(self.simPlotHandle,'YData',Absorbance);
        end
        function self = fitFrequencyAxisPickFreqPoints(self,hObject,eventdata)
        
            % Load spectrum values from MOD_constructSpectrum
            polydegree = 3;
            numPoints = 5;

            HITRANx = get(self.simPlotHandle,'XData');
            HITRANy = get(self.simPlotHandle,'YData');
            EXPx = get(self.expPlotHandle,'XData');
            EXPy = get(self.expPlotHandle,'YData');

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
            set(hpointsPlot,'XData',[EXPpickedXFitted 1e4./HITRANpickedX]);
            set(hpointsPlot,'YData',[EXPpickedY HITRANpickedY]);

            self.xAxisFitted = EXPxFitted;
        end
        function self = calibrationSettings()
            % Set calibration parameters
            x = inputdlg('Set pixel threshold [counts]', 'Calibration Settings', [1 50],...
                {'10'});
            handles.MOD_constructSpectrum.thresh = str2double(x{1});
        end
        function Sigma = calculateCrossSection(self,filename,wavenumMin,wavenumMax,P,Pa,T)
            % T: Temp in Kelvin
            % Pa: Partial pressure in atm
            % P: total pressure in atm

                load(filename);
                q=(s.iso>0) & (wavenumMin <= s.wnum) & (s.wnum <= wavenumMax);

                s.igas= s.igas(q,:);
                s.iso= s.iso(q,:);
                s.wnum= s.wnum(q,:);
                s.int= s.int(q,:);
                %s.Acoeff=s.Acoeff(q,:);
                s.abroad=s.abroad(q,:);
                s.sbroad=s.sbroad(q,:);
                s.els=s.els(q,:);
                s.abcoef=s.abcoef(q,:);
                s.tsp=s.tsp(q,:);
                s.gn=s.gn(q,:);

                L=length(s.wnum);

                % call for mex function
                g=SpecMe(s.wnum,s.abroad,s.sbroad,s.int,P,Pa,T,L,wavenumMin,wavenumMax);

                % Absorbance
                Sigma=g*(296/T);
        end
           %%---%%%
       function delete(self)
       end
       function self = constructTab(self,hObject)
       end
       end
end