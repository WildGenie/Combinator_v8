function [CH4_cavity_spectrum] = calculate_CH4_midIRcavity_spectrum_fixedGaussian(hitran_s,wavenum_scale, pressure, conc, broad)

clear CH4_cavity_spectrum abs_spectrum
linesvals = find((hitran_s.int > 0) & (hitran_s.wnum >= min(wavenum_scale)) & (hitran_s.wnum <= max(wavenum_scale)));

c = 3e8; %m/s
h_bar = 1.055e-34;
kB = 1.38e-23; %J/K=Nm/K=kg m^2/s^2/K
T = 273.15+23; %K
m = 16*1.663e-27; %kgco
u_velocity = sqrt(2*kB*T/m); %m/s

atm_press = 760;
L = 54.9;
finesse = 6000;
r = 1-pi./finesse;
t = 1-r;

wavenum = hitran_s.wnum(linesvals);
lambdas = 1/100./wavenum;
frequencies = c./lambdas;
linestrength = hitran_s.int(linesvals);

nA = 2.5e19; % mol/cm3 (avogadro/molar volume)
n_0 = 2.686e19;
S = linestrength*n_0*273.15/T;

single_pass = S*conc*pressure/atm_press*L;

omega = c./lambdas*2*pi;
k = omega/c;

freq_scale = 100*c*wavenum_scale;
grid_ = length(wavenum_scale);

ilosc_linii = length(wavenum);
transition_abs = zeros(grid_, ilosc_linii);
transition_disp = zeros(grid_, ilosc_linii);
krok = wavenum_scale(2)-wavenum_scale(1);
narrow = round(5/krok);

for qwe = 1:ilosc_linii 
peak_pos = find(round(freq_scale/krok/30e9) == round(frequencies(qwe)/krok/30e9));
f_min = peak_pos-narrow; 
f_max = peak_pos+narrow;    
if f_min < 1
    f_min =1;
end
if f_max>length(freq_scale)
    f_max= length(freq_scale);
end

%% Use fixed normalized (peak amplitude) gaussian here instead of voigt
peak_value = c*100*sqrt(log(2)/pi)/broad; % From voigt script
abs = peak_value*exp(-(freq_scale(f_min:f_max)-frequencies(qwe)).^2*log(2)/broad^2);
disp = zeros(size(f_min:f_max));
%% End use of gaussian

%[abs, disp] = complex_voigt(freq_scale(f_min:f_max), frequencies(qwe), broad.*ones(size(qwe)), 0.*ones(size(qwe)));

transition_abs(f_min:f_max,qwe) = single_pass(qwe)*abs;
transition_disp(f_min:f_max,qwe) = single_pass(qwe)*disp;
end

abs_spectrum = sum(transition_abs, 2);
disp_spectrum = sum(transition_disp, 2);

faza = -0.000;
E_transm = t.*exp(1i*faza/2)./(1-r.*exp(1i*faza)); 
intens_transm = E_transm.*conj(E_transm);
E_transm_analyte = t.*exp(1i*faza/2-abs_spectrum/2-1i*disp_spectrum/2)./(1-r.*exp(1i*faza-abs_spectrum-1i*disp_spectrum));
CH4_cavity_spectrum  = E_transm_analyte.*conj(E_transm_analyte)./intens_transm;