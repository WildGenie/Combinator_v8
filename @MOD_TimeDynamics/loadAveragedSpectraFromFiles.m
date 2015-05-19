function self = loadAveragedSpectraFromFiles(self,hObject,eventdata)
    [filename,filepath] = uigetfile('*.avgSpectra',sprintf('Load files...'),self.lastSaveLoadDirectory,'MultiSelect', 'off');
    if ~isequal(filename,0) && ~isequal(filepath,0)
       filenames = fullfile(filepath,filename);
       self.lastSaveLoadDirectory = filepath;
    else
        return;
    end
    
    if ~iscell(filenames)
       filenames = {filenames}; 
    end
    
    filename = filenames{1};
    data = load(filename,'-mat');
    
    self.constructTimeDynamicsPlot_summedSpectra = data.summedSpectra;
    self.constructTimeDynamicsPlot_averageNum = data.averageNum;
    self.constructTimeDynamicsPlot_spectrumWavenumber = data.spectrumWavenumber;
    self.constructTimeDynamicsPlot_relativeAcquireTime = data.relativeAcquireTime;
    self.constructTimeDynamicsPlot_integrationTime = data.integrationTime;
    self.constructTimeDynamicsPlot_chemInfo = data.chemInfo;
    self.constructTimeDynamicsPlot_spectrumInfo = data.spectrumInfo;
    
     % Update the plot
     self.updatePlot(NaN,NaN);
end