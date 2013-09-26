module Adapter
  autoload :RsLogger, File.expand_path("../adapter/rs_logger", __FILE__)
  autoload :Generic, File.expand_path("../adapter/generic", __FILE__)
  autoload :Dev, File.expand_path("../adapter/dev", __FILE__)
end
