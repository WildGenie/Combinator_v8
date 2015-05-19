function [voigt_real, voigt_imag] = complex_voigt(v, v0, Doppler_width, homog_width)
c = 3e8;
G = 0;
detuning = (v-v0);
x = detuning*sqrt(log(2))/Doppler_width;
y = sqrt(log(2)*(1+G))*homog_width/Doppler_width;
a=complex(x,y);

voigt= cef(a,1000);
peak_value = sqrt(log(2)/pi)/Doppler_width;
% 2*c*1e2*sqrt(pi*log(2))/half_width_rad;
voigt_real = peak_value*real(voigt);
voigt_imag = peak_value*imag(voigt);
