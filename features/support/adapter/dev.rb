class Adapter::Dev < Adapter::Generic
  attr_reader :interface

  def initialize(port, &block)
    @interface ||= CommPort::Rs232.new(port)
    connect
    $stdout.puts "*** Rs232 instance has been initialized. Build v#{CommPort::VERSION}"
    super(&block)
  end

  def connect
    @open = @interface.open
    open?
  end

  def write(bytes)
    @interface.write(bytes)
  end

  def close
    defer_reading
    @interface.close
    !open?
  end

  def flush
    @interface.flush
  end

  def open?
    @interface && !@interface.closed?
  end

  def read(count, blocking = false)
    array       = []

    bytes_count = (count == -1) ? @interface.available? : count

    if blocking
      bytes = block_io_until(count, count)
      array.push bytes if bytes
    else
      bytes_count.times do
        byte = @interface.read(1)
        array.push byte if byte
      end
    end
    array.empty? ? nil : array.join
  end

  private

  def block_io_until(count, up_to)
    while @interface.available? < count && up_to > 0
      up_to -= 1
    end
    up_to > 0
  end

  def read_io_until(count, up_to)
    until block_io_until(count, up_to)
      sleep 0.001
    end
    read(count)
  end

end

