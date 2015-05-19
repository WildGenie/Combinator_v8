function h = plotIndcsOnImage(image,indcs)
    % Plot the fringes for the user
    h = imagesc(image'); hold on;
    [I,J] = ind2sub(size(image),indcs);
    scatter(I,J,'.r');
end