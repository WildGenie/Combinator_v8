function outputArray = nanindex(inputArray,varargin)
    % Check the inputs - TO DO!!!
    if nargin < 2
       error('Number of arguments must be >= 2'); 
    elseif nargin == 2
       outputArrayDims = {numel(varargin{1}) 1};
    else
       outputArrayDims = cellfun(@numel,varargin);
    end
    for i = 1:numel(varargin)
       if ~isvector(varargin{i})
           error('Indices must be vectors');
       end
    end

    % Construct the output
    outputArray = NaN*zeros(outputArrayDims{:});
    inIndcs = cellfun(@(x) int32(x(~isnan(x))),varargin, 'UniformOutput', false);
    outIndcs = cellfun(@(x) ~isnan(x),varargin, 'UniformOutput', false);
    outputArray(outIndcs{:}) = inputArray(inIndcs{:});
end