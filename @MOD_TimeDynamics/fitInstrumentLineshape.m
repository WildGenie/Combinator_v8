function self = fitInstrumentLineshape(self,~,~)
    % Need to select a portion of the spectrum
    disp('Warning (fitInstrumentLineshape): need to make image number a variable');
    
    specNum = 26;
    x = self.constructTimeDynamicsPlot_spectrumWavenumber;
    y = reshape(self.constructTimeDynamicsPlot_summedSpectra(:,:,specNum),[],1)/self.constructTimeDynamicsPlot_averageNum;
    
    axes_xlim = get(self.axes,'XLim');
    cropIndcs = find(x > axes_xlim(1) & x < axes_xlim(2));
    xcrop = x(cropIndcs);
    ycrop = y(cropIndcs);
    %h = figure;plot(xcrop,ycrop)
    
    xs = xcrop;
    ys = ycrop;
    %[pind,xs,ys] = selectdata('selectionmode','lasso');
    %close(h);
    
    
    %figure; plot(xs,ys);
    %hold on;
    
    % Fit the data to a voigt profile
    [~,ind] = max(ys);
    %fun = @(params,x) -log(1-params(1)*complex_voigt(x,params(2),params(3),params(4))./complex_voigt(0,0,params(3),params(4)))+params(5);
    %fun = @(params,x) VIPAmolecularLineshape(x,params(2),params(1),params(3),0,params(4))+params(5);
    G = @(FWHM,x0,x) exp(-(x-x0).^2/(FWHM/sqrt(2*log(2))/2)^2/2)/(FWHM/sqrt(2*log(2))/2)/sqrt(2*pi);
    fun = @(params,x) params(1)*G(params(3),params(2),x) + params(4);
    params0 = [max(ys)/30 xs(ind) (max(xs)-min(xs))/50 0];
    %plot(xs,fun(params0,xs));
    %return
    figure; plot(xs,ys); hold on; plot(xs,fun(params0,xs),'g');
    %return
    params = nlinfit(xs,ys,fun,params0);
    plot(xs,fun(params,xs),'r');
    sum((fun(params,min(xs):0.001:max(xs))-params(4))/params(1))*0.001
    %figure; plot(xs,ys); hold on; plot(xs,fun(params,xs),'r'); plot(xs,fun(params0,xs),'g');
    title(sprintf('Center: %f cm^{-1}\nGaussian FWHM: %f (%f MHz)\nArea: %g cm^{-1}',params(2),params(3)*29979.2458,params(3)*29979.2458,params(1)));
    
    
end