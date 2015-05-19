function spectrumOut = contructNormSpectrum(spectraIn,refNumber,sigNumber)
    
    spectrumOutRef = zeros(size(spectraIn(:,:,1)));
    for j = 1:size(spectraIn,2)
        % Fringe is along I. We'll fit the amplitude first
        Afit = double(spectraIn(:,j,refNumber));
        Afit = reshape(Afit,1,[]);
        if sum(~isnan(Afit)) < 10
            spectrumOutRef(:,j) = NaN;
        else
            ws = warning('off','all');  % Turn off warning
            ppA = polyfit(1:numel(Afit(~isnan(Afit))),Afit(~isnan(Afit)),3);
            warning(ws);  % Turn it back on.
            spectrumOutRef(:,j) = spectraIn(:,j,refNumber)./polyval(ppA,1:numel(Afit))';
        end
    end

    spectrumOutSig = zeros(size(spectraIn(:,:,1)));
    for j = 1:size(spectraIn,2)
        % Fringe is along I. We'll fit the amplitude first
        Afit = double(spectraIn(:,j,sigNumber));
        Afit = reshape(Afit,1,[]);
        if sum(~isnan(Afit)) < 10
            spectrumOutRef(:,j) = NaN;
        else
            ws = warning('off','all');  % Turn off warning
            ppA = polyfit(1:numel(Afit(~isnan(Afit))),Afit(~isnan(Afit)),3);
            warning(ws);  % Turn it back on.
            spectrumOutSig(:,j) = spectraIn(:,j,sigNumber)./polyval(ppA,1:numel(Afit))';
        end
    end
    
    spectrumOut = 1 - reshape(spectrumOutSig,[],1)./reshape(spectrumOutRef,[],1);