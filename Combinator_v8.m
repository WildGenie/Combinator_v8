%% Module Construction

% Standard Subroutines:
%   getDependencies - returns a struct array with handles to the modules
%        that are dependencies and adds these to the enabled modules
%        struct.
%   getPublicProperties - returns an array of public properties to be added
%        to the main property page

% To Do:
%   - Implement save/load on objects (done for MOD_VIPA)
%   - Implement dll for Pleora (fast image acquisition)
%   - Implement faster calibration
%   - Make peak selection better in calibration

%% Set up modules
enabledModules = {...
    @MOD_VIPA,...
    @MOD_Spectrum,...
    @MOD_TimeDynamics
    };

%% Open the window
% Open a new figure window and remove the toolbar and menus
window = figure( 'Name', 'The Combinator', ...
    'MenuBar', 'none', ...
    'Toolbar', 'figure', ...
    'NumberTitle', 'off', ...
    'handlevisibility','off', ...
    'integerhandle','off');

%% Display progress bar
h_waitbar = waitbar(0,sprintf('Loading Modules...'));

%% Check dependencies and module availability
handles = guidata(window);

% Add the modules to the window
handles.enabledModules = enabledModules;

% Check module dependencies
doneAddingModules = 0;
while doneAddingModules == 0
    doneAddingModules = 1;
    oldEnabledModules = handles.enabledModules;
    for i = 1:length(oldEnabledModules)
       tempModule = oldEnabledModules{i}();
       newModules = tempModule.dependencies;
       clear('tempModule')
       for j = 1:length(newModules);
           if sum(arrayfun(@(x) isequal(x{1},newModules{j}),handles.enabledModules)) == 0
               handles.enabledModules{end+1} = newModules{j};
               doneAddingModules = 0;
           end
       end
    end
end
guidata(window,handles);

%% Define Module Data Structures
handles = guidata(window);
handles.mainWindowHandle = window;
handles.childFigures = [];

% Define the data structures
handles.moduleData = struct();
handles.enabledModulesString = struct([]);
for i = 1:length(handles.enabledModules)
    handles.moduleData.(func2str(handles.enabledModules{i})) = handles.enabledModules{i}();
end

guidata(window,handles);

%% Add Dependency handles to modules

% Iterate through each module
moduleNames = fieldnames(handles.moduleData);
for i = 1:numel(moduleNames);
    dependencies = handles.moduleData.(moduleNames{i}).dependencies;
    dependencyHandles = {};
    for j = 1:numel(dependencies)
        dependencyHandles.(func2str(dependencies{j})) = handles.moduleData.(func2str(dependencies{j}));
    end
    handles.moduleData.(moduleNames{i}).dependencyHandles = dependencyHandles;
end

%% Create the layout
% The layout involves two panels side by side. This is done using a
% flexible horizontal box. The left-hand side is filled with a standard
% panel and the right-hand side with some tabs.
handles = guidata(window);
handles.tabpanel = uiextras.TabPanel( 'Parent', ...
    window, ...
    'Padding', 0);
guidata(window,handles);

%% Construct the tabs for each module
handles = guidata(window);
handles.tabpanelNames = {};
guidata(window,handles);

% Iterate through each module
moduleNames = fieldnames(handles.moduleData);
for i = 1:numel(moduleNames);
    handles.moduleData.(moduleNames{i}).constructTab(window);
    handles = guidata(window);
    if length(handles.tabpanelNames) ~= length(get(handles.tabpanel,'TabNames'))
        error([func2str(handles.enabledModules{i}) ' has not provided a name for one of its tabs']);
    end
end

%% Update the tab titles
handles.tabpanel.TabNames = handles.tabpanelNames;

%% Show the first tab
handles.tabpanel.SelectedChild = 1;

%% Allow the figure to finish loading (avoids a race condition)
drawnow;

%% Initialize the modules
handles = guidata(window);

% Iterate through each module
moduleNames = fieldnames(handles.moduleData);
for i = 1:numel(moduleNames);
    handles.moduleData.(moduleNames{i}).initialize(window);
end

%% Define figure close function
closeFunctions = {};
moduleNames = fieldnames(handles.moduleData);
for i = 1:numel(moduleNames);
    closeFunctions{end+1} = @() delete(handles.moduleData.(moduleNames{i}));
end
closeFunctions{end+1} = @() delete(window);
closeFunction = @(hObject,eventdata)cellfun(@feval,closeFunctions);

set(window,'CloseRequestFcn',closeFunction);

%% Close the progress bar
close(h_waitbar);