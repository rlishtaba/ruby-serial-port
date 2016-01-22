$LOAD_PATH.unshift File.expand_path '../../../', __FILE__
require 'rs_232'

module Communication
  def serial_port_name
    port = ENV['SERIAL_PORT']
    fail 'SERIAL_PORT env var not set' unless port
    port
  end

  def connection
    @connection ||= CommPort::Rs232.new serial_port_name
  end
end

World(Communication)
