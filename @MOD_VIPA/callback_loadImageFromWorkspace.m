function self = callback_loadImageFromWorkspace( self, hObject, eventdata)
%CALLBACK_LOADIMAGEFROMWORKSPACE Summary of this function goes here
%   Detailed explanation goes here

        % Load image
        workspaceList = evalin('base','who');
        [s,v] = listdlg('PromptString','Select a file:',...
                'SelectionMode','single',...
                'ListString',workspaceList);
        if v == 0 % The user cancelled the dialog
            return
        end
        
        % Extract the variable from the base workspace
        img = evalin('base',workspaceList{s});
        
        % Display image
        set(self.imageHandle,'CData',img);
        set(self.axes,'XLim',[0 size(img,2)]);
        set(self.axes,'YLim',[0 size(img,1)]);

end

