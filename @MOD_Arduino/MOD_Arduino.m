classdef MOD_Arduino < MOD_BASECLASS

       %%% BEGIN PROPERTY GRID %%%
       properties (Dependent = true)
            comPort;
       end
       properties (Hidden=true)
            hprop_comPort;
            PropertyGridProperties = [];
            chks = false;  % Checks serial connection before every operation
            chkp = true;   % Checks parameters before every operation
       end
       methods
           function self = set.comPort(self,value)
                self.hprop_comPort.Value = value;
           end
           function value = get.comPort(self)
                value = self.hprop_comPort.Value;
           end
           function self = setProperties(self)
            self.hprop_comPort = PropertyGridField('arduinoCommPort', 'COM4', ...
                'Category', self.moduleName, ...
                'DisplayName', 'Arduino COM Port', ...
                'Description', 'Arduino COM Port. Determine COM port using Device Manager.');
            self.PropertyGridProperties = [ ...
                    self.hprop_comPort];
           end
       end
       %%% END PROPERTY GRID %%%

   % write a description of the class here.
       properties (Constant)
           dependencies = {@MOD_SettingsTab};
           moduleName = 'Arduino';
       end
       properties
       % define the properties of the class here, (like fields of a struct)
           commPort = 'COM4';
           aser;   % Serial Connection
       end
       methods
           function self = MOD_Arduino()
           end
           function self = initialize(self,hObject)
                self.setProperties();
                self.dependencyHandles.MOD_SettingsTab.addProperties(self.PropertyGridProperties);
                self.Connect();
           end
           function self = Connect(self)
                try
                    %commPort = handles.properties.Properties.FindByName('arduinoCommPort').Value;
                    self.ConnectArduino(self.commPort);
                    message = sprintf('Arduino successfully connected at COMM port %s.',self.commPort);
                    %uiwait(msgbox(message));
                catch
                    self.ConnectArduino('DEMO');
                    message = sprintf('Could not open COMM port %s. Arduino is running in DEMO mode. Maybe check the Arduino COMM port in Device Manager...',self.commPort);
                    %uiwait(msgbox(message));
                end
           end
           function self = Disconnect(self)
                % if it is a serial, valid and open then close it
                if isa(self.aser,'serial') && isvalid(self.aser) && strcmpi(get(self.aser,'Status'),'open'),
                    fclose(self.aser);
                end

                % if it's an object delete it
                if isobject(self.aser),
                    delete(self.aser);
                end
           end
            % distructor, deletes the object
            function delete(self)
                % if it is a serial, valid and open then close it
                if isa(self.aser,'serial') && isvalid(self.aser) && strcmpi(get(self.aser,'Status'),'open'),
                    fclose(self.aser);
                end

                % if it's an object delete it
                if isobject(self.aser),
                    delete(self.aser);
                end
            end % delete
           function self = constructTab(self,hObject)
                handles = guidata(hObject);

                % No gui necessary

                % Initialize the uimenu
                connectMenu = findobj(hObject,'Type','uimenu','-and','Label','Arduino','-and','Parent',hObject);
                if isempty(connectMenu)
                   connectMenu = uimenu(hObject,'Label','Arduino');
                else
                   connectMenu = connectMenu(1); 
                end
                %uimenu(connectMenu, 'label','Set Continuous Acquire Trigger','Callback', @self.callback_connectCamera);
%                 uimenu(connectMenu, 'label','Connect Fake FLIR Camera','Callback', @self.callback_connectFakeCamera);
%                 uimenu(connectMenu, 'label','Set Frame Rate','Callback', @self.callback_setCameraFrameRate);
%                 uimenu(connectMenu, 'label','Set Camera Trigger','Callback', @self.callback_setTrigger);

                guidata(hObject,handles);
           end
        % excimerProgram
        function self = excimerProgram(self,arduinoDelayMilliseconds,TTLdivisionFactor,numImages,pulseDelay,excimerImages)
            
            %%%%%%%%%%%%%%%%%%%%%%%%% ARGUMENT CHECKING %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            
            if (numel(arduinoDelayMilliseconds) > 1 ||...
                ceil(arduinoDelayMilliseconds) ~= floor(arduinoDelayMilliseconds) ||...
                arduinoDelayMilliseconds < 0 ||...
                arduinoDelayMilliseconds >= 65535)
               error('arduinoDelayMilliseconds is not formatted correctly') 
            end
            if (numel(TTLdivisionFactor) > 1 ||...
                ceil(TTLdivisionFactor) ~= floor(TTLdivisionFactor) ||...
                TTLdivisionFactor <= 0 ||...
                TTLdivisionFactor >= 65535)
               error('TTLdivisionFactor is not formatted correctly') 
            end
            if (numel(numImages) > 1 ||...
                ceil(numImages) ~= floor(numImages) ||...
                numImages < 1 ||...
                numImages > 500)
               error('numImages is not formatted correctly') 
            end
            if (numel(pulseDelay) > 1 ||...
                ceil(pulseDelay) ~= floor(pulseDelay) ||...
                pulseDelay < 0 ||...
                pulseDelay > 65535)
               error('pulseDelay is not formatted correctly') 
            end
%             if (~isempty(excimerImages) &&...
%                 (sum(ceil(excimerImages) - floor(excimerImages)) == 0)) ||...
%                 min(excimerImages) < 0 ||...
%                 max(excimerImages) >= 65535)
%                error('excimerImages is not formatted correctly') 
%             end
            
            %%%%%%%%%%%%%%%%%%%%%%%%% PERFORM DIGITAL OUTPUT %%%%%%%%%%%%%%%%%%%%%%%%%%
            
            if strcmpi(get(self.aser,'Port'),'DEMO'),
                % handle demo mode
                
                % minimum digital output delay
                pause(0.0014);
                
            else
                
                % check a.aser for openness if a.chks is true
                if self.chks,
                    errstr=arduino_BJB.checkser(self.aser,'open');
                    if ~isempty(errstr), error(errstr); end
                end
                
                % send mode, pin and value
                toSend = [50 arduinoDelayMilliseconds TTLdivisionFactor numImages pulseDelay excimerImages 65535];
                fwrite(self.aser,toSend,'uint16');
            end
            
        end
        
        % excimerProgram
        function self = public_oneCameraImage(self)
            
            %%%%%%%%%%%%%%%%%%%%%%%%% PERFORM DIGITAL OUTPUT %%%%%%%%%%%%%%%%%%%%%%%%%%
            
            if strcmpi(get(self.aser,'Port'),'DEMO'),
                % handle demo mode
                
                % minimum digital output delay
                pause(0.0014);
                
            else
                
                % check a.aser for openness if a.chks is true
                if self.chks,
                    errstr=arduino_BJB.checkser(self.aser,'open');
                    if ~isempty(errstr), error(errstr); end
                end
                
                % send mode, pin and value
                toSend = [52 65535];
                fwrite(self.aser,toSend,'uint16');
            end
            
        end
        
        % excimerProgram
        function self = setInterruptOperation(self,interruptOperation)
            if (numel(interruptOperation) > 1 ||...
                ceil(interruptOperation) ~= floor(interruptOperation) ||...
                interruptOperation < 0 ||...
                interruptOperation >= 65536)
               error('interruptOperation is not formatted correctly') 
            end
            
            %%%%%%%%%%%%%%%%%%%%%%%%% PERFORM DIGITAL OUTPUT %%%%%%%%%%%%%%%%%%%%%%%%%%
            
            if strcmpi(get(self.aser,'Port'),'DEMO'),
                % handle demo mode
                
                % minimum digital output delay
                pause(0.0014);
                
            else
                
                % check a.aser for openness if a.chks is true
                if self.chks,
                    errstr=arduino_BJB.checkser(self.aser,'open');
                    if ~isempty(errstr), error(errstr); end
                end
                
                % send mode, pin and value
                toSend = [5 interruptOperation 65535];
                fwrite(self.aser,toSend,'uint16');
            end
            
        end
        
        function self = public_shutterProgram(self)
            
            %%%%%%%%%%%%%%%%%%%%%%%%% ARGUMENT CHECKING %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            
            %%%%%%%%%%%%%%%%%%%%%%%%% PERFORM DIGITAL OUTPUT %%%%%%%%%%%%%%%%%%%%%%%%%%
            
            if strcmpi(get(self.aser,'Port'),'DEMO'),
                % handle demo mode
                
                % minimum digital output delay
                pause(0.0014);
                
            else
                
                % check a.aser for openness if a.chks is true
                if self.chks,
                    errstr=arduino_BJB.checkser(self.aser,'open');
                    if ~isempty(errstr), error(errstr); end
                end
                
                % send program (51) and end uint16 (0xFFFF)
                toSend = [51 65535];
                fwrite(self.aser,toSend,'uint16');
            end
            
        end
        
        function self = setContinuousFunction(self,arduinoContinuousFunction,otherArgs)
            %%%%%%%%%%%%%%%%%%%%%%%%% ARGUMENT CHECKING %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            if (numel(arduinoContinuousFunction) > 1 ||...
                ceil(arduinoContinuousFunction) ~= floor(arduinoContinuousFunction) ||...
                arduinoContinuousFunction < 0 ||...
                arduinoContinuousFunction >= 65535)
               error('arduinoContinuousFunction is not formatted correctly.') 
            end
            
            if (~isempty(otherArgs) &&...
                (ceil(otherArgs) ~= floor(otherArgs) ||...
                min(otherArgs) < 0 ||...
                max(otherArgs) >= 65535))
               error('otherArgs is not formatted correctly') 
            end
            %%%%%%%%%%%%%%%%%%%%%%%%% PERFORM DIGITAL OUTPUT %%%%%%%%%%%%%%%%%%%%%%%%%%
            
            if strcmpi(get(self.aser,'Port'),'DEMO'),
                % handle demo mode
                
                % minimum digital output delay
                pause(0.0014);
                
            else
                
                % check a.aser for openness if a.chks is true
                if self.chks,
                    errstr=arduino_BJB.checkser(self.aser,'open');
                    if ~isempty(errstr), error(errstr); end
                end
                
                % send program (2) and end uint16 (0xFFFF)
                toSend = [2 arduinoContinuousFunction otherArgs 65535];
                fwrite(self.aser,toSend,'uint16');
            end
            
        end
           function publicProperties = getPublicProperties(self)
                self.publicProperties = [ ...
                    PropertyGridField('arduinoCommPort', 'COM4', ...
                        'Category', 'Arduino Timing Controller', ...
                        'DisplayName', 'Arduino COM Port', ...
                        'Description', 'Arduino COM Port. Determine COM port using Device Manager.',...
                        'ValueChangeCallback', @(name,oldValue,newValue) selfModule(hObject,'callback_updateCommPort')) ...
                    PropertyGridField('arduinoPulseDelay', uint16(0), ...
                        'Category', 'Arduino Timing Controller', ...
                        'DisplayName', 'Arduino Pulse Delay', ...
                        'Description', 'Cycles (x4) to delay between trig and output. Setting self to 1 yields 250 ns delay, etc.')
                        ];
           end
       end
end