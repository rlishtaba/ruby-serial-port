require "logger"

module Adapter::RsLogger

  class LogFormatter < ::Logger::Formatter

    def call(severity, time, progname, msg)
      "#{format_datetime(time)}[TID:#{$$}] [Rs232::#{severity}]: #{msg}\n"
    end


    private

    def format_datetime(time)
      if @datetime_format.nil?
        time.strftime("%Y-%m-%d %H:%M:%S.") << "%06d " % time.usec
      else
        time.strftime(@datetime_format)
      end
    end

  end

  def logger
    @logger ||= begin
      logger = ::Logger.new( ENV["LOG"]||$stdout )
      logger.level = ENV["DEBUG"].to_i
      logger.formatter= LogFormatter.new
      logger
    end
  end
  
  module_function :logger

end

