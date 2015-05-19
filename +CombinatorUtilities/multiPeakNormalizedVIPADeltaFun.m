function Z=multiPeakNormalizedVIPADeltaFun(v,X,Y)
% Input Parameters:
%    Baseline:
%        I: 3 params
%        J: 3 params
%    Each Fringe:
%        Center: 3 params
%        Width: 3 params
%        Amplitude: 3 params

% Fringes are along X dimension (VIPA Dispersion)
% Y direction is grating dispersion
nbaseline = 1;
nfringe = 9;

n = (length(v)-nbaseline)/nfringe;
Z = v(1)*ones(size(X));% + ...
    %v(2)*X.^2 + v(2)*X.^3 + ...
    %v(5)*Y.^2 + v(6)*Y.^3;

for i=0:n-1
    nstart = nbaseline + 1;
    A=v(9*i+nstart)*X.^2+v(9*i+nstart+1)*X+v(9*i+nstart+2);
    gamma=v(9*i+nstart+3)*X.^2+v(9*i+nstart+4)*X+v(9*i+nstart+5);
    y0=v(9*i+nstart+6)*X.^2+v(9*i+nstart+7)*X+v(9*i+nstart+8);
    c = gamma/sqrt(log(2));
    c = 0;
    if c ~= 0
        Z=Z+A.*exp(-(Y-y0).^2./c.^2);
    else
        Z=Z+A.*(Y == y0);
    end
end