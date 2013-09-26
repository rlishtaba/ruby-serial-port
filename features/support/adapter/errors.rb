module Adapter::Errors

  class Base < StandardError
  end

  class ConnectionClosed < Base
  end

  class MethodNotImplemented < Base
    def initialize(class_name, method_name, *params)
      super "Class #{class_name} does not implement method ##{method_name}(#{params.join ', '})"
    end
  end

end
