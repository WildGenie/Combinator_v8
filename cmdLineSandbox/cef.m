function w = cef(z,N)

%  Computes the function w(z) = exp(-z^2) erfc(-iz) using a rational 
%  series with N terms.  It is assumed that Im(z) > 0 or Im(z) = 0.
%
%                             Andre Weideman, 1995

M = 2*N;  M2 = 2*M;  k = [-M+1:1:M-1]';    % M2 = no. of sampling points.
L = sqrt(N/sqrt(2));                       % Optimal choice of L.
theta = k*pi/M; t = L*tan(theta/2);        % Define variables theta and t.
f = exp(-t.^2).*(L^2+t.^2); f = [0; f];    % Function to be transformed.
a = real(fft(fftshift(f)))/M2;             % Coefficients of transform.
a = flipud(a(2:N+1));                      % Reorder coefficients.
Z = (L+1i*z)./(L-1i*z); p = polyval(a,Z);    % Polynomial evaluation.
w = 2*p./(L-1i*z).^2+(1/sqrt(pi))./(L-1i*z); % Evaluate w(z).

% abs_carrier = exp(-4*(real(z)).^2*log(2));

%figure(20)
%hold on
%plot(z, real(w), 'b', z, imag(w), 'r')

%figure(21)
%hold on
%plot(z, real(w), 'b', z, abs_carrier, 'r')








