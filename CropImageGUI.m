function position = CropImageGUI( image )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
h1 = figure;
imagesc(image);
h = imrect;
position = wait(h);
close(h1);
end

