function self = saveSpectraToFile(filename)
    
    summedSpectra = constructTimeDynamicsPlot_summedSpectra;
    averageNum = constructTimeDynamicsPlot_averageNum;
    spectrumWavenumber = constructTimeDynamicsPlot_spectrumWavenumber;
    relativeAcquireTime = constructTimeDynamicsPlot_relSpectrumTime;
    integrationTime = constructTimeDynamicsPlot_integrationTime;
    chemInfo = constructTimeDynamicsPlot_chemInfo;
    spectrumInfo = constructTimeDynamicsPlot_spectrumInfo;
    
    save(filename,'-v6','summedSpectra','averageNum','spectrumWavenumber','relativeAcquireTime','integrationTime','chemInfo','spectrumInfo');

    
end