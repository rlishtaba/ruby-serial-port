#
# Copyright (c) 2013, Ingenico Inc.
#
# Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted,
# provided that the above copyright notice and this permission notice appear in all copies.
#                                                                                                                                                                                                          *
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
# IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.
#

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

