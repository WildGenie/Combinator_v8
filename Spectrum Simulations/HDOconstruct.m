%% Calculate HDO spectrum

%% Linear fit section - fixed fwhm
kB = 1.3806488e-23; %J/K=Nm/K=kg m^2/s^2/K
T = 273.15+21; %K
load('01_hit08.mat');
hitran_s = s;
wavenum_scale = 2400:0.01:3000;
n = 10^12; % mlc/cc
conc = 1;
pressure = n*100^3*kB*T; % torr
broad = 1E9;
natAbund = 3.10693E-4;          %HDO natural abundance

clear HDO_cavity_spectrum abs_spectrum
linesvals = find((hitran_s.iso == 4) & (hitran_s.int > 0) & (hitran_s.wnum >= min(wavenum_scale)) & (hitran_s.wnum <= max(wavenum_scale)));

c = 299792458; %m/s
h_bar = 1.054571726e-34;
m = 80.91*1.660538921e-27; %kgco
u_velocity = sqrt(2*kB*T/m); %m/s

atm_press = 760;
L = 1000;

wavenum = hitran_s.wnum(linesvals);
lambdas = 1/100./wavenum;
frequencies = c./lambdas;
linestrength = hitran_s.int(linesvals);

nA = 2.5e19; % mol/cm3 (avogadro/molar volume)
n_0 = 2.6867805e19;
S = linestrength*n_0*273.15/T/natAbund;

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

figure; plot(wavenum_scale,1-exp(-abs_spectrum));
