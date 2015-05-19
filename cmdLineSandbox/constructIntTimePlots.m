[filename,filepath] = uigetfile('*.avgSpectra',sprintf('Load files...'),'MultiSelect', 'on');
if ~isequal(filename,0) && ~isequal(filepath,0)
   filenames = fullfile(filepath,filename);
else
    return;
end

if ~iscell(filenames)
   filenames = {filenames}; 
end
%%
skipFiles = [4 6];
for i = setdiff(1:numel(filenames),skipFiles)
    data = load(filenames{i},'-mat');
    data.relativeAcquireTime = ((1:size(data.summedSpectra,3))-26)/250+(i-1)*100e-6;
    %return

    if i == 1
        avgSpectra = data.summedSpectra/data.averageNum;
        spectrumWavenumber = data.spectrumWavenumber;
        relativeAcquireTime = data.relativeAcquireTime;
    else
        avgSpectra = cat(3,avgSpectra,data.summedSpectra/data.averageNum);
        relativeAcquireTime = cat(2,relativeAcquireTime,data.relativeAcquireTime);     
    end
end

% Reshape the summed spectra and divide by the average number
y = reshape(avgSpectra,[],size(avgSpectra,3));

% Sort the data
t = relativeAcquireTime;
[tSort,sortIndex] = sort(relativeAcquireTime);
ySort = y(:,sortIndex);

figure;imagesc(ySort);colormap('bone')
figure;plot(tSort);

% Pseudocolor plot
figure;h=surf(relativeAcquireTime,spectrumWavenumber(:),ySort/max(ySort(:)));set(h,'EdgeColor','none');colormap('bone')