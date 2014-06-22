require 'bundler'
require 'bundler/setup'
require 'rspec'
require 'rs_232'

Dir[File.expand_path('support/**/*.rb', File.dirname(__FILE__))].each do |f|
  require f if File.file?(f)
end

RSpec.configure do |config|
  config.color_enabled = true
  config.formatter = :documentation
end

load File.expand_path '../simplecov_setup.rb', __FILE__