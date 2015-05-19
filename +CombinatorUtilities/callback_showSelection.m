function self = callback_showSelection(self)
    figure;
    plotIndcsOnImage(get(self.imageHandle,'CData'),self.spectrumIdcs);
end