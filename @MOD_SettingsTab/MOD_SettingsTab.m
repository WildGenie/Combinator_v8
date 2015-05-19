classdef MOD_SettingsTab < MOD_BASECLASS
   % write a description of the class here.
       properties (Constant)
           dependencies = {};
           moduleName = 'Settings';
       end
       properties
       % define the properties of the class here, (like fields of a struct)
           Tab;
           Panel;
           PropertyGrid;
       end
       methods
       % methods, including the constructor are defined in self block
           function self = MOD_SettingsTab()
           end
           function self = initialize(self,hObject)
                
           end
           function delete(self)
           end
           function self = constructTab(self,hObject)
                % Construct the tab
                handles = guidata(hObject);
                self.Tab = uiextras.Panel( 'Parent', handles.tabpanel, 'Padding', 5, 'Title', self.moduleName);
                handles.tabpanelNames{end+1} = self.moduleName;
                guidata(hObject,handles);
                
                % Adds the property grid panel to the tab
                %set(self.Panel,'Parent',self.Tab);
                self.Panel = uipanel('Parent',self.Tab);
                self.PropertyGrid = PropertyGridPackage.PropertyGrid(self.Panel);
           end
           function self = onTabSelect(self,hObject,eventdata)
           end
           function self = addProperties(self,properties)
               for i = 1:numel(properties)
                self.PropertyGrid.Properties(end+1) = properties(i);
               end
           end
       end
end