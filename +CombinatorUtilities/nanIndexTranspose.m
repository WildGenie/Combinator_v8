function outputIndcs = nanIndexTranspose(inputIndcs,varargin)
    % Check the inputs - TO DO!!!
    if nargin < 2
       error('Number of arguments must be >= 2'); 
    end
    for i = 1:numel(varargin)
       if ~isscalar(varargin{i})
           error('Dimensions must be scalar');
       end
    end
    
    % Construct the output
    tempMatrix = zeros(varargin{:});
    tempMatrix(inputIndcs) = 1;
    outputIndcs = find(tempMatrix');
end