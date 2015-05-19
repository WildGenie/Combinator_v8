function self = saveAveragedSpectraToFile(self,hObject,eventdata)
    % Save the averaged spectra to a file
    [filename,filepath] = uiputfile('*.avgSpectra','Save Averaged Spectra As...',self.lastSaveLoadDirectory);
    if ~isequal(filename,0) && ~isequal(filepath,0)
       [~,filename,~] = fileparts(filename);
       saveFilename = fullfile(filepath,filename);
       self.lastSaveLoadDirectory = filepath;
    else
       return;
    end
    
    summedSpectra = self.constructTimeDynamicsPlot_summedSpectra;
    averageNum = self.constructTimeDynamicsPlot_averageNum;
    spectrumWavenumber = self.constructTimeDynamicsPlot_spectrumWavenumber;
    relativeAcquireTime = self.constructTimeDynamicsPlot_relativeAcquireTime;
    integrationTime = self.constructTimeDynamicsPlot_integrationTime;
    chemInfo = self.constructTimeDynamicsPlot_chemInfo;
    spectrumInfo = self.constructTimeDynamicsPlot_spectrumInfo;
    
    save(sprintf('%s.avgSpectra',saveFilename),'-v6','summedSpectra','averageNum','spectrumWavenumber','relativeAcquireTime','integrationTime','chemInfo','spectrumInfo');
end