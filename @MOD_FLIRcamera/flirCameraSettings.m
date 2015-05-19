function settingsOut = flirCameraSettings( settingsIn )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

    if nargin == 0
        settingsIn = struct();
    elseif nargin > 1
        error('Too many arguments');
    end
    
    command = 'genctrlExample';
    [status,cmdout] = dos(command);
    
    if status == 1
       disp(cmdout);
    else
       settingsOut = 0; 
    end
end

