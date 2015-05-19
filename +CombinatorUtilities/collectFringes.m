function [out fringeX fringeY] = collectFringes(pic,bckg,thresh)

fringeX = [];
fringeY = [];

% filtering flags and settings
%--------------------------------
% Filter #1 - 2D background subtraction from images
baseline_subtract = 2; % 0 is no subtraction, 1 is Mike's method, 2 is using imopen
number_of_iterations=30; % only for Mike's method
disk_size = 5; % only for imopen method

% fringe finding algorithm
% if derivative is true then use derivative method
% otherwise use threshold method
derivative = false;

rmax = size(pic,1);
rmid = floor(rmax/2);
imgSize = size(bckg);

%FILTER #1
%
% Finds baseline intensity of the 'bckg' picture using a 'min_finder' algorithm.
% basically very low pass filter
%---------------------------------------------------------------------
switch baseline_subtract
    case 0
        baseline_bckg = zeros(imgSize);
        baseline_pic = zeros(imgSize);
    case 1
        baseline = bckg;
        ssize = length(baseline(:)); % make 1D array
        temp1 = baseline(:);
        temp2 = baseline(:);
        % find lowest of point or average of points +/- k away for each point l,
        % repeat for k iterations
        for k = 1:number_of_iterations
            for l = (1+k):(ssize-k)
                temp2(l) = min(temp1(l),(temp1(l+k)+temp1(l-k))/2);
            end
            temp1 = temp2;
        end
        baseline_bckg = reshape(temp1,imgSize); % reform into 2D array
        % repeat for sample picture
        baseline = pic;
        ssize = length(baseline(:)); % make 1D array
        temp1 = baseline(:);
        temp2 = baseline(:);
        % find lowest of point or average of points +/- k away for each point l,
        % repeat for k iterations
        for k = 1:number_of_iterations
            for l = (1+k):(ssize-k)
                temp2(l) = min(temp1(l),(temp1(l+k)+temp1(l-k))/2);
            end
            temp1 = temp2;
        end
        baseline_pic = reshape(temp1,imgSize); % reform into 2D array
    case 2
        baseline_bckg = imopen(bckg, strel('disk', disk_size));
        baseline_pic = imopen(pic, strel('disk', disk_size));
end

pic = imsubtract(pic, baseline_pic);
bckg = imsubtract(bckg, baseline_bckg);

% Determine the number of fringes
% iidx will automaticly become the second minimum.
%--------------------------------------------------------------------------

fringeProfile =  sum(bckg((rmid-5):(rmid+5),:),1)/11;     % sum(bckg,1);
% average up values +/- 5 points from center line to eliminate error from
% intensity noise or absorption feature

% if istest, plot(fringeProfile),pause;close; end
if derivative
    fringeDiff = diff(fringeProfile);
else
    fringeDiff = fringeProfile - thresh; %subtract threshold value
end
poss = find(fringeDiff >= 0); % poss is list of indicies for points >= threshold
idx = 1;  %idx is index of poss
fringeN = 1; %fringe number

picv = [];
bckgv = [];
fringeX = [];
fringeY = [];

while idx < length(poss)-10
    % skips the first fringe (in case it's a partial fringe) then finds
    % beginning of next fringe and the beginning of the third fringe the
    % next iteration goes back to the beginning of the second fringe and
    % skips over that one (since it was already counted) to find the
    % beginning of the third and fourth fringes
    for k = 1:2
        while poss(idx)+1 == poss(idx+1) % if next point in fringeDiff is also positive
            idx = idx + 1;
        end
        idx = idx + 1; % steps to first point in next fringe
        if k == 1; iidx = poss(idx); oldidx = idx; end    
        % iidx is index in fringeDiff
    end
    fidx = poss(idx-1); % steps back to last point in previous fringe so iidx is first point in fringe
    % and fidx is last point
    [maxI,midx] = max(bckg(rmid, iidx:fidx)); % find max of finge, midx is index within list of iidx->fidx 
    
    %w = floor((fidx-iidx+1)/3); % set some width
    wset = 3;       % hlf-width of fringe to average over
    
    midx = iidx + midx-1; %!!!  converts to index in fringeDiff
    %steps up fringe vertically and find max
    for ridx = rmid:rmax;
        w = wset;
        if  ((midx - w) < 1) || ((midx + w) > imgSize(2))
            w = min(midx - 1, imgSize(2) - midx);
        end
        [maxI,peakx] = max(bckg(ridx, (midx-w):(midx+w)));
        midx = (midx-w) + peakx-1; %!!!
        if  ((midx - w) < 1) || ((midx + w) > imgSize(2))
            w = min(midx - 1, imgSize(2) - midx);
        end
        %average over width 
        bckgv(ridx,fringeN) = sum(bckg(ridx, (midx-w):(midx+w)),2)/(2*w+1);
        picv(ridx,fringeN) = sum(pic(ridx, (midx-w):(midx+w)),2)/(2*w+1);
        fringeX(ridx,fringeN) = ridx;
        fringeY(ridx,fringeN) = midx;
    end
    %repeat vertically down fringe
    [maxI,midx] = max(bckg(rmid-1,iidx:fidx));
    midx = iidx + midx-1; %!!! 
    for ridx = (rmid-1):-1:1;
        w = wset;
        if  ((midx - w) < 1) || ((midx + w) > imgSize(2))
            w = min(midx - 1, imgSize(2) - midx);
        end
        [maxI,peakx] = max(bckg(ridx, (midx-w):(midx+w)));
        midx = (midx-w) + peakx-1; %!!!
        if  ((midx - w) < 1) || ((midx + w) > imgSize(2))
            w = min(midx - 1, imgSize(2) - midx);
        end
        bckgv(ridx,fringeN) = sum(bckg(ridx, (midx-w):(midx+w)),2)/(2*w+1);
        picv(ridx,fringeN) = sum(pic(ridx, (midx-w):(midx+w)),2)/(2*w+1);
        fringeX(ridx,fringeN) = ridx;
        fringeY(ridx,fringeN) = midx;
    end
    fringeN = fringeN + 1;
    idx = oldidx; %go back to beginning of fringe
end

fringes = (bckgv - picv)./(bckgv);
fringes = fringes(end:-1:1,:);
fringeX = fringeX(end:-1:1,:);
fringeY = fringeY(end:-1:1,:);

[fringeL,fringeN] = size(fringes);
out = fringes(:,:);

