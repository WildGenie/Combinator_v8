function [y]=multiPeakNormalizedGaussianFun(v,x)
n = (length(v)-1)/3;
y = v(1)*ones(1,length(x));

for i=0:n-1
    A=v(3*i+2);
    gamma=v(3*i+3);
    x0=v(3*i+4);
    c = gamma/sqrt(log(2));
    if c ~= 0
        y=y+A*exp(-(x-x0).^2/c^2);
    else
        y=y+A*(x == x0);
    end
end
y=y';