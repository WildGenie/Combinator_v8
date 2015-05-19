function self = fitAveragedSpectra(self, ~, ~ )

    if numel(self.constructTimeDynamicsPlot_relativeAcquireTime) ~= size(self.constructTimeDynamicsPlot_summedSpectra,3)
       errordlg('The relativeAcquireTime parameter is not set correctly. Please set it and try again.'); 
       return
    end

    [filename,filepath] = uigetfile('*.simSpec',sprintf('Load Spectra to Fit To'),'MultiSelect', 'on');
    if ~isequal(filename,0) && ~isequal(filepath,0)
       filenames = fullfile(filepath,filename);
    else
        return;
    end
    
    if ~iscell(filenames)
       filenames = {filenames}; 
    end

    fitArray = {};
    for i = 1:numel(filenames)
       [~,~,ext] = fileparts(filenames{i});
       switch ext
           case '.simSpec'
                data = load(filenames{i},'-mat');
                fitArray{end+1} = data.wavenumber;
                fitArray{end+1} = data.crossSection;
                %figure;plot(data.wavenumber,data.crossSection);
                disp('Warning: .simSpec format may change');
           case '.csv'
               error('csv: not implemented')
           case '.specLib'
               error('specLib: not implemented')
       end
    end
    
    %return;
    h_waitbar = waitbar(0,sprintf('Fitting Spectrum 1 of %i\n',size(self.constructTimeDynamicsPlot_summedSpectra,3)));
    betas = zeros(numel(fitArray)/2,size(self.constructTimeDynamicsPlot_summedSpectra,3));
    fittedYs = NaN*zeros(size(self.constructTimeDynamicsPlot_summedSpectra,1)*size(self.constructTimeDynamicsPlot_summedSpectra,2),size(self.constructTimeDynamicsPlot_summedSpectra,3));
    for i = 1:size(self.constructTimeDynamicsPlot_summedSpectra,3)
        if ishandle(h_waitbar)
            waitbar((i-1)/size(self.constructTimeDynamicsPlot_summedSpectra,3),h_waitbar,sprintf('Fitting Spectrum %i of %i\n',i,size(self.constructTimeDynamicsPlot_summedSpectra,3)));
        else
            break;
        end
        fitX = reshape(self.constructTimeDynamicsPlot_spectrumWavenumber,[],1);
        fitY = reshape(self.constructTimeDynamicsPlot_summedSpectra(:,:,i),[],1)/self.constructTimeDynamicsPlot_averageNum;
        fitIndcs = ~isnan(fitX) & ~isnan(fitY);
        [beta fittedY] = LinearArrayFit(fitX(fitIndcs),...
            fitY(fitIndcs),...
            fitArray);
        betas(:,i) = beta;

        fittedYs(fitIndcs,i) = fittedY;
    end
    if ishandle(h_waitbar)
        close(h_waitbar);
    end

    h = figure;
    for i = 1:size(betas,1)
        x = self.constructTimeDynamicsPlot_relativeAcquireTime;
        plot(x,betas(i,:));
        hold on;
    end
    xlabel('Wavenumber [cm^{-1}');
    ylabel('N*L_{eff} [mlc/cm^3 * cm]');
    
     h = figure;
     ha = axes('Parent',h);
     colors = {'k'};
     for i = 1:numel(self.specNumsToDisplay)
            plotSpectrum = reshape(self.constructTimeDynamicsPlot_summedSpectra(:,:,self.specNumsToDisplay(i)),[],1)/self.constructTimeDynamicsPlot_averageNum+(i-1)*self.specOffsetI+self.specOffset;
            plot(ha,self.constructTimeDynamicsPlot_spectrumWavenumber,plotSpectrum,colors{mod(i-1,numel(colors))+1});
            hold(ha,'on');
            plot(ha,self.constructTimeDynamicsPlot_spectrumWavenumber,fittedYs(:,self.specNumsToDisplay(i))+(i-1)*self.specOffsetI+self.specOffset,'r');
     end
end

