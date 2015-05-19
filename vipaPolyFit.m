function spectrum = vipaPolyFit( spectrum )
    if size(spectrum,3) ~= 1
       error('The spectrum must be a 2d array'); 
    end

    polydegree = 3;
    for j = 1:size(spectrum,2)
        Afit = reshape(spectrum(:,j),[],1);
        x = (1:numel(Afit))';
        xfit = x(~isnan(Afit));
        yfit = Afit(~isnan(Afit));

        ws = warning('off','all');  % Turn off warning
        ppA = polyfit(xfit, yfit,double(polydegree));
        wFun = @(x,a,b) 0.5*(1-erf((abs(x)-a)/b));
        for k = 1
            ydiff = (yfit-polyval(ppA,xfit));
            w = wFun(ydiff,std(ydiff),std(ydiff)/4);
            ppA = wpolyfit(xfit,yfit,double(polydegree),w);
        end
        warning(ws);  % Turn it back on

        spectrum(:,j) = spectrum(:,j) - polyval(ppA,x);
    end
end

