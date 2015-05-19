% D2O Lines construct spectrum script

load('01_hit08.mat');
hitran_s = s;
x = 2500:0.01:3500;
linesvals = find((hitran_s.iso == 4) & (hitran_s.int > 0) & (hitran_s.wnum >= min(x)) & (hitran_s.wnum <= max(x)));


c = 299792458; %m/s
kB = 1.3806488e-23; %J/K=Nm/K=kg m^2/s^2/K
T = 300; % kelvin
n = 1;%1*10^11; % mlc/cc
conc = 1;
pressure = n*100^3*kB*T; % torr
atm_press = 760; % torr
L = 1000; % cm

% line strengths are in cm^-2/atm
n_0 = 2.6867805e19;     % Loschmidt mlc/cm^3 for 293.15 Kelvin
%strength = strength./n_0;   %now in cm/mlc
OneAtm = 101325; % Pa

wavenumber = hitran_s.wnum(linesvals);
linestrength = hitran_s.int(linesvals)/0.000310693000;
strength = linestrength*n_0;
%linestrength = strength./n_0;   %now in cm/mlc
S = linestrength*n_0*273.15/T;
single_pass = S*conc*pressure/atm_press*L;
% S = (strength*OneAtm/100^2)*kB*T*100; % assuming strength is cm^-2/atm, S is in cm/molecule
% single_pass = S*n;

broad_Hz = 0.5e9; % Hz
broad_wave = broad_Hz/(c*100); % wavenumbers

A = zeros(size(x));
crossSection = zeros(size(x));
for i = 1:numel(wavenumber)
    peak_value = single_pass(i)*sqrt(log(2)/pi)/broad_wave; % From voigt script
    A = A + peak_value.*exp(-(x - wavenumber(i)).^2*log(2)/broad_wave.^2);
    crossSection = crossSection+...
        linestrength(i)*sqrt(log(2)/pi)/broad_wave.*... % now in cm^2/molecule
        exp(-(x - wavenumber(i)).^2*log(2)/broad_wave.^2);
end

figure;plot(x,1-exp(-A));
ylabel('per cm absorption');