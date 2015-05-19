function FLIRcamNoisePlot( int_times, numSamples, camAcqFun )

means = zeros(size(int_times));
variances = zeros(size(int_times));
vardiff = zeros(size(int_times));

clc
h = figure;
for i = 1:length(int_times)
   fprintf('Set integration time to %f ms and press enter to continue...\n',int_times(i));
   pause
   camAcqFun(100);
   imgs = camAcqFun(numSamples);
   arr = reshape(imgs(100,100,:),1,numSamples);
   arrdiff = reshape(imgs(:,:,2)-imgs(:,:,1),1,[]);
   figure(h);clf;plot(1:length(arr),arr);
   
   means(i) = mean(arr);
   variances(i) = var(arr);
   vardiff(i) = var(arrdiff);
end

x = 0:0.01:max(int_times);
p = polyfit(int_times,means,1);
ymean = polyval(p,x);
p = polyfit(int_times,variances,1);
yvar = polyval(p,x);
p = polyfit(int_times,vardiff,1);
yvardiff = polyval(p,x);
figure;plot(x,ymean);hold on; scatter(int_times,means);xlabel('Integration Time [ms]');ylabel('Mean [cts]');
figure;plot(x,yvar);hold on;scatter(int_times,variances);xlabel('Integration Time [ms]');ylabel('Variance [cts^2]');
figure;plot(x,yvardiff);hold on;scatter(int_times,vardiff);xlabel('Integration Time [ms]');ylabel('Variance [cts^2]');

end

