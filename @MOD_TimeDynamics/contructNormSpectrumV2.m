function spectrumOut = contructNormSpectrumV2(spectraIn,,refNumber,sigNumber)
    
    DEBUGMODE = 1;

    spectrumOutSig = zeros(size(spectraIn(:,:,1)));
    for j = 1:size(spectraIn,2)
        % Fringe is along I. We'll fit the amplitude first
        Afit = double(spectraIn(:,j,sigNumber));
        Afit = reshape(Afit,1,[]);
        if sum(~isnan(Afit)) < 10
            spectrumOutSig(:,j) = NaN;
        else
            %ws = warning('off','all');  % Turn off warning
            %ppA = polyfit(1:numel(Afit(~isnan(Afit))),Afit(~isnan(Afit)),6);
            x = 1:numel(Afit);
            xfit = x(~isnan(Afit));
            smoothA = smooth(xfit,Afit(~isnan(Afit)));
            %warning(ws);  % Turn it back on.
            smoothAdiv = Afit;
            smoothAdiv(~isnan(Afit)) = smoothA;
%             figure;plot(x,Afit);hold on;
%             plot(x,smoothAdiv,'r');
%             error;
            spectrumOutSig(:,j) = spectraIn(:,j,sigNumber)./smoothAdiv';
        end
    end

    spectrumOut = 1 - reshape(spectrumOutSig,[],1);