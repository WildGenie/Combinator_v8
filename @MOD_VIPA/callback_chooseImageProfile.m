function self = callback_chooseImageProfile( self,hObject,eventdata)
%CALLBACK_CHOOSEIMAGEPROFILE Summary of this function goes here
%   Detailed explanation goes here

    % Get image from screen
    fringeImage = get(self.imageHandle,'CData')';
    self.fringeImageSize = size(fringeImage');

    % Select a profile
    h = figure;imagesc(fringeImage');
    [cx,cy,c] = improfile;
    figure;plot(c);
    close(h);

    % Save indices as indices
    fringeImageIdcsCrop = sub2ind(size(fringeImage),...
        round(cx),...
        round(cy));

    % Flip the fringe indices
    %fringeImageIdcsCrop = flipud(fringeImageIdcsCrop);

    self.spectrumIdcs = fringeImageIdcsCrop(:);

    % Save spectrumX
    self.spectrumX = 1:numel(self.spectrumIdcs);

end

