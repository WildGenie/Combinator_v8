function self = callback_AcquireButton(self,hObject,eventdata)

%         % Check if we've been called from the gui.
%         usingTimerForGUIFunction = 1;
%         if isempty(eventdata) && usingTimerForGUIFunction
%             t = timer('TimerFcn',@(x,y)self.callback_AcquireButton(hObject,y),...
%                 'StopFcn',@(x,y)delete(x),...
%                 'StartDelay',0.1);
%             start(t);
%             return;
%         end
        
        % Live image
        %Continue as long as button is pressed
        if (hObject == self.continuousAcquireButton) && (get(hObject, 'value') == 0)
            return
        elseif (hObject == self.singleAcquireButton)
            set(self.continuousAcquireButton,'value',1);
            saveFilename = [];
            fileCounter = 0;
        end

        averaging = 1;%1;
        
        customScan = false;
        if (hObject == self.continuousAcquireButton)
            % Set save file if needed
            [filename,filepath] = uiputfile('*.rawSpectra','Save Spectra As...',self.lastSaveLoadDirectory);
            if ~isequal(filename,0) && ~isequal(filepath,0)
               [~,filename,~] = fileparts(filename);
               saveFilename = fullfile(filepath,filename);
               fileCounter = 0;
               self.lastSaveLoadDirectory = filepath;
               
               prompt = {'Scan Variable (photolysisTimeOffsetUs/chemInfo.*/spectrumInfo.*):','Scan Range:','Number of Averages:'};
               dlg_title = 'Input';
               num_lines = 1;
               def = {'photolysisTimeOffsetUs','0:50:500','20'};
               answer = inputdlg(prompt,dlg_title,num_lines,def);
               if ~isempty(answer)
                  customScan = true;
                  if strcmp(answer{1},'photolysisTimeOffsetUs')
                     customScanVar = 'photolysisTimeOffsetUs';
                     customScanRange = str2num(answer{2});
                     customScanNumAvgs = str2double(answer{3});
                     customScanRangeCounter = 1;
                     customScanAvgCounter = 0;
                  else
                      error('The scan variable must be an accepted input');
                  end 
               end
            else
               saveFilename = [];
               fileCounter = 0;
            end
        else
        end
        
        avgCleared = 0;
        lastAcquire = 0;
        while (get(self.continuousAcquireButton, 'Value') == 1)
            
            % Ask the user to set the scan variable to what is appropriate
            if customScan == true
                customScanAvgCounter = customScanAvgCounter+1;
                if customScanAvgCounter > customScanNumAvgs
                    customScanRangeCounter = customScanRangeCounter+1;
                    customScanAvgCounter = 1;
                    if customScanRangeCounter > numel(customScanRange)
                        disp('Done with Custom Scan')
                       break;
                    end
                end
                
                if (customScanAvgCounter == 1)
                    msgboxText = sprintf('Set %s to %f',customScanVar,customScanRange(customScanRangeCounter));
                    uiwait(msgbox(msgboxText)); 
                    avgCleared = 0;
                end
                
                % Set the custom scan variable
                if strcmp(customScanVar,'photolysisTimeOffsetUs')
                    self.photolysisTimeOffsetUs = customScanRange(customScanRangeCounter);
                end
            end
            
            % Wait the appropriate amount of time
            minTimeBetweenAcquisitions_inDays = self.minTimeBetweenAcquisitions/(3600*24);
            
            drawnow;
            while ((now - lastAcquire) < minTimeBetweenAcquisitions_inDays) &&...
                    (get(self.continuousAcquireButton, 'Value') == 1)
               drawnow
            end
            if (get(self.continuousAcquireButton, 'Value') ~= 1)
               break; 
            end
            if (hObject == self.singleAcquireButton)
                set(self.continuousAcquireButton,'value',0);
            end
            lastAcquire = now;
            
             % Acquire background A
             bkgtimeTic = tic;
%              fprintf('Bkg A...');
%              [bkgSpectra,bkgImages,fringeIndices] = self.dependencyHandles.MOD_VIPA.acquireBackgroundSpectra(3);
%              bkgSpectrumA = bkgSpectra(:,:,1);
%              bkgSpectrumA = reshape(bkgSpectrumA,[],1);
%              bkgSpectrumB = bkgSpectra(:,:,2);
%              bkgSpectrumB = reshape(bkgSpectrumB,[],1);
             bkgtime = toc(bkgtimeTic);

             % Start acquiring the YAG pulse
             %NI5922acquire(uint16(0),15e6,uint32(50),uint32(1));
             
             %pause(0.5);
             
             % Aquire spectra (allocate 1 second for acquisition)
             fprintf('Acquiring at Trig/%i...',self.acqRateDivFactor);
             acceptableAcquire = 0;
             while acceptableAcquire == 0;
                 sigtimeTic = tic;
                 [acqSpectra,acqImages,fringeIndices] = self.dependencyHandles.MOD_VIPA.acquirePhotolysisSpectra(50+3);
                 
                 if ~isempty(acqImages)
                     bkgSpectrumA = acqSpectra(:,:,1);
                     sigSpectra = acqSpectra(:,:,4:end);
                     bkgSpectra = acqSpectra(:,:,1:3);
                     bkgImages = acqImages(:,:,1:3);
                     sigImages = acqImages(:,:,4:end);
                     spectrumWavenumber = self.dependencyHandles.MOD_VIPA.public_getWavenumberAxis();
                     spectrumWavenumber = reshape(spectrumWavenumber,[],1);
                     sigtime = toc(sigtimeTic);

                     thresholdCompare = nanmean(reshape(sigSpectra(:,:,1)-bkgSpectra(:,:,1),[],1));
                     if thresholdCompare > 100
                        acceptableAcquire = 1; 
                     else
                         acceptableAcquire = 0;
                         if ~isempty(saveFilename) || averaging
                            uiwait(msgbox(sprintf('Mean below threshold: %f\nLock the laser and press ok',thresholdCompare)));
                         end
                     end
                 end
                 drawnow;
             end
             
             % Return the YAG pulse data
             YAGdata = 1;%NI5922acquire(uint16(1),15e6,uint32(50),uint32(1));
             
             if isempty(YAGdata)
                error('No YAG fire detected'); 
             end
             
             %figure(10); plot(YAGdata(1,:));% hold on; plot(YAGdata(2,:),'r');
             pulseEnergy = 1;%sum(YAGdata(1,:)-mean(YAGdata(1,30:50)));
             %return

            % Check to see if bad pixels have been detected
            if sum(isnan(sigSpectra)) == 0
               % Bad pixels have not been detected. We'll do that here

                % Find the indices of the bad pixels
                badPixelIndcs = find(double(bkgSpectrumA)<0.75*mean(bkgSpectrumA(:)) | double(bkgSpectrumA(:))>1.5*mean(bkgSpectrumA(:)));
                for i = 1:300
                    sigSpectra(badPixelIndcs + numel(bkgSpectrumA)*(i-1)) = NaN;
                end
            end
             
            
            %%% TODO:CHANGE THIS %%%
            % Set up the chemInfo structure
            chemInfo = struct();
            chemInfo.pulseEnergy = pulseEnergy;
            spectrumInfo = struct();
            spectrumInfo.acquireTime = lastAcquire;
            
            % Set up the integration time and relative acquire time
             integrationTime = self.integrationTimeUs*1e-6;
             frameRate = self.frameRate;
             photolysisTimeOffset = self.photolysisTimeOffsetUs*1e-6;
             photolysisImage = self.photolysisImage;
            relativeAcquireTime = ((1:size(sigSpectra,3)) - double(photolysisImage))/frameRate+photolysisTimeOffset;
            

            % Update the plot if needed
            plottimeTic = tic;
            if ~self.noPlotUpdate
               self.constructTimeDynamicsPlot_relativeAcquireTime = relativeAcquireTime;
               self.constructTimeDynamicsPlot_integrationTime = integrationTime;
               self.constructTimeDynamicsPlot_chemInfo = chemInfo;
               self.constructTimeDynamicsPlot_spectrumInfo = spectrumInfo;

                % Construct the spectra
                if avgCleared == 0
                    self.constructTimeDynamicsPlot('clearAverage',true,'spectrumWavenumber',spectrumWavenumber,'backgroundSpectra',bkgSpectra,'signalSpectra',sigSpectra,'polyFitDisplay',true);
                    avgCleared = 1*averaging;
                else
                    self.constructTimeDynamicsPlot('spectrumWavenumber',spectrumWavenumber,'backgroundSpectra',bkgSpectra,'signalSpectra',sigSpectra,'polyFitDisplay',true);
                end
            end
            drawnow;
            plottime = toc(plottimeTic);
             
            savetimeTic = tic;
            if ~isempty(saveFilename)
               save(sprintf('%s_%i.rawSpectra',saveFilename,fileCounter),'-v6','bkgSpectra','sigSpectra','spectrumWavenumber','relativeAcquireTime','integrationTime','chemInfo','spectrumInfo');
               if self.saveRAWimages
                   save(sprintf('%s_%i_RAWimages.rawVIPA',saveFilename,fileCounter),'-v6','bkgImages','sigImages','fringeIndices','spectrumWavenumber','relativeAcquireTime','integrationTime','chemInfo','spectrumInfo');
               end
               savetime = toc(savetimeTic);
               fprintf('Saved ''%s''\n',sprintf('%s_%i',filename,fileCounter));
               fileCounter = fileCounter + 1;
            end
             savetime = toc(savetimeTic);
             
             %fprintf('\nOther Stats| Sig Max: %f (%f,%f) | bkgStd: %f | S/N: %f \n',nanmax(refSpec-bkgSpectrumA),nanmax(refSpec),nanmin(bkgSpectrumA),sqrt(bkgVar),nanmax(refSpec-bkgSpectrumA)/sqrt(bkgVar));
             fprintf('YAG Pulse| Energy: %f V*s\n',pulseEnergy);
             fprintf('Timing Stats| Bkg: %f s | Sig: %f s | Plot: %f | Save: %f s | Total: %f s\n',bkgtime,sigtime,plottime,savetime,(now-lastAcquire)*24*60*60);
        end
end