function collapsedImage = VIPAcollapseV2(image,fringeIndcs,gaussianWidth,yoffset)
    
    %%%% CHANGE THIS TO BETTER METHOD %%%%
    % Get the fringe Indices
    image = double(image)./max(double(image(:)));
    numfringes = 39;%2*sum(diff(fringeIndcs) > 10);
    pixelsPerFringe = size(fringeIndcs)/numfringes;
    if round(pixelsPerFringe) ~= pixelsPerFringe
       error('Pixels per fringe is not integer') 
    end
    fringes = reshape(fringeIndcs,[],numfringes);
    %figure;plot(fringes(:,1));
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    % Construct the fitting startpoint
    startfit = zeros(1,numfringes*9+1);
    startfit(1) = yoffset;
    for j = 1:numfringes
        % Get the fringe Indices
        [I,J] = ind2sub(size(image),fringes(:,j));
        fringesRounded = sub2ind(size(image),round(I),round(J));
        % Fringe is along I. We'll fit the amplitude first
        Afit = double(image(fringesRounded(~isnan(fringesRounded))));
        ppA = polyfit(J(~isnan(fringesRounded)),Afit,2);
        startfit((9*(j-1)+2):(9*(j-1)+2+2)) = ppA;
        % We'll fit the width next
        startfit((9*(j-1)+3+2):(9*(j-1)+4+2)) = 0;
        startfit((9*(j-1)+5+2):(9*(j-1)+5+2)) = gaussianWidth;
        % We'll fit the start position last
        ppI = polyfit(J(~isnan(fringesRounded)),I(~isnan(fringesRounded)),2);
        %ppI(1:2) = 0;
        startfit((9*(j-1)+6+2):(9*(j-1)+8+2)) = ppI;
    end
    
    % Construct the fringe
    [X,Y] = meshgrid(1:size(image,2),1:size(image,1));
    Z=multiPeakNormalizedVIPAGaussianFun(startfit,X,Y);
    %Z=multiPeakNormalizedVIPAGaussianFun([0 0 0 100 0 0 2 0 0.1 50],X,Y);
    
%     figure;
%     plotIndcsOnImage(Z,fringeIndcs);
%     figure;
%     plotIndcsOnImage(image,fringeIndcs);
%     return
    
    % Image to fit to
    [I,J] = ind2sub(size(image),fringeIndcs);
    minI = (floor(min(I))-gaussianWidth);
    if minI < 1
       minI = 1; 
    end
    maxI = (ceil(max(I))+gaussianWidth);
    if maxI > size(image,1)
       maxI = size(image,1); 
    end
    minJ = min(J);
    maxJ = max(J);
    %[Ifit,Jfit] = meshgrid(minJ:maxJ,minI:maxI);
    %fitIndcs = sub2ind(size(image),minI:maxI,minJ:maxJ);
    Xfit = X(minI:maxI,minJ:maxJ);
    Yfit = Y(minI:maxI,minJ:maxJ);
    ImageFit = image(minI:maxI,minJ:maxJ);
    ImageMask = (~isnan(ImageFit));
    fitfun = @(v) ImageMask.*(multiPeakNormalizedVIPAGaussianFun(v,Xfit,Yfit) - double(ImageFit));
    opts = optimset('Display','Iter');
%     figure;plotIndcsOnImage(multiPeakNormalizedVIPAGaussianFun(startfit,Xfit,Yfit),[]);
%     figure;plotIndcsOnImage(ImageFit,[]);
%     return
    %fitfun = @(v,X) multiPeakNormalizedGaussianFun(v,X(1:(numel(X)/2)),X((numel(X)/2+1):end));
    %nlinfit([Xfit Yfit],fitfun,startfit);
    fitparams = lsqnonlin(fitfun,startfit,[],[],opts);
    collapsedImage = image + ...
        multiPeakNormalizedVIPADeltaFun(fitparams,X,Y) - ...
        multiPeakNormalizedVIPAGaussianFun(fitparams,X,Y);

    
end