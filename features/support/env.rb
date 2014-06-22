require 'cucumber'
require 'rs_232'
require_relative '../../spec/support/adapter'

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# relative path location method
#
def expand_path(path)
  File.expand_path(path, File.dirname(__FILE__))
end

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# Load only if bundled console
#

unless $0 =~ /cucumber/i
  runtime = Cucumber::Runtime.new
  runtime.load_programming_language('rb')
end


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# logger impl
#

class LogFormatter < ::Logger::Formatter

  def call(severity, time, progname, msg)
    "#{format_datetime(time)}[TID:#{$$}] [EXT::#{severity}]: #{msg}\n"
  end

  private

  def format_datetime(time)
    time.strftime('%Y-%m-%d %H:%M:%S.') << "%06d " % time.usec
  end

end

def logger
  @logger ||= begin
    l           = ::Logger.new($stdout)
    l.level     = Logger::DEBUG
    l.formatter = LogFormatter.new
    l
  end
end

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

def serial_port
  if ENV['SERIAL_PORT'].nil?
    $stdout.write 'Enter serial port details: '
    ENV['SERIAL_PORT'] = $stdin.gets.chomp
  end
  ENV['SERIAL_PORT']
end

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

def adapter
  @adapter ||= Adapter::Dev.new(serial_port) do |message|
    logger.debug message
  end
end