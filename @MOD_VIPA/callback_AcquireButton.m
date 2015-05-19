function self = callback_AcquireButton( self, hObject,eventdata )
%CALLBACK_ACQUIREBUTTON Summary of this function goes here
%   Detailed explanation goes here
        % Live image
        % Continue as long as button is pressed
        bkgCounter = 0;
        while (get(self.acquireButton, 'value'))
            
            % Check to see if we need a new background
            if mod(bkgCounter,self.imgsPerBackground) == 0
                 bkgImages = self.dependencyHandles.MOD_ExternalAcquireSync.acquireBackgroundImages(3);
                 bkgImage = bkgImages(:,:,1);
                 %figure;imagesc(bkgImage);return
                 bkgCounter = 0;
                 disp('MOD_VIPA: Background Acquired');
            end
            bkgCounter = bkgCounter + 1;
            
            % Aquire image
            theImage = self.dependencyHandles.MOD_ExternalAcquireSync.acquireImages(1);
            
            img = double(theImage) - double(bkgImage);

            % Display image
            set(self.imageHandle,'CData',img');
            set(self.axes,'XLim',[0 size(img,1)]);
            set(self.axes,'YLim',[0 size(img,2)]);
            
            drawnow;
            pause(0.01);
        end

end

