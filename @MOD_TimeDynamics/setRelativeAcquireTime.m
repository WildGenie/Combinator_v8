function self = setRelativeAcquireTime(self, ~, ~ )
    
    prompt = {'Frame Rate [Hz]:','Photolysis Image Number:','Photolysis Time Offset [us]:'};
    dlg_title = 'Set Relative Acquire Time';
    num_lines = 1;
    def = {'250','26','0'};
    answer = inputdlg(prompt,dlg_title,num_lines,def);
    frameRate = str2double(answer{1});
    photImageNum = str2double(answer{2});
    photTimeOffset = str2double(answer{3})*1e-6;
    self.constructTimeDynamicsPlot_relativeAcquireTime = ...
        ((1:size(self.constructTimeDynamicsPlot_summedSpectra,3))-photImageNum)/frameRate + ...
        photTimeOffset;
end

