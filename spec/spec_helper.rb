$LOAD_PATH.unshift File.expand_path '../../lib', __FILE__
example = File.expand_path '../../vendor/rs_232_example/lib', __FILE__
$LOAD_PATH.unshift example

require 'bundler'
require 'bundler/setup'
require 'rspec'
require 'rs_232'
require 'rs_232_example'

Dir[File.expand_path('support/**/*.rb', File.dirname(__FILE__))].each do |f|
  require f if File.file?(f)
end

RSpec.configure do |config|
  config.formatter = :documentation
end
