module Adapter
  autoload :RsLogger, File.expand_path("../adapter/rs_logger", __FILE__)
  autoload :Interface, File.expand_path("../adapter/interface", __FILE__)
  autoload :Generic, File.expand_path("../adapter/generic", __FILE__)
  autoload :Errors, File.expand_path("../adapter/errors", __FILE__)
  autoload :Dev, File.expand_path("../adapter/dev", __FILE__)
end


# * # * # * # * # * # * # * # * # * # * # * # * # * # * # * # * # * # * # * # * # * # * # * # * # * # * # * # * # * # *


def transmit(string)
  connection.tx(string)
end