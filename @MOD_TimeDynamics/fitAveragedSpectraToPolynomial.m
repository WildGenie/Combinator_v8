function self = fitAveragedSpectraToPolynomial( self, varargin)
    %------------ Input Argument Checking -----------
    args = struct();
    args.interactive = true;
    args.fitNums = 0; %fit all spectra

    % Check to see if we have arguments
    if nargin > 1 && ischar(varargin{1})
        p = inputParser;
        if verLessThan('matlab','8.0.1')
            p.addParamValue('fitNums',args.fitNums,@isnumeric);
        else
            p.addParameter('fitNums',args.fitNums,@isnumeric);
        end
        p.parse(varargin{:});
        args = p.Results;
    end
    % -----------------------------------------------

    summedSpectra = self.constructTimeDynamicsPlot_summedSpectra;
    averageNum = self.constructTimeDynamicsPlot_averageNum;

    if args.fitNums == 0
        fitNums = 1:size(summedSpectra,3);
    else
       fitNums = args.fitNums; 
    end
    
    polydegree = 5;
    fitPoly = zeros(size(summedSpectra));
    fitCoeff = zeros(size(summedSpectra));
    fitNum = 1;
    h_waitbar = waitbar(0,sprintf('Fitting Spectrum 1 of %i to Polynomial\n',numel(fitNums)));
    for i = fitNums
        if ishandle(h_waitbar)
            waitbar(fitNum/numel(fitNums),h_waitbar,sprintf('Fitting Spectrum %i of %i to Polynomial\n',fitNum,numel(fitNums)));
            fitNum = fitNum+1;
        else
            break;
        end
        for j = 1:size(summedSpectra,2)
            Afit = reshape(summedSpectra(:,j,i),[],1);
            x = (1:numel(Afit))';
            xfit = x(~isnan(Afit));
            yfit = Afit(~isnan(Afit));
            
            ws = warning('off','all');  % Turn off warning
            ppA = polyfit(xfit, yfit,double(polydegree));
            alpha = 20;
            wFun = @(x,a,b) 0.5*(1-erf((abs(x)-a)/b));
            for k = 1:5
                ydiff = (yfit-polyval(ppA,xfit))/averageNum;
                w = wFun(ydiff,std(ydiff),std(ydiff)/4);
                ppA = self.wpolyfit(xfit,yfit,double(polydegree),w);
            end
            warning(ws);  % Turn it back on
            
            wfit = NaN*zeros(size(x));
            wfit(~isnan(Afit)) = w;
            fitCoeff(:,j,i) = wfit;
            fitPoly(:,j,i) = polyval(ppA,x);
%             figure;plot(fitPoly(:,j,i));
%             figure;plot(summedSpectra(:,j,i));
%             error
        end
    end
    if ishandle(h_waitbar)
        close(h_waitbar);
    end
%     figure;plot(reshape((summedSpectra(:,:,26)-fitPoly(:,:,26))/averageNum,[],1));
%     figure;plot(reshape(summedSpectra(:,:,26),[],1)/averageNum);hold('on');
%            plot(reshape(fitPoly(:,:,26),[],1)/averageNum,'r');
%     figure;plot(reshape(fitCoeff(:,:,26),[],1));
    self.constructTimeDynamicsPlot_summedSpectra = summedSpectra-fitPoly;
    
    self.updatePlot(NaN,NaN);
end

