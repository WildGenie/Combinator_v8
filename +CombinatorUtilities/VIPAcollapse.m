function collapsedImage = VIPAcollapse(image,fringeIndcs,gaussianWidth,yoffset)
    
    % Get the fringe Indices
    [I,J] = ind2sub(size(image),fringeIndcs);
    
    % in this, fringes are defined to be in X dimension (rows, I) grating
    % dispersion is along Y dimension (columns, J). Therefore, I need to pull
    % out each column to get the fringes.
    
    % Sort the fringe elements for easy use
    rows = unique(J(~isnan(J)),'sorted');
    cols = struct([]);
    for i = 1:numel(rows)
        cols{i} = I(J == rows(i));
    end
    
    collapsedImage = double(image);
    % Fit each fringe element
    for i = 1:numel(rows)
        fprintf('Row %i of %i\n',i,numel(rows));
        minCols = (floor(min(cols{i}))-gaussianWidth);
        if minCols < 1
           minCols = 1; 
        end
        maxCols = (ceil(max(cols{i}))+gaussianWidth);
        if minCols > size(image,1)
           minCols = size(image,1); 
        end
        xfit = minCols:maxCols;
        yfit = double(image(xfit,rows(i)));
        col = cols{i};
        startfit = zeros(1,numel(col)*3+1);
        startfit(1) = yoffset;
        for j = 1:numel(col)
            startfit(3*j-1) = image(round(col(j)),round(rows(i))) - yoffset;
            if isnan(startfit(3*j-1))
                startfit(3*j-1) = nanmean(image(round([col(j)-1 col(j) col(j)+1]),round(rows(i)))) - yoffset;
            end
            startfit(3*j-0) = gaussianWidth;
            startfit(3*j+1) = col(j);
        end
%          startfit
%          figure;plot(xfit,yfit);
%          hold on;
%          plot(xfit,multiPeakNormalizedGaussianFun(startfit,xfit),'r');
%         return;
        imageColumnFit = nlinfit(xfit,yfit,@multiPeakNormalizedGaussianFun,startfit);
        yfitted = multiPeakNormalizedGaussianFun(imageColumnFit,xfit);
        
        % Construct the new delta function
        multiDeltaParams = imageColumnFit;
        multiDeltaParams(1) = 0;
        for j = 1:numel(col)
            multiDeltaParams(3*j-1) = imageColumnFit(3*j-1)*sqrt(pi)*imageColumnFit(3*j-0);
            multiDeltaParams(3*j-0) = 0;
            multiDeltaParams(3*j+1) = round(col(j));
        end
        multiDelta = multiPeakNormalizedGaussianFun(multiDeltaParams,xfit);
        collapsedImage(xfit,rows(i)) = yfit + multiDelta - yfitted;
        %cols{i} = I(J == rows(i));
%         figure;plot(xfit,yfit);
%         hold on;
%         plot(xfit,yfitted,'g');
    end
        
    % Plot the fringes for the user
    figure;
    plotIndcsOnImage(collapsedImage,[]);%fringeIndcs);
end