function self = loadWavenumAxisFromAveragedSpectraFile(self,varargin)
    %------------ Input Argument Checking -----------
    args = struct();
    args.interactive = true;
    args.filename = '';

    % Check to see if we have arguments
    if nargin > 1 && ischar(varargin{1})
        p = inputParser;
        if verLessThan('matlab','8.0.1')
            p.addParamValue('filename',args.filename,@ischar);
        else
            p.addParameter('filename',args.filename,@ischar);
        end
        p.parse(varargin{:});
        args = p.Results;
    end
    % -----------------------------------------------

    if isempty(args.filename)
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
    else
        filename = args.filename;
    end
        
    data = load(filename,'-mat');
    
    if size(self.constructTimeDynamicsPlot_summedSpectra,1)*size(self.constructTimeDynamicsPlot_summedSpectra,2) == numel(data.spectrumWavenumber)
        self.constructTimeDynamicsPlot_spectrumWavenumber = data.spectrumWavenumber;
    else
        errordlg('Wavenumber axis in file is not the same size as the current spectrum');
        return
    end

     % Update the plot
     self.updatePlot(NaN,NaN);
end