function spectrum = simulateVoigtAlphaSpectrum( wavenumber, crossSection, lorentzianFWHM, gaussianFWHM )
    %Constructs a voigt cross Section spectrum with the input parameters.
    single_pass = L.*Ss.*peak_att_Voigt.*conc.*pressure./atm_press
    
    abs_spectrum = single_pass;
    disp_spectrum = 0;

end

