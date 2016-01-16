# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'rs_232/version'

Gem::Specification.new do |spec|
  spec.name = 'rs_232'
  spec.version = Rs232::VERSION
  spec.authors = ['Roman Lishtaba']
  spec.email = ['roman@lishtaba.com']
  spec.description = 'RS-232 cross-platform implementation as Ruby C native extension.'
  spec.summary = <<-SUMMARY
RS-232 cross-platform implementation as Ruby C native extension.
Rubygem offering simple API in order to start using Serial Port communication in your project running on Linux, Mac OS X and Windows.
  SUMMARY
  spec.homepage = 'http://www.lishtaba.com'
  spec.license = 'MIT'
  spec.files = [
    Dir.glob('ext/**/*'),
    Dir.glob('lib/**/*.rb'),
    'Rakefile', 'rs_232.gemspec',
    'Gemfile',
    'LICENSE.txt'
  ].flatten
  spec.executables = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ['lib']
  spec.extensions = Dir.glob('ext/**/extconf.rb')
  spec.add_development_dependency 'bundler', '~> 1.10'
  spec.add_development_dependency 'rake', '~> 10.0'
  spec.add_development_dependency 'rubocop', '~> 0'
  spec.add_development_dependency 'simplecov', '~> 0.9'
  spec.add_development_dependency 'rspec', '~> 3.1'
  spec.add_development_dependency 'cucumber', '~> 1.3'
  spec.add_development_dependency 'rspec_junit_formatter', '~> 0'
  spec.add_development_dependency 'yard', '~> 0.8'
  spec.add_development_dependency 'rake-compiler', '~> 0'
  spec.post_install_message = <<-MSG
  (::) You've installed binary version of the Rs-232 gem! (::)
  MSG
end
