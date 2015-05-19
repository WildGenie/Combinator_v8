function self = constructTimeDynamicsPlot(self,varargin)
         
         % Get input options
         inputOptions = struct(varargin{:});
         
         if ~isfield(inputOptions,'plotType')
             inputOptions.plotType = 'AveragedSpectrum';
         end
         
         switch inputOptions.plotType
             case 'AveragedSpectrum'
                 % Check for the required inputs
                 if ~isfield(inputOptions,'backgroundSpectra')
                     error('The backgroundSpectra parameter must be specified.')
                 end
                 if ~isfield(inputOptions,'signalSpectra')
                     error('The signalSpectra parameter must be specified.')
                 end
                 if isfield(inputOptions,'spectrumWavenumber')
                     self.constructTimeDynamicsPlot_spectrumWavenumber = inputOptions.spectrumWavenumber;
                 else
                     error('The signalSpectra parameter must be specified.')
                 end
                 if isfield(inputOptions,'clearAverage') && inputOptions.clearAverage == true
                     self.constructTimeDynamicsPlot_summedSpectra = struct([]);
                     self.constructTimeDynamicsPlot_averageNum = 1;
                     self.constructTimeDynamicsPlot_weightedSummedSpectra = struct([]);
                     self.constructTimeDynamicsPlot_weightSum = struct([]);
                 end
                 
                 % Set the relevant parameters
                 bkgSpectra = inputOptions.backgroundSpectra;
                 signalSpectra = inputOptions.signalSpectra;
                 
                 % Subtract the background 
                 theSpectraMinusBKG = signalSpectra - repmat(bkgSpectra(:,:,1),[1 1 size(signalSpectra,3)]);
                 theSpectraMinusBKG(theSpectraMinusBKG < 50) = NaN;

                 % Average the spectra
                 if self.constructTimeDynamicsPlot_averageNum == 1
                    self.constructTimeDynamicsPlot_summedSpectra = zeros(size(theSpectraMinusBKG));
                    self.constructTimeDynamicsPlot_weightedSummedSpectra = zeros(size(theSpectraMinusBKG));
                    self.constructTimeDynamicsPlot_weightSum = zeros(size(theSpectraMinusBKG));
                 end
                 for i = 1:size(theSpectraMinusBKG,3);
                    [plotSpectrum,weights] = self.contructNormSpectrumV6(theSpectraMinusBKG,self.refSpecNum,i,self.polydegree);
                    self.constructTimeDynamicsPlot_summedSpectra(:,:,i) = self.constructTimeDynamicsPlot_summedSpectra(:,:,i) + plotSpectrum;
                    
                    weights(isnan(weights)) = 0;
                    plotSpectrum(isnan(plotSpectrum)) = 0;
                    self.constructTimeDynamicsPlot_weightedSummedSpectra(:,:,i) = self.constructTimeDynamicsPlot_weightedSummedSpectra(:,:,i) + weights.*plotSpectrum;
                    self.constructTimeDynamicsPlot_weightSum(:,:,i) = self.constructTimeDynamicsPlot_weightSum(:,:,i) + weights;
                 end
                 self.constructTimeDynamicsPlot_averageNum = self.constructTimeDynamicsPlot_averageNum + 1;
                 % Update the plot
                 if ~self.noPlotUpdate
                    self.updatePlot(NaN,NaN);
                 end
         end
end