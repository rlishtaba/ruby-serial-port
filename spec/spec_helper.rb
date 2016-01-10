$LOAD_PATH.unshift File.expand_path '../lib', __FILE__

require 'bundler/setup'
require 'rs_232'

Dir[File.expand_path('support/**/*.rb', File.dirname(__FILE__))].each do |f|
  require f if File.file?(f)
end

RSpec.configure do |config|
  config.color     = true
  config.formatter = :documentation
  config.include Fixtures
end
