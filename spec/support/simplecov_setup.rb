begin
  require 'simplecov'

  SimpleCov.root(File.expand_path(File.dirname(__FILE__) + '../../'))
  SimpleCov.start do
    add_filter '/features/'
    add_filter '/spec/'
  end

rescue LoadError
  warn("Unable to load simplecov gem")
end