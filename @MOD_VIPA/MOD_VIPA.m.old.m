function returnData = MOD_VIPA(hObject,argument)
%SUB_calibration - initializes and calibrates spectra
%   argument - a parameter that indicates what is to be done

this = mfilename;
thisModule = str2func(mfilename);

if nargin == 0
   edit(this);
   return
end

if iscell(argument)
    if numel(argument) > 1
        vararg = argument(2:end);
    else
        vararg = {};
    end
    argument = argument{1};
end

switch argument
    
    %%%%%%%%%%%%%%%%%%%%%
    % STANDARD ROUTINES
    %%%%%%%%%%%%%%%%%%%%%
    case 'getDependencies'
       % Check for MOD_camera
        returnData = {@MOD_FLIRcamera,@MOD_fitVIPAspectrum};
    case 'getPublicProperties'
        returnData = [ ...
            PropertyGridField('calibrationGas', 'Methane', ...
                'Type', PropertyType('char', 'row', {'Methane'}), ...
                'Category', 'VIPA', ...
                'DisplayName', 'Calibration Gas', ...
                'Description', 'Calibration gas spectrum to use when calibrating VIPA.') ...
            PropertyGridField('calibrationGasPartialPressure', 1, ...
                'Category', 'VIPA', ...
                'DisplayName', 'Cal. Gas Partial Pressure [torr]', ...
                'Description', 'Calibration gas partial pressure, in torr. Used to construct calibration gas spectrum when calibrating VIPA.') ...
            PropertyGridField('calibrationGasPathLength', 1, ...
                'Category', 'VIPA', ...
                'DisplayName', 'Cal. Gas Path Length [m]', ...
                'Description', 'Calibration gas optical path length, in meters. Used to construct calibration gas spectrum when calibrating VIPA.') ...
            PropertyGridField('fringeThreshold', 10, ...
                'Category', 'VIPA', ...
                'DisplayName', 'VIPA Fringe Threshold', ...
                'Description', 'Used when calibrating VIPA.') ...
                ];
    case 'constructGUI'
        handles = guidata(hObject);
        % Construct GUI Framework
        theTab = uiextras.Panel( 'Parent', handles.tabpanel, 'Padding', 5, 'Title', 'VIPA');
        handles.tabpanelNames{end+1} = 'VIPA';
        handles.tabpanelCallbacks{end+1} = @(hObject) thisModule(hObject,'callback_update');
        vbox = uiextras.VBox( 'Parent', theTab );
        handles.moduleData.(this).axes = axes( 'Parent', vbox );
        hbox = uiextras.HButtonBox( 'Parent', vbox, 'Padding', 5 );
        handles.moduleData.(this).acquireButton = uicontrol( 'Parent', hbox, ...
            'String', 'Acquire' );
        handles.moduleData.(this).collectFringesButton = uicontrol( 'Parent', hbox, ...
            'String', 'Collect Fringes' );
        handles.moduleData.(this).calibrateButton = uicontrol( 'Parent', hbox, ...
            'String', 'Calibrate' );
        handles.moduleData.(this).fitVIPAimageButton = uicontrol( 'Parent', hbox, ...
            'String', 'Fit to Cal. Gas' );
        set( vbox, 'Sizes', [-1 35] )
        handles.moduleData.(this).imageHandle = imagesc(zeros(100),'Parent',handles.moduleData.(this).axes);
        
        % Set image context menu
        calibMenu = uicontextmenu;
        recordAsMenu = uimenu(calibMenu, 'Label', 'Record Image As');
        handles.moduleData.(this).menu_recordReference = ...
            uimenu(recordAsMenu, ...
                'Label', 'Reference', ...
                'Callback', @(hObject,eventdata) thisModule(hObject,'callback_recordReference'));
        handles.moduleData.(this).menu_recordReferenceBackground = ...
            uimenu(recordAsMenu, ...
                'Label', 'Reference Background', ...
                'Callback', @(hObject,eventdata) thisModule(hObject,'callback_recordReferenceBackground'));
        handles.moduleData.(this).menu_recordCalibrationGas = ...
            uimenu(recordAsMenu, ...
                'Label', 'Calibration Gas', ...
                'Callback', @(hObject,eventdata) thisModule(hObject,'callback_recordCalibrationGas'));
        handles.moduleData.(this).menu_recordCalibrationGasBackground = ...
            uimenu(recordAsMenu, ...
                'Label', 'Calibration Gas Background', ...
                'Callback', @(hObject,eventdata) thisModule(hObject,'callback_recordCalibrationGasBackground'));
        loadImageMenu = uimenu(calibMenu, 'Label', 'Load Image');
        uimenu(loadImageMenu, ...
                'Label', 'Load Image from Workspace', ...
                'Callback', @(hObject,eventdata) thisModule(hObject,'callback_loadImageFromWorkspace'));
        uimenu(loadImageMenu, ...
                'Label', 'Calculate Reference - Ref. Bkg', ...
                'Callback', @(hObject,eventdata) thisModule(hObject,'callback_calculateReferenceMinusRefBkg'));
        customSelectionMenu = uimenu(calibMenu, 'Label', 'Custom Selection');
        uimenu(customSelectionMenu, ...
                'Label', 'Line Profile', ...
                'Callback', @(hObject,eventdata) thisModule(hObject,'callback_chooseImageProfile'));
        uimenu(calibMenu, 'Label', 'Find Bad Pixels', ...
                'Callback', @(hObject,eventdata) thisModule(hObject,'callback_badPixels'));
        set(handles.moduleData.(this).imageHandle,'uicontextmenu',calibMenu);
        
        
        % Set GUI Callbacks
        set(handles.moduleData.(this).acquireButton,...
            'Style','togglebutton',...
            'String','Acquire',...
            'Visible','on',...
            'Callback',@(hObject,eventdata) thisModule(hObject,'callback_AcquireButton'));
        set(handles.moduleData.(this).collectFringesButton,...
            'Style','pushbutton',...
            'String','Collect Fringes',...
            'Visible','on',...
            'Callback',@(hObject,eventdata) thisModule(hObject,'callback_collectFringesButton'));
        set(handles.moduleData.(this).calibrateButton,...
            'Style','pushbutton',...
            'String','Calibrate',...
            'Visible','on',...
            'Callback',@(hObject,eventdata) thisModule(hObject,'callback_CalibrateButton'));
        set(handles.moduleData.(this).fitVIPAimageButton,...
            'Style','pushbutton',...
            'String','Fit to Cal. Gas',...
            'Visible','on',...
            'Callback',@(hObject,eventdata) thisModule(hObject,'callback_fitVIPAimage'));
        guidata(hObject,handles);
        
        % Set default internal parameters
        handles.moduleData.(this).calibrationImages_reference = [];
        handles.moduleData.(this).calibrationImages_referenceBackground = [];
        handles.moduleData.(this).calibrationImages_calibrationGas = [];
        handles.moduleData.(this).calibrationImages_calibrationGasBackground = [];
        guidata(hObject,handles);
        
    %%%%%%%%%%%%%%%%%
    % PUBLIC METHODS
    %%%%%%%%%%%%%%%%%
    case 'public_getWavelengthAxis'
        handles = guidata(hObject);
        returnData = handles.moduleData.(this).spectrumX;
    
    case 'public_acquireSpectrum'
        handles = guidata(hObject);

        % Aquire image
        img = double(MOD_FLIRcamera(hObject,'public_acquireSingleImage'));
        handles = guidata(hObject);
        img(handles.moduleData.MOD_FLIRcamera.badPixelIndcs) = NaN;
        img = img';

        % Check to see if the image has the correct dimensions
        if size(img') ~= handles.moduleData.(this).fringeImageSize
            img
           error('The collected fringes image is not the same size as the calibration image'); 
        end
        
        % Construct averaging over fringe
%         avgNums = 0;
%         spectrumIndcsAvg = repmat(handles.moduleData.(this).spectrumIdcs,[],numel(avgNums));
%         spectrumIndcsAvg = spectrumIndcsAvg + ones(size(handles.moduleData.(this).spectrumIdcs))*avgNums;

        % Check the indices
%         figure;plot(img(:));figure;imagesc(img);
%         error
        
        % Construct the spectrum
        returnData = NaN*zeros(size(handles.moduleData.(this).spectrumIdcs));
        %returnData(:) = NaN;
        returnData(~isnan(handles.moduleData.(this).spectrumIdcs)) = ...
            mean(img(round(...
            handles.moduleData.(this).spectrumIdcs(~isnan(handles.moduleData.(this).spectrumIdcs))...
            )),2);
%         returnData = ...
%             mean(interp1(1:numel(img),double(img(:)),spectrumIndcsAvg),2);
        
        guidata(hObject,handles);
    case 'public_acquireMultipleSpectra'
        % Get the input
        if isempty(vararg)
           error('The number of images must be specified'); 
        end
        numImages = vararg{1};

        % Aquire image
        MOD_FLIRcamera(hObject,{'public_acquireMultipleImages',numImages});
        
        handles = guidata(hObject);

        % Check to see if the image has the correct dimensions
%         if size(handles.imageArray,1) ~= handles.moduleData.(this).fringeImageSize(1) ||...
%                 size(handles.imageArray,2) ~= handles.moduleData.(this).fringeImageSize(2) ||...
%                 size(handles.imageArray,3) ~= numImages
%             size(handles.imageArray)
%            error('The collected fringes image is not the same size as the calibration image'); 
%         end

        if size(handles.imageArray,1) ~= 1 ||...
                size(handles.imageArray,2) ~= handles.moduleData.(this).fringeImageSize(1)*handles.moduleData.(this).fringeImageSize(2)*numImages
            size(handles.imageArray)
           error('The collected fringes image is not the same size as the calibration image'); 
        end
        
        % Construct the indices for the image
        imageOffset = repmat(0:(numImages-1),[length(handles.moduleData.(this).spectrumIdcs) 1]);
        indcs = repmat(handles.moduleData.(this).spectrumIdcs,[1 numImages]);
        numElements = handles.moduleData.(this).fringeImageSize(1)*handles.moduleData.(this).fringeImageSize(2);
        spectrumIndcs = imageOffset*numElements + indcs;
        
%         % Construct averaging over fringe
%         avgNums = -1:1;
%         spectrumIndcsAvg = repmat(spectrumIndcs,[],size(avgNums));
%         spectrumIndcsAvg = spectrumIndcsAvg + ones(size(spectrumIndcs))*avgNums;
        
        % Construct the spectra
        returnData = zeros(size(spectrumIndcs));
        returnData(:) = NaN;
        returnData(~isnan(spectrumIndcs)) = ...
            handles.imageArray(round(...
            spectrumIndcs(~isnan(spectrumIndcs))...
            ));
        
        guidata(hObject,handles);

    %%%%%%%%%%%%%%%%%
    % CALLBACKS
    %%%%%%%%%%%%%%%%%
    
    case 'callback_AcquireButton'
        % Live image
        % Continue as long as button is pressed
        handles = guidata(hObject);
        imgsPerBackground = 1e6;
        bkgCounter = 0;
        while (get(handles.moduleData.(this).acquireButton, 'value'))
            
            % Check to see if we need a new background
            if mod(bkgCounter,imgsPerBackground) == 0
                 MOD_Arduino(hObject,'public_shutterProgram');
                 MOD_FLIRcamera(hObject,{'public_acquireMultipleImages',3});
                 handles = guidata(hObject);
                 bkgImages = reshape(handles.imageArray,[320 256 3]);
                 bkgImage = bkgImages(:,:,2)';
                 bkgCounter = 0;
                disp('bkg');
            end
            bkgCounter = bkgCounter + 1;
            
            % Aquire image
            MOD_Arduino(hObject,'public_oneCameraImage');
            img = double(MOD_FLIRcamera(hObject,'public_acquireSingleImage')) - double(bkgImage);
            img(handles.moduleData.MOD_FLIRcamera.badPixelIndcs) = NaN;

            % Display image
            set(handles.moduleData.(this).imageHandle,'CData',img);
            set(handles.moduleData.(this).axes,'XLim',[0 size(img,2)]);
            set(handles.moduleData.(this).axes,'YLim',[0 size(img,1)]);
            
            pause(0.01);
        end
        guidata(hObject,handles);
    case 'callback_recordReference'
        handles = guidata(hObject);
        handles.moduleData.(this).calibrationImages_reference = get(handles.moduleData.(this).imageHandle,'CData');
        set(handles.moduleData.(this).menu_recordReference,'Checked','on');
        guidata(hObject,handles);
    case 'callback_recordReferenceBackground'
        handles = guidata(hObject);
        handles.moduleData.(this).calibrationImages_referenceBackground = get(handles.moduleData.(this).imageHandle,'CData');
        set(handles.moduleData.(this).menu_recordReferenceBackground,'Checked','on');
        guidata(hObject,handles);
    case 'callback_recordCalibrationGas'
        handles = guidata(hObject);
        handles.moduleData.(this).calibrationImages_calibrationGas = get(handles.moduleData.(this).imageHandle,'CData');
        set(handles.moduleData.(this).menu_recordCalibrationGas,'Checked','on');
        guidata(hObject,handles);
    case 'callback_recordCalibrationGasBackground'
        handles = guidata(hObject);
        handles.moduleData.(this).calibrationImages_calibrationGasBackground = get(handles.moduleData.(this).imageHandle,'CData');
        set(handles.moduleData.(this).menu_recordCalibrationGasBackground,'Checked','on');
        guidata(hObject,handles);
    case 'callback_loadImageFromWorkspace'
        handles = guidata(hObject);
        
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
        set(handles.moduleData.(this).imageHandle,'CData',img);
        set(handles.moduleData.(this).axes,'XLim',[0 size(img,2)]);
        set(handles.moduleData.(this).axes,'YLim',[0 size(img,1)]);
    case 'callback_calculateReferenceMinusRefBkg'
        handles = guidata(hObject);
        
        % Calculate Image
        img = handles.moduleData.(this).calibrationImages_reference -...
            handles.moduleData.(this).calibrationImages_referenceBackground;
        
        % Display image
        set(handles.moduleData.(this).imageHandle,'CData',img);
        set(handles.moduleData.(this).axes,'XLim',[0 size(img,2)]);
        set(handles.moduleData.(this).axes,'YLim',[0 size(img,1)]);
    case 'callback_collectFringesButton'
        handles = guidata(hObject);
        
        % Get image from screen
        fringeImage = get(handles.moduleData.(this).imageHandle,'CData');
        
        % Save as reference
        handles.moduleData.(this).calibrationImages_reference = fringeImage';
        
        % Bad Pixel Locations
        badPixelKernel = [1 1 1; 1 0 1; 1 1 1]/8;
        fringeImage(handles.moduleData.MOD_FLIRcamera.badPixelIndcs) = 0;
        badPixelReplace = conv2(fringeImage,badPixelKernel,'same');
        fringeImage(handles.moduleData.MOD_FLIRcamera.badPixelIndcs) = badPixelReplace(handles.moduleData.MOD_FLIRcamera.badPixelIndcs);
        fringeImage = fringeImage';
        figure;imagesc(fringeImage');
        
        % Identify the zero crossings of the image
        windowSize = 30;
        %fringeImageBase = repmat(mean(fringeImage,1),size(fringeImage,1),1);
        fringeImageBase = filter(ones(1,windowSize)/windowSize,1,fringeImage,[],1);
        fringeImageNorm = fringeImage - fringeImageBase;
        
        %figure;imagesc(fringeImageNorm');
        %error
        
        fringeImageNorm1 = fringeImageNorm(1:end-1,:);
        fringeImageNorm2 = fringeImageNorm(2:end,:);
        idx = find(sign(fringeImageNorm1)-sign(fringeImageNorm2));
        [idxX,idxY] = ind2sub(size(fringeImageNorm1),idx);
        %figure;imagesc(fringeImageNorm');hold on;scatter(idxX,idxY,'.k');
        isPeak = (-sign(fringeImageNorm1(idx(1:end-1)))+1)/2;
        m = (fringeImageNorm2(idx)-fringeImageNorm1(idx));
        b = fringeImageNorm1(idx)-m.*idxX;
        idxX = -b./m;
        %figure;imagesc(fringeImageNorm');hold on;scatter(idxX,idxY,'.k');
        
        % Identify the peaks for each row of the image
        thePeaksAndValleysX = (idxX(1:end-1)+idxX(2:end))/2;
        thePeaksAndValleysY = idxY(1:end-1);
        deltaY = idxY(1:end-1)-idxY(2:end);
        thePeaksX = thePeaksAndValleysX((isPeak == 1) & (deltaY == 0));
        thePeaksY = thePeaksAndValleysY((isPeak == 1) & (deltaY == 0));
        %thePeaks = thePeaks(:,2:end-1);
        %figure;imagesc(fringeImageNorm');hold on;scatter(thePeaksX,thePeaksY,'.k');
        
        % Group the rows (and sort them)
        [uniqueRows,ia,ic] = unique(thePeaksY);
        
        % Iterate over the uniqe rows, selecting peaks and adding them to
        % a fringe
        fringesX = {};
        fringesY = {};
        for i = 1:length(uniqueRows)

            idx = find(thePeaksY == uniqueRows(i));
            for j = 1:length(idx)
                if i == 1
                   fringesX{i,j} = thePeaksX(idx(j));
                   fringesY{i,j} = thePeaksY(idx(j));
                else
                    fringeMatchIdx = [];
                    for k = 1:size(fringesX,2)
                        if ~isempty(fringesX{i-1,k}) & (abs(fringesX{i-1,k} - thePeaksX(idx(j))) < 1)
                            fringeMatchIdx = k;
                            break;
                        end
                    end
                    
                   %fringeMatchIdx = find(abs([fringesX{i-1,:}] - thePeaksX(idx(j))) < 1);
                   if isempty(fringeMatchIdx)
                    fringesX{i,end+1} = thePeaksX(idx(j));
                    fringesY{i,end+1} = thePeaksY(idx(j));
                   else
                    fringesX{i,fringeMatchIdx} = thePeaksX(idx(j));
                    fringesY{i,fringeMatchIdx} = thePeaksY(idx(j));
                   end
                   
                end
            end
        end
        %figure;imagesc(fringeImageNorm');hold on;
        %scatter([fringesX{:}],[fringesY{:}],'.k');
        
        % Save the fringes to be used laser
        for i = 1:numel(fringesX);
           if isempty(fringesX{i})
               fringesX{i} = NaN;
           end
           if isempty(fringesY{i})
               fringesY{i} = NaN;
           end
        end
        fringesXmat = cell2mat(fringesX);
        fringesYmat = cell2mat(fringesY);
        
        % Get the minimum x element from each fringe
        fringesStartX = min(fringesXmat,[],1);
        [~,idx] = sort(fringesStartX);

        % Sort the fringes by fringesStartX
        fringesXmatSorted = fringesXmat(:,idx);
        fringesYmatSorted = fringesYmat(:,idx);

        % Remove fringes that do not cover at least half of the screen and
        % that do not have at least 100 points
        newFringesX = [];
        newFringesY = [];
        fringeHighThresh = 0*size(fringeImage',1);
        fringeLowThresh = 1*size(fringeImage',1);
        for i = 1:size(fringesXmatSorted,2)
           if sum(~isnan(fringesXmatSorted(:,i))) > 50 && ...
                   max(fringesYmatSorted(:,i)) > fringeHighThresh && ...
                   min(fringesYmatSorted(:,i)) < fringeLowThresh
               newFringesX(:,end+1) = fringesXmatSorted(:,i);
               newFringesY(:,end+1) = fringesYmatSorted(:,i);
           end
        end
        
        % Save the fringes to be used later
        handles.moduleData.(this).fringeX = newFringesX;
        handles.moduleData.(this).fringeY = newFringesY;
        handles.moduleData.(this).fringeImageSize = size(fringeImage');
        guidata(hObject,handles);
        
        % Plot the fringes for the user
        figure;imagesc(fringeImageNorm');hold on;
        fringesOddX = newFringesX(:,1:2:end);
        fringesOddY = newFringesY(:,1:2:end);
        fringesEvenX = newFringesX(:,2:2:end);
        fringesEvenY = newFringesY(:,2:2:end);
        scatter(fringesOddX(:),fringesOddY(:),'.k');
        scatter(fringesEvenX(:),fringesEvenY(:),'.r');
        
    case 'callback_CalibrateButton'
        handles = guidata(hObject);

        % Get image from screen
        fringeImage = get(handles.moduleData.(this).imageHandle,'CData')';
        fringeImage = fringeImage./handles.moduleData.(this).calibrationImages_reference;
        
        % Check to make sure that the dimensions of the image are correct
        if size(fringeImage') ~= handles.moduleData.(this).fringeImageSize
           error('The collected fringes image is not the same size as the calibration image'); 
        end
        
        % Construct fringe image from indices
        fringeImageIdcs = sub2ind(size(fringeImage),...
            handles.moduleData.(this).fringeX,...
            handles.moduleData.(this).fringeY);
        
        collectedFringes = fringeImageIdcs;
        collectedFringes(~isnan(fringeImageIdcs)) = fringeImage(round(fringeImageIdcs(~isnan(fringeImageIdcs))));
        
        %figure;imagesc(collectedFringes);
        
        % Crop to an FSR
        cropArgsFringes = CropImageGUI(collectedFringes);
        
        % Crop indices to an FSR
        handles.moduleData.(this).fringeXcrop = CropImageGUI_doCrop(handles.moduleData.(this).fringeX,cropArgsFringes);
        handles.moduleData.(this).fringeYcrop = CropImageGUI_doCrop(handles.moduleData.(this).fringeY,cropArgsFringes);
        
        % Save indices as indices
        fringeImageIdcsCrop = sub2ind(size(fringeImage),...
            handles.moduleData.(this).fringeXcrop,...
            handles.moduleData.(this).fringeYcrop);
        
        % Flip the fringe indices
        fringeImageIdcsCrop = flipud(fringeImageIdcsCrop);
        
        size(fringeImageIdcsCrop)
        handles.moduleData.(this).fringeHeight = size(fringeImageIdcsCrop,1);
        handles.moduleData.(this).numFringes = size(fringeImageIdcsCrop,2);
        handles.moduleData.(this).spectrumIdcs = fringeImageIdcsCrop(:);
        
        % Save spectrumX
        handles.moduleData.(this).spectrumX = 1:numel(handles.moduleData.(this).spectrumIdcs);
        
        % Save the relevant data
        %handles.MOD_constructSpectrum.imageFringeX = imageFringeX;
        %handles.MOD_constructSpectrum.imageFringeY = imageFringeY;
        %handles.MOD_constructSpectrum.imageFringeNumFringes = imageFringeNumFringes;
        %handles.MOD_constructSpectrum.imageFringeVertExtent = imageFringeVertExtent;
        guidata(hObject,handles);
    case 'callback_fitVIPAimage'
        handles = guidata(hObject);

        % Get images
        img = get(handles.moduleData.(this).imageHandle,'CData')';
        imgRef = handles.moduleData.(this).calibrationImages_reference;
        imgDiv = 1-img./imgRef;

        % Check to see if the image has the correct dimensions
        if size(imgDiv') ~= handles.moduleData.(this).fringeImageSize
            imgDiv
           error('The collected fringes image is not the same size as the calibration image'); 
        end
        
        % Construct the spectrum
        fitSpectrum = zeros(size(handles.moduleData.(this).spectrumIdcs));
        fitSpectrum(:) = NaN;
        fitSpectrum(~isnan(handles.moduleData.(this).spectrumIdcs)) = ...
            imgDiv(round(...
            handles.moduleData.(this).spectrumIdcs(~isnan(handles.moduleData.(this).spectrumIdcs))...
            ));
        size(handles.moduleData.(this).spectrumIdcs)
        
        % Fit the spectrum
        MOD_fitVIPAspectrum(hObject,{'setCalibSpectrumYaxis',fitSpectrum(:),handles.moduleData.(this).fringeHeight,handles.moduleData.(this).numFringes});
        uiwait(MOD_fitVIPAspectrum(hObject,'fitFrequencyAxis'));
        
        spectrumX = MOD_fitVIPAspectrum(hObject,'getFittedXaxis');
        if ~isempty(spectrumX)
            handles.moduleData.(this).spectrumX = spectrumX;
            disp('Calibration saved');
        else
            disp('Note: Fitting aborted');
        end
        
        guidata(hObject,handles);
    case 'callback_chooseImageProfile'
        handles = guidata(hObject);
        
        % Get image from screen
        fringeImage = get(handles.moduleData.(this).imageHandle,'CData')';
        handles.moduleData.(this).fringeImageSize = size(fringeImage');
        
        % Select a profile
        h = figure;imagesc(fringeImage');
        [cx,cy,c] = improfile;
        figure;plot(c);
        close(h);
        
        % Save indices as indices
        fringeImageIdcsCrop = sub2ind(size(fringeImage),...
            round(cx),...
            round(cy));
        
        % Flip the fringe indices
        %fringeImageIdcsCrop = flipud(fringeImageIdcsCrop);
        
        handles.moduleData.(this).spectrumIdcs = fringeImageIdcsCrop(:);
        
        % Save spectrumX
        handles.moduleData.(this).spectrumX = 1:numel(handles.moduleData.(this).spectrumIdcs);
        
        guidata(hObject,handles);
        
    case 'callback_badPixels'
        handles = guidata(hObject);
        
        % Get image from screen
        fringeImage = get(handles.moduleData.(this).imageHandle,'CData');
        
        % Get bkg Image
                 MOD_Arduino(hObject,'public_shutterProgram');
                 MOD_FLIRcamera(hObject,{'public_acquireMultipleImages',3});
                 handles = guidata(hObject);
                 bkgImages = reshape(handles.imageArray,[320 256 3]);
                 bkgImage = bkgImages(:,:,2)';
%         figure;imagesc(bkgImage);
%         return
        
%         % User input
%         disp('Place a hot source in front of the camera and press enter...');
%         pause(5);
        
%         % Collect hot source
%         MOD_Arduino(hObject,'public_oneCameraImage');
%         hotImage = MOD_FLIRcamera(hObject,{'public_acquireSingleImage','rawImage'});
        
        % Find the indices of the bad pixels
        idx = find(double(bkgImage)<0.75*mean(bkgImage(:)) | double(bkgImage)>1.5*mean(bkgImage(:)));
        [idxX,idxY] = ind2sub(size(bkgImage),idx);
        
        % Plot the image and bad pixels
        figure;
        imagesc(bkgImage); hold on;
        scatter(idxY,idxX,'o');
        
        % Save the bad pixels to MOD_FLIRcamera
        handles.moduleData.MOD_FLIRcamera.badPixelIndcs = idx;
        
        guidata(hObject,handles);

end

end