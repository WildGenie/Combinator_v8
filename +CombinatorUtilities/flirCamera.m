classdef flirCamera < handle
    properties (Hidden = true, SetAccess = private)
        cpp_handle;
    end
    methods
        % Constructor
        function this = flirCamera()
            this.cpp_handle = init_flirCamera_mex();
        end
        % Destructor
        function delete(this)
            clear_flirCamera_mex(this.cpp_handle);
        end
        % Example method
        function output = action(this, data)
            output = action_flirCamera_mex(this.cpp_handle, data);
        end
    end
end