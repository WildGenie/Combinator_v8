function imCropped = CropImage( image,position )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
position = int32(position);
xmin = position(1);
ymin = position(2);
width = position(3);
height = position(4);

imCropped = image(ymin:(ymin+height),xmin:(xmin+width));
end

