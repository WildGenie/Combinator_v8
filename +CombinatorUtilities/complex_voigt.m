function [voigt_real, voigt_imag] = complex_voigt(v, v0, Gaussian_FWHM, Lorentz_FWHM)
G = 0;
detuning = (v-v0);
x = detuning*sqrt(log(2))/abs(Gaussian_FWHM/2);
y = sqrt(log(2)*(1+G))*abs(Lorentz_FWHM/2)/abs(Gaussian_FWHM/2);
a=complex(x,y);

voigt= cef(a,1000);
peak_value = sqrt(log(2)/pi)/abs(Gaussian_FWHM/2);
% 2*c*1e2*sqrt(pi*log(2))/half_width_rad;
voigt_real = peak_value*real(voigt);
voigt_imag = peak_value*imag(voigt);
