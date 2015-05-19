classdef MOD_fitVIPAspectrum < MOD_BASECLASS
   % write a description of the class here.
       properties (Constant)
           moduleName = 'fitVIPAspectrum';
           dependencies = {};
       end
       properties
           % Acquire a spectrum
           spectrumX = [];
           spectrumY = [];
           
           simPlotHandle;
           expPlotHandle;
           fitFrequencyAxisFigureHandle;
           
           % Dependency Handles
           xAxisFitted;
           calibSpectrumXaxis
           calibSpectrumYaxis;
           imageFringeVertExtent;
           imageFringeNumFringes;
           guessLambda = 3.725; %GHz
           guessFSR = 55; %GHz
       end
       methods
       % methods, including the constructor are defined in self block
           function self = MOD_fitVIPAspectrum()
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
           function fitFrequencyAxisFigureHandle = fitFrequencyAxis(self)

                % Clear the previously fitted x axis
                self.xAxisFitted = [];

                load('Icons');
                % Create a uipushtool in the toolbar
                self.fitFrequencyAxisFigureHandle = figure;
                self.expPlotHandle = plot(1:10,1:10); hold on;
                self.simPlotHandle = plot(1:10,1:10,'r'); hold off;
                xlabel('Wavelength [\mum]');

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
                         @self.fitFrequencyAxisPickFreqPoints);

                self.fitFrequencyAxisFigureUpdateSpectrum();
                fitFrequencyAxisFigureHandle = self.fitFrequencyAxisFigureHandle;
           end
        function returnData = getFittedXaxis(self)
            returnData = self.xAxisFitted;
        end
        function self = fitFrequencyAxisFigureShiftLeft(self,hObject,eventdata)
            self.guessLambda = self.guessLambda - 0.001;
            self.fitFrequencyAxisFigureUpdateSpectrum();
        end
        function self = fitFrequencyAxisFigureShiftSet(self,hObject,eventdata)
            x = inputdlg('Enter spectrum center wavenumber [cm-1]:', 'Set Spectrum Center Wavenumber', [1 50],...
                {num2str(1e4./self.guessLambda)});
            self.guessLambda = 1e4./str2double(x{1});
            self.fitFrequencyAxisFigureUpdateSpectrum();
        end
        function self = fitFrequencyAxisFigureShiftRight(self,hObject,eventdata)
            self.guessLambda = self.guessLambda + 0.001;
            self.fitFrequencyAxisFigureUpdateSpectrum();
        end
        function self = fitFrequencyAxisFigureUpdateSpectrum(self)

            % Get the necessary parameters
            imageFringeVertExtent = self.imageFringeVertExtent;
            imageFringeNumFringes = self.imageFringeNumFringes;
            centerlambda = self.guessLambda;
            fsr = self.guessFSR;

            % Convert center lambda to reflambda
            reflambda = 1/(1/centerlambda + fsr*1e9*imageFringeNumFringes/2/299792458*(1e-6));

            % Construct the new x-axis for the spectrum (in microns)
            self.calibSpectrumXaxis = zeros(imageFringeVertExtent,imageFringeNumFringes);
            for k = 1:imageFringeNumFringes
                deltaLambda = fsr * 1e9 * ((reflambda/10^6)^2)/3e8 * 1e6;
                self.calibSpectrumXaxis(:,k) = reflambda + deltaLambda*(k-1) + ...
                    deltaLambda/imageFringeVertExtent*((1:imageFringeVertExtent)-1);
            end
            self.calibSpectrumXaxis = self.calibSpectrumXaxis(:);

            % Construct the spectrum to fit to
            load('06_hit04.mat'); % CH4
            fun = @(params,x) 1-calculate_CH4_midIRcavity_spectrum_fixedGaussian(s,x, 30, params(1)*1e-3, params(2)*1e9);
            simulationWavenumber = min(1e4./self.calibSpectrumXaxis):0.01:max(1e4./self.calibSpectrumXaxis);
            figure(self.fitFrequencyAxisFigureHandle);

            % Actually plot the spectra
            set(self.expPlotHandle,'XData',1e4./self.calibSpectrumXaxis);
            set(self.expPlotHandle,'YData',self.calibSpectrumYaxis);
            set(self.simPlotHandle,'XData',simulationWavenumber);
            set(self.simPlotHandle,'YData',fun([0.1 1],simulationWavenumber)-0.5);
        end
        function self = fitFrequencyAxisPickFreqPoints(self,hObject,eventdata)
        
            % Load spectrum values from MOD_constructSpectrum
            polydegree = 3;
            numPoints = 5;

            HITRANx = 1e4./get(self.simPlotHandle,'XData');
            HITRANy = get(self.simPlotHandle,'YData');
            EXPx = 1e4./get(self.expPlotHandle,'XData');
            EXPy = get(self.expPlotHandle,'YData');

            hfig = figure; hEXPplot = plot(1e4./EXPx,EXPy); hold on; hHITRANplot = plot(1e4./HITRANx,HITRANy,'r'); hpointsPlot = scatter(1e4./mean(EXPx),mean(EXPy),'k*');
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
                x = 1e4./x;

                [~,b]=min(((EXPx-x)/deltaX).^2+((EXPy-y)/deltaY).^2);
                EXPpickedX(i) = EXPx(b(1));
                EXPpickedY(i) = EXPy(b(1));
                [x,y]=ginput(1);
                x = 1e4./x;
                
                [~,b]=min(((HITRANx-x)/deltaX).^2+((HITRANy-y)/deltaY).^2);
                HITRANpickedX(i) = HITRANx(b(1));
                HITRANpickedY(i) = HITRANy(b(1));

                set(hpointsPlot,'XData',[1e4./EXPpickedX(1:i) 1e4./HITRANpickedX(1:i)]);
                set(hpointsPlot,'YData',[EXPpickedY(1:i) HITRANpickedY(1:i)]);
            end

            close(hfig);

            %  Actually Fit the freq axis
            p = polyfit(EXPpickedX,HITRANpickedX,2);
            EXPxFitted = polyval(p,EXPx);
            EXPpickedXFitted = polyval(p,EXPpickedX);
            polyX = min(EXPpickedX):0.0001:max(EXPpickedX);
            figure; scatter(1e4./EXPpickedX,HITRANpickedX); hold on; plot(1e4./polyX,polyval(p,polyX),'r');

            hfig = figure; hEXPplot = plot(1e4./EXPxFitted,EXPy); hold on; hHITRANplot = plot(1e4./HITRANx,HITRANy,'r'); hpointsPlot = scatter(1e4./mean(EXPx),mean(EXPy),'k*');
            set(hpointsPlot,'XData',[1e4./EXPpickedXFitted 1e4./HITRANpickedX]);
            set(hpointsPlot,'YData',[EXPpickedY HITRANpickedY]);

            self.xAxisFitted = EXPxFitted;
        end
        function self = calibrationSettings()
            % Set calibration parameters
            x = inputdlg('Set pixel threshold [counts]', 'Calibration Settings', [1 50],...
                {'10'});
            handles.MOD_constructSpectrum.thresh = str2double(x{1});
        end
           %%---%%%
       function delete(self)
       end
       function self = constructTab(self,hObject)
       end
       end
end