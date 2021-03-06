function self = loadMOD_VIPAstruct(self,structIn)
           self.spectrumY = structIn.spectrumY;
           self.spectrumX = structIn.spectrumX;
           self.xAxis = structIn.xAxis;
           self.yAxis = structIn.yAxis;
           self.refSpectrumY = structIn.refSpectrumY;
           self.calibrationImages_reference = structIn.calibrationImages_reference;
           self.calibrationImages_referenceBackground = structIn.calibrationImages_referenceBackground;
           self.calibrationImages_calibrationGas = structIn.calibrationImages_calibrationGas;
           self.calibrationImages_calibrationGasBackground = structIn.calibrationImages_calibrationGasBackground;
           self.fringeImageSize = structIn.fringeImageSize;
           self.spectrumIdcs = structIn.spectrumIdcs;
           self.fringeX = structIn.fringeX;
           self.fringeY = structIn.fringeY;
           self.fringeXcrop = structIn.fringeXcrop;
           self.fringeYcrop = structIn.fringeYcrop;
           self.fringeHeight = structIn.fringeHeight;
           self.numFringes = structIn.numFringes;
           self.calibrationGas = structIn.calibrationGas;
           self.calibrationGasPartialPressure = structIn.calibrationGasPartialPressure;
           self.calibrationGasPathLength = structIn.calibrationGasPathLength;
           self.fringeThreshold = structIn.fringeThreshold;
           self.imgsPerBackground = structIn.imgsPerBackground;
end