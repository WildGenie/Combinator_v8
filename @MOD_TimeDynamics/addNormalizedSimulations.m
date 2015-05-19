function self = addNormalizedSimulations(self,varargin)
   
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
        [filename,filepath] = uigetfile('*.simSpec',sprintf('Load files...'),self.lastSaveLoadDirectory,'MultiSelect', 'on');
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
        j = numel(self.constructTimeDynamicsPlot_simulations);
        self.constructTimeDynamicsPlot_simulations(j+1).filename = filenames{i};
        self.constructTimeDynamicsPlot_simulations(j+1).normalized = true;
    end
    if ishandle(h_waitbar)
        close(h_waitbar);
    end
end