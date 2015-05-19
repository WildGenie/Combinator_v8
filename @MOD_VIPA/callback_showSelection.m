function self = callback_showSelection(self,hObject,eventdata)
    figure;
    plotIndcsOnImage(get(self.imageHandle,'CData')',self.spectrumIdcs(:));
end