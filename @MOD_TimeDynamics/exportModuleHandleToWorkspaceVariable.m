function self = exportModuleHandleToWorkspaceVariable(self,~,~)
         response = inputdlg('Enter Variable Name:',...
             'Export Module Handle to Workspace', [1 50], {'h_TimeDynamics'});
         assignin('base',response{1},self);
end