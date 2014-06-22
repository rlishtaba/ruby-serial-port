$:.unshift File.expand_path '../../../lib', __FILE__
require 'logger'
require 'rs_232'

module Rs232Example

  module Adapter
    autoload :Generic, 'rs_232_example/adapter/generic'
    autoload :Dev, 'rs_232_example/adapter/dev'
  end

  def self.logger
    @logger ||= begin
      logger       = ::Logger.new($stdout)
      logger.level = ::Logger::DEBUG
      logger
    end
  end

end
