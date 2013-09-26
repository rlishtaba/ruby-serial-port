module Adapter::Interface

  def open?
    raise Adapter::Errors::MethodNotImplemented.new self.class.name, "open?"
  end

  def write(message)
    raise Adapter::Errors::MethodNotImplemented.new self.class.name, "write", "message<string>"
  end

  def read(bytes, blocking = false)
    raise Adapter::Errors::MethodNotImplemented.new self.class.name, "read", "bytes<integer>"
  end

  def close
    raise Adapter::Errors::MethodNotImplemented.new self.class.name, "close"
  end
end
