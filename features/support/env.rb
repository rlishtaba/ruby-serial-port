$:.unshift File.expand_path '../../../', __FILE__
require 'spec/spec_helper'

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#
unless $0 =~ /cucumber/i
  runtime = Cucumber::Runtime.new
  runtime.load_programming_language('rb')
end

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#
def serial_port
  if ENV['SERIAL_PORT'].nil?
    $stdout.write 'Enter serial port details: '
    ENV['SERIAL_PORT'] = $stdin.gets.chomp
  end
  ENV['SERIAL_PORT']
end

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#
def adapter
  @adapter ||= Rs232Example::Adapter::Dev.new(serial_port) do |message|
    logger.debug message
  end
end