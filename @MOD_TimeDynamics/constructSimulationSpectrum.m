function [outputSpectrumX, outputSpectrumY] = constructSimulationSpectrum( self, spectrumStruct, xLims, yNormValue )
    simulationFilename = spectrumStruct.filename;
    
    % Check the file type
    [~,~,ext] = fileparts(simulationFilename);
    if strcmp(ext,'.simSpec')
        data = load(simulationFilename,'-mat');
        x = data.wavenumber;
        indcs = find(x > xLims(1) & x < xLims(2));
        outputSpectrumX = x(indcs);
        outputSpectrumY = data.crossSection(indcs);
    else
        error('not implemented')
        data = csvread(self.simFilename);
        simulationWavenumber = data(:,1);
        Absorbance = data(:,2);
    end
    
    
    if spectrumStruct.normalized == true
        outputSpectrumY = outputSpectrumY./nanmax(outputSpectrumY).*yNormValue;
    end

end

