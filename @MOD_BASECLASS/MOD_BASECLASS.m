classdef (Abstract) MOD_BASECLASS < hgsetget
   % write a description of the class here.
       properties (Constant,Abstract)
            moduleName;
            dependencies;
       end
       properties
          dependencyHandles;
       end
       properties (Abstract)
       % define the properties of the class here, (like fields of a struct)
       end
       methods
       % methods, including the constructor are defined in this block
           function this = MOD_BASECLASS()
           end
           function delete(this)
           end
       end
       methods
           function this = onTabSelect(this,hObject,eventdata)
           end
       end
end