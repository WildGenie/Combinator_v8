function self = loadSpectraFromFiles(self,varargin)
   
    %------------ Input Argument Checking -----------
    args = struct();
    args.interactive = true;
    args.filenames = {};

    % Check to see if we have arguments
    if nargin > 1 && ischar(varargin{1})
        p = inputParser;
        p.addOptional('filenames',args.filenames,@iscellstr);
        p.parse(varargin{:});
        args = p.Results;
    end
    % -----------------------------------------------
        
    if isempty(args.filenames)
        [filename,filepath] = uigetfile('*.rawSpectra',sprintf('Load files...'),self.lastSaveLoadDirectory,'MultiSelect', 'on');
        if ~isequal(filename,0) && ~isequal(filepath,0)
           filenames = fullfile(filepath,filename);
           self.lastSaveLoadDirectory = filepath;
        else
            return;
        end

        if ~iscell(filenames)
           filenames = {filenames}; 
        end
    else
        filenames = args.filenames;
    end
    
    %
    h_waitbar = waitbar(0,sprintf('Averaging Spectrum 1 of %i\n',numel(filenames)));
    for i = 1:numel(filenames)
        data = load(filenames{i},'-mat');
        if ishandle(h_waitbar)
            waitbar((i-1)/numel(filenames),h_waitbar,sprintf('Averaging Spectrum %i of %i\n',i,numel(filenames)));
        else
            break;
        end
        if i == 1
            self.constructTimeDynamicsPlot('clearAverage',true,'spectrumWavenumber',data.spectrumWavenumber,'backgroundSpectra',data.bkgSpectra,'signalSpectra',data.sigSpectra);
        else
            self.constructTimeDynamicsPlot('spectrumWavenumber',data.spectrumWavenumber,'backgroundSpectra',data.bkgSpectra,'signalSpectra',data.sigSpectra);
        end
    end
    if ishandle(h_waitbar)
        close(h_waitbar);
    end
    drawnow;
end