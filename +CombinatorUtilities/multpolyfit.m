function c = multpolyfit(x,y,n)
m = size(x,2);

c = zeros(n+1,m);
for k = 1:m
    M = repmat(x(:,k),1,n+1);
    M = bsxfun(@power,M,0:n);
    c(:,k) = M\y(:,k);
end