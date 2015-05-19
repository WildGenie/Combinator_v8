[filename,filepath] = uigetfile('*.mat',sprintf('Load files...'),'MultiSelect', 'on');
if ~isequal(filename,0) && ~isequal(filepath,0)
   filenames = fullfile(filepath,filename);
else
    return;
end

if ~iscell(filenames)
   filenames = {filenames}; 
end

% Sort out the filenames of spectra
spectrumFilenames = struct([]);
for i = 1:numel(filenames)
    if isempty(strfind(filenames{i},'_RAWimages'))
        spectrumFilenames{end+1} = filenames{i};
    end
end

%
h_waitbar = waitbar(0,sprintf('Converting File 1 of %i\n',numel(spectrumFilenames)));
for i = 1:numel(spectrumFilenames)
    data = load(spectrumFilenames{i});
    if ishandle(h_waitbar)
        waitbar((i-1)/numel(spectrumFilenames),h_waitbar,sprintf('Converting File %i of %i\n',i,numel(spectrumFilenames)));
    else
        break;
    end
    
    bkgSpectra = data.bkgSpectra;
    sigSpectra = data.theSpectra;
    spectrumWavenumber = 1e4./data.spectrumX;
    pulseEnergy = NaN;
    
    %%% TODO:CHANGE THIS %%%
    % Set up the chemInfo structure
    chemInfo = struct();
    chemInfo.pulseEnergy = pulseEnergy;
    spectrumInfo = struct();
    spectrumInfo.acquireTime = NaN;%lastAcquire;
    % Set up the integration time and relative acquire time
    integrationTime = 50e-6;
    frameRate = 250;
    photolysisOffset = 400e-6;
    photolysisImage = 101;
    relativeAcquireTime = (1:size(sigSpectra,3) - photolysisImage)/frameRate+photolysisOffset;
    
   save(sprintf('%s.rawSpectra',spectrumFilenames{i}),'-v6','bkgSpectra','sigSpectra','spectrumWavenumber','relativeAcquireTime','integrationTime','chemInfo','spectrumInfo');
end
close(h_waitbar);