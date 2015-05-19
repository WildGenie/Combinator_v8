function self = ConnectSerialPort(self,comPort)

    % check port
    if ~ischar(comPort),
        error('The input argument must be a string, e.g. ''COM8'' ');
    end

    % check if we are already connected
    if isa(self.aser,'serial') && isvalid(self.aser) && strcmpi(get(self.aser,'Status'),'open'),
        disp(['It looks like we are already connected to port ' comPort ]);
        disp('Delete the object to force disconnection');
        disp('before attempting a connection to a different port.');
        return;
    end

    % check whether serial port is currently used by MATLAB
    if ~isempty(instrfind({'Port'},{comPort})),
        disp(['The port ' comPort ' is already used by MATLAB']);
        disp(['If you are sure that MOD_Arduino is connected to ' comPort]);
        disp('then delete the object, execute:');
        disp(['  delete(instrfind({''Port''},{''' comPort '''}))']);
        disp('to delete the port, disconnect the cable, reconnect it,');
        disp('and then create a new arduino_BJB object');
        error(['Port ' comPort ' already used by MATLAB']);
    end

    % define serial object
    self.aser=serial(comPort,'BaudRate',115200,'DataBits',8,'Parity','none','StopBits',1,'ByteOrder','bigEndian');

    % connection
    if strcmpi(get(self.aser,'Port'),'DEMO'),
        % handle demo mode

        fprintf(1,'MOD_Arduino:  Demo mode connection ...');
        fprintf(1,'\n');

        % chk is equal to 3, (general server running)
        chk=3;

    else
        % actual connection

        % open port
        try
            fopen(self.aser);
        catch ME,
            disp(ME.message)
            delete(self.aser)
            error(['Could not open port: ' comPort]);
        end

        % it takes several seconds before any operation could be attempted
        fprintf(1,'Attempting connection .');
        for i=1:2,
            pause(1);
            fprintf(1,'.');
        end
        fprintf(1,'\n');

        % check echo
        toSend = [0 4321 65535];
        fwrite(self.aser,toSend,'uint16');
        chk = fread(self.aser,length(toSend),'uint16');

        % exit if there was no answer
        if chk ~= toSend'
            delete(self.aser);
            error('Connection unsuccessful, please make sure that the arduino_BJB is powered on, running either srv.pde, adiosrv.pde or mororsrv.pde, and that the board is connected to the indicated serial port. You might also try to unplug and re-plug the USB cable before attempting a reconnection.');
        else
           disp('Echo test passed...') 
        end

    end

    if strcmpi(get(self.aser,'Port'),'DEMO'),
        % handle demo mode here
        pause(0.0014);
    else
        % check version
        toSend = [1 65535];
        fwrite(self.aser,toSend,'uint16');
        chk = fread(self.aser,length(toSend)*2+2,'uint8');

        % check returned value
        if chk==[0; 0; 0; 7; 255; 255],
            disp('Basic I/O Script Version 7 detected!');
        else
            delete(self.aser);
            error('Unknown Script.');
        end

        % notify successful installation
        disp('arduino_BJB successfully connected !');
    end

end