function [Center,FWHM,Area] = fitGaussianLineshape(self,varargin)
    %------------ Input Argument Checking -----------
    args = struct();
    args.interactive = true;
    args.fitNums = 0; %fit all spectra

    % Check to see if we have arguments
    if nargin > 1 && ischar(varargin{1})
        p = inputParser;
        if verLessThan('matlab','8.0.1')
            p.addParamValue('interactive',args.fitNums,@islogical);
            p.addParamValue('fitNums',args.fitNums,@isnumeric);
        else
            p.addParameter('interactive',args.fitNums,@islogical);
            p.addParameter('fitNums',args.fitNums,@isnumeric);
        end
        p.parse(varargin{:});
        args = p.Results;
    end
    % -----------------------------------------------

    % Need to select a portion of the spectrum
    disp('Warning (fitInstrumentLineshape): need to make image number a variable');
    
    specNum = 26;
    x = self.constructTimeDynamicsPlot_spectrumWavenumber;
    y = reshape(self.constructTimeDynamicsPlot_summedSpectra(:,:,specNum),[],1)/self.constructTimeDynamicsPlot_averageNum;
    
    axes_xlim = get(self.axes,'XLim');
    cropIndcs = find(x > axes_xlim(1) & x < axes_xlim(2));
    xcrop = x(cropIndcs);
    ycrop = y(cropIndcs);
    
    xs = xcrop;
    ys = ycrop;
    
    % Fit the data to a gaussian profile
    [~,ind] = max(ys);
    G = @(FWHM,x0,x) exp(-(x-x0).^2/(FWHM/sqrt(2*log(2))/2)^2/2)/(FWHM/sqrt(2*log(2))/2)/sqrt(2*pi);
    fun = @(params,x) params(1)*G(params(3),params(2),x) + params(4);
    params0 = [(max(ys)-min(ys))/30 xs(ind) (max(xs)-min(xs))/10 0];

    if args.interactive
        figure; plot(xs,ys); hold on; plot(xs,fun(params0,xs),'g');
    end
    
    params = nlinfit(xs,ys,fun,params0);
    
    if args.interactive
        plot(xs,fun(params,xs),'r');
        title(sprintf('Center: %f cm^{-1}\nGaussian FWHM: %f (%f MHz)\nArea: %g cm^{-1}',params(2),params(3)*29979.2458,params(3)*29979.2458,params(1)));
    end
    
    Center = params(2);
    FWHM = params(3);
    Area = params(1);
end