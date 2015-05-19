function self = updatePlot(self,hObject,eventdata,varargin)
         
         % Get input options
         inputOptions = struct(varargin{:});
         
         if ~isfield(inputOptions,'axesHandle')
             inputOptions.axesHandle = self.axes;
         end
         
         if isempty(inputOptions.axesHandle)
             figure;
             inputOptions.axesHandle = axes();
         end
         
         plotAxes = inputOptions.axesHandle;
         
         % Construct each of the required plots
         currentInfo = struct();
         currentInfo.XLim = get(plotAxes,'XLim');
         currentInfo.YLim = get(plotAxes,'YLim');
         currentInfo.ZLim = get(plotAxes,'ZLim');
         colors = {'k','r','b','m'};
         hold(plotAxes,'off');
         for i = 1:numel(self.specNumsToDisplay)
                weightedAverage = 1;
                if weightedAverage == 1
                    plotSpectrum = self.constructTimeDynamicsPlot_weightedSummedSpectra(:,:,self.specNumsToDisplay(i))./self.constructTimeDynamicsPlot_weightSum(:,:,self.specNumsToDisplay(i));
                else
                    plotSpectrum = self.constructTimeDynamicsPlot_summedSpectra(:,:,self.specNumsToDisplay(i))/self.constructTimeDynamicsPlot_averageNum;
                end
                polyBaselineFit = 1;
                if polyBaselineFit == 1
                    polydegree = 2;
                    for j = 1:size(plotSpectrum,2)
                        Afit = reshape(plotSpectrum(:,j),[],1);
                        x = (1:numel(Afit))';
                        xfit = x(~isnan(Afit));
                        yfit = Afit(~isnan(Afit));

                        ws = warning('off','all');  % Turn off warning
                        ppA = polyfit(xfit, yfit,double(polydegree));
                        wFun = @(x,a,b) 0.5*(1-erf((abs(x)-a)/b));
                        for k = 1
                            ydiff = (yfit-polyval(ppA,xfit));
                            w = wFun(ydiff,std(ydiff),std(ydiff)/4);
                            ppA = self.wpolyfit(xfit,yfit,double(polydegree),w);
                        end
                        warning(ws);  % Turn it back on

                        plotSpectrum(:,j) = plotSpectrum(:,j) - polyval(ppA,x);
                    end
                end
                plot(plotAxes,reshape(self.constructTimeDynamicsPlot_spectrumWavenumber,1,[]),reshape(plotSpectrum,[],1)+(i-1)*self.specOffsetI+self.specOffset,colors{mod(i-1,numel(colors))+1});
                hold(plotAxes,'on');
         end
         
         % Plot the simulations
         for i = 1:numel(self.constructTimeDynamicsPlot_simulations)
                [x,y] = self.constructSimulationSpectrum(self.constructTimeDynamicsPlot_simulations(i),...
                    [min(self.constructTimeDynamicsPlot_spectrumWavenumber(:)) nanmax(self.constructTimeDynamicsPlot_spectrumWavenumber(:))],...
                    self.specOffsetI*0.9);
                plot(plotAxes,x,y-self.specOffsetI+self.specOffset,colors{mod(i-1,numel(colors))+1});
                hold(plotAxes,'on');
         end

         hold(plotAxes,'off');
         if numel(self.constructTimeDynamicsPlot_simulations) > 0
            newYlim = [self.specOffset-self.specOffsetI*1.5 self.specOffset+(numel(self.specNumsToDisplay)+1)*self.specOffsetI];
         else
            newYlim = [self.specOffset-self.specOffsetI self.specOffset+(numel(self.specNumsToDisplay)+1)*self.specOffsetI];
         end
         defaultInfo = struct();
         defaultInfo.XLimMode = 'auto';
         defaultInfo.YLimMode = 'manual';
         defaultInfo.ZLimMode = 'auto';
         defaultInfo.XLim = get(plotAxes,'XLim');
         defaultInfo.YLim = newYlim;
         defaultInfo.ZLim = get(plotAxes,'ZLim');
         defaultInfo.DataAspectRatio = [1 1 2];
         defaultInfo.DataAspectRatioMode = 'auto';
         defaultInfo.PlotBoxAspectRatio = [1 1 1];
         defaultInfo.PlotBoxAspectRatioMode = 'auto';
         defaultInfo.CameraPosition = [1.5000 1.5000 17.3205];
         defaultInfo.CameraViewAngleMode = 'auto';
         defaultInfo.CameraTarget = [1.5000 1.5000 0];
         defaultInfo.CameraPositionMode = 'auto';
         defaultInfo.CameraUpVector = [0 1 0];
         defaultInfo.CameraTargetMode = 'auto';
         defaultInfo.CameraViewAngle = 6.6086;
         defaultInfo.CameraUpVectorMode = 'auto';
         defaultInfo.View = [0 90];
         setappdata(plotAxes, 'matlab_graphics_resetplotview', defaultInfo)
         if currentInfo.XLim(1) > max(self.constructTimeDynamicsPlot_spectrumWavenumber) || currentInfo.XLim(2) < min(self.constructTimeDynamicsPlot_spectrumWavenumber)
            set(plotAxes,'YLim',newYlim);
         else
            set(plotAxes,'XLim',currentInfo.XLim);
            set(plotAxes,'YLim',currentInfo.YLim);
            set(plotAxes,'ZLim',currentInfo.ZLim);
         end
end