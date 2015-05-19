function [spectrumOut, weights] = contructNormSpectrumV6(self,spectraIn,refNumber,sigNumber,polydegree)
    if refNumber > size(spectraIn,3)
       errordlg('Reference image number is larger than the total number of images')
       return
    end
    if sigNumber > size(spectraIn,3)
       errordlg('Signal image number is larger than the total number of images')
       return
    end
    
%     figure;plot(reshape(spectraIn(:,:,sigNumber),[],1));
%     figure;plot(reshape(spectraIn(:,:,refNumber),[],1));
%     error
    
    spectrumOut = -log(spectraIn(:,:,sigNumber)./spectraIn(:,:,refNumber));
    %weights = repmat(nanmean(spectraIn(:,:,sigNumber),1),size(spectraIn,1),1).*...
    %        repmat(nanmin(spectraIn(:,:,sigNumber),[],1) > 400 & nanmin(spectraIn(:,:,refNumber),[],1) > 400,size(spectraIn,1),1);;
    weights = repmat(nanmean(spectraIn(:,:,sigNumber),1) > 800 & nanmean(spectraIn(:,:,refNumber),1) > 800,size(spectraIn,1),1);

    return

    spectrumOutSig = zeros(size(spectraIn(:,:,1)));
    for j = 1:size(spectraIn,2)
        spectrumOutSig(:,j) = spectraIn(:,j,sigNumber)./spectraIn(:,j,refNumber);
        % Fringe is along I. We'll fit the amplitude first
        Afit = double(spectrumOutSig(:,j));
        Afit = reshape(Afit,[],1);
        if sum(~isnan(Afit)) < 10
            spectrumOutSig(:,j) = NaN;
        else
            if polydegree >= 0
                ws = warning('off','all');  % Turn off warning
                x = (1:numel(Afit))';
                
                xfit = x(~isnan(Afit));
                yfit = Afit(~isnan(Afit));
                ppA = polyfit(xfit, yfit,double(polydegree));
                alpha = 20;
                w = exp(-alpha*abs(1-yfit./polyval(ppA,xfit)));
                
                ppA = wpolyfit(xfit,yfit,double(polydegree),w);
                
                % Faster polyfit
                    %ppA = zeros(polydegree+1,numel(Afit));
%                     M = repmat(x,1,polydegree+1);
%                     M = bsxfun(@power,M,0:double(polydegree));
%                     ppA = M\Afit;
                
%                 if sum(~isnan(M*ppA))>50
%                     figure;plot(spectrumOutSig(:,j));
%                     (M*ppA)
%                     figure;plot((M*ppA));
%                     error
%                 end
                
                %warning(ws);  % Turn it back on.
                spectrumOutSig(:,j) = spectrumOutSig(:,j)./polyval(ppA,1:numel(Afit))';
                %spectrumOutSig(:,j) = spectrumOutSig(:,j)./(M*ppA);
            else
                spectrumOutSig(:,j) = spectrumOutSig(:,j);
            end
        end
    end
    
    spectrumOut = spectrumOutSig;