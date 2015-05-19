function spectrumOut = contructNormSpectrumV4(spectraIn,refNumber,sigNumber,polydegree)

    spectrumOutSig = zeros(size(spectraIn(:,:,1)));
    for j = 1:size(spectraIn,2)
        spectrumOutSig(:,j) = spectraIn(:,j,sigNumber)./spectraIn(:,j,refNumber);
        % Fringe is along I. We'll fit the amplitude first
        Afit = double(spectrumOutSig(:,j));
        Afit = reshape(Afit,1,[]);
        if sum(~isnan(Afit)) < 10
            spectrumOutSig(:,j) = NaN;
        else
            if polydegree >= 0
                ws = warning('off','all');  % Turn off warning
                x = 1:numel(Afit);
                ppA = polyfit(x(~isnan(Afit)),Afit(~isnan(Afit)),3);
                warning(ws);  % Turn it back on.
                spectrumOutSig(:,j) = spectrumOutSig(:,j)./polyval(ppA,1:numel(Afit))';
            else
                spectrumOutSig(:,j) = spectrumOutSig(:,j);
            end
        end
    end
    
    spectrumOut = spectrumOutSig;