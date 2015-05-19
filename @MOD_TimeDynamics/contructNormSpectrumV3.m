function spectrumOut = contructNormSpectrumV3(spectraIn,refNumber,sigNumber)
    
    DEBUGMODE = 1;

    spectrumOutRef = zeros(size(spectraIn(:,:,1)));
    for j = 1:size(spectraIn,2)
        % Fringe is along I. We'll fit the amplitude first
        Afit = double(spectraIn(:,j,refNumber));
        Afit = reshape(Afit,1,[]);
        if sum(~isnan(Afit)) < 10
            spectrumOutRef(:,j) = NaN;
        else
            ws = warning('off','all');  % Turn off warning
            x = 1:numel(Afit);
            ppA = polyfit(x(~isnan(Afit)),Afit(~isnan(Afit)),2);
            warning(ws);  % Turn it back on.
            spectrumOutRef(:,j) = spectraIn(:,j,refNumber);%./polyval(ppA,1:numel(Afit))';
        end
    end

    spectrumOutSig = zeros(size(spectraIn(:,:,1)));
    for j = 1:size(spectraIn,2)
        % Fringe is along I. We'll fit the amplitude first
        Afit = double(spectraIn(:,j,sigNumber));
        Afit = reshape(Afit,1,[]);
        if sum(~isnan(Afit)) < 10
            spectrumOutSig(:,j) = NaN;
        else
            ws = warning('off','all');  % Turn off warning
            x = 1:numel(Afit);
            ppA = polyfit(x(~isnan(Afit)),Afit(~isnan(Afit)),2);
            warning(ws);  % Turn it back on.
            spectrumOutSig(:,j) = spectraIn(:,j,sigNumber);%./polyval(ppA,1:numel(Afit))';
        end
    end
%     figure(10); plot(reshape(double(spectraIn(:,:,refNumber)),[],1),'b'); hold on;
%     plot(reshape(double(spectraIn(:,:,sigNumber)),[],1),'r');
%     hold off;
%     %error;
%     %figure; plot(reshape(double(spectraIn(:,:,refNumber)),[],1),'b'); hold on; plot(reshape(double(spectraIn(:,:,sigNumber+1)),[],1),'r');
%     figure; plot(reshape(spectrumOutRef,[],1),'b'); hold on; plot(reshape(spectrumOutSig,[],1),'r');
%     %ylim([-0.9 1.1]);
%     error;
    spectrumOut = reshape(spectrumOutSig,[],1)./reshape(spectrumOutRef,[],1);