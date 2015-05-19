function yOut = VIPAmolecularLineshape( v, v0, L, Gaussian_FWHM, Lorentz_FWHM, VIPA_FWHM )
Gaussian_FWHM = abs(Gaussian_FWHM);
Lorentz_FWHM = abs(Lorentz_FWHM);
VIPA_FWHM = abs(VIPA_FWHM);

dx = 0.0001;
R = (max(v)-min(v));
x = -R:dx:R;
gamma1 = VIPA_FWHM;%0.01;
yL1 = (gamma1/pi/2)./((gamma1/2).^2+x.^2);
gamma2 = Lorentz_FWHM;%0.0001;
yL2 = (gamma2/pi/2)./((gamma2/2).^2+x.^2);
G_HWHM = Gaussian_FWHM/2;%0.01;
G_sigma = G_HWHM/sqrt(2*log(2));
yG = exp(-x.^2/G_sigma^2/2)/G_sigma/sqrt(2*pi);

% Make the molecule part
%L = 0.10;
if Lorentz_FWHM > 5*dx
    y_mlc = exp(-L*conv(yG,yL2,'same')*dx);
else
    y_mlc = exp(-L*yG);
end
    
y_box = zeros(size(x));
boxHalfWidth = min(abs(diff(v)))/2;
y_box(x < boxHalfWidth & x > -boxHalfWidth) = 1;
y_box = y_box/sum(y_box)/dx;
y_tot = -log(conv(y_mlc-1,conv(yL1,y_box,'same')*dx,'same')./sum(yL1)+1);
% figure;plot(x,y_tot);
% error

yOut = interp1(x,y_tot,v-v0);

end

