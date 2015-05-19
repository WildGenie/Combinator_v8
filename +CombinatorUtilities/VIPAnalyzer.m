%% Module Construction

% Standard Subroutines:
%   getDependencies - returns a struct array with handles to the modules
%        that are dependencies and adds these to the enabled modules
%        struct.
%   getPublicProperties - returns an array of public properties to be added
%        to the main property page

%% Set up modules
enabledModules = {...
    @MOD_VIPA
    };

%% Open the window
% Open a new figure window and remove the toolbar and menus
window = figure( 'Name', 'The Combinator', ...
    'MenuBar', 'none', ...
    'Toolbar', 'figure', ...
    'NumberTitle', 'off' );

% Show hidden handles
set(0,'ShowHiddenHandles','on');

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
disp('Done Constructing Module Dependency Tree...');

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

%% Construct the public property tree
handles = guidata(window);
properties = [];

% Iterate through each module
moduleNames = fieldnames(handles.moduleData);
for i = 1:numel(handles.moduleData);
    %func2str(handles.enabledModules{i})
    newProperties = handles.moduleData.(moduleNames{i}).getPublicProperties();
    properties = [properties newProperties];
end
    
% arrange flat list into a hierarchy based on qualified names
properties = properties.GetHierarchy();

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
handles.tabpanelCallbacks = {};
guidata(window,handles);

% Iterate through each module
moduleNames = fieldnames(handles.moduleData);
for i = 1:numel(handles.moduleData);
    handles.moduleData.(moduleNames{i}).constructTab(window);
    handles = guidata(window);
    if length(handles.tabpanelNames) ~= length(get(handles.tabpanel,'TabNames'))
        error([func2str(handles.enabledModules{i}) ' has not provided a name for one of its tabs']);
    end
    if length(handles.tabpanelCallbacks) ~= length(get(handles.tabpanel,'TabNames'))
        error([func2str(handles.enabledModules{i}) ' has not provided a callback for one of its tabs']);
    end
end

%% Create the tabs
% Each tab is filled with a list box showing some numbers
handles = guidata(window);

htab3 = uiextras.Panel( 'Parent', handles.tabpanel, 'Padding', 5, 'Title', 'Settings');
handles.tabpanelNames{end+1} = 'Settings';

% Add a panel to tab 3.
cont = uipanel('Parent',htab3);

% Add the property tree to tab 3
handles.properties = PropertyGrid(cont, ...            % add property pane to figure
    'Properties', properties ...  % set properties explicitly
    );
guidata(window,handles);

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
for i = 1:numel(handles.moduleData);
    handles.moduleData.(moduleNames{i}).initialize(window);
end

%% Define figure close function
closeFunctions = {};
moduleNames = fieldnames(handles.moduleData);
for i = 1:numel(handles.moduleData);
    closeFunctions{end+1} = @() delete(handles.moduleData.(moduleNames{i}));
end
closeFunctions{end+1} = @() delete(window);
closeFunction = @(hObject,eventdata)cellfun(@feval,closeFunctions);

set(window,'CloseRequestFcn',closeFunction);