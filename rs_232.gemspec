# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'rake'
require 'rs_232/version'

Gem::Specification.new do |spec|
  spec.name          = 'rs_232'
  spec.version       = Rs232::VERSION
  spec.authors       = ['Roman Lishtaba']
  spec.email         = ['roman@lishtaba.com']
  spec.description   = %q{This is a rs-232 posix implementation as a Ruby extension in C.}
  spec.summary       = %q{This is a rs-232 implementation as a Ruby extension in C.}
  spec.homepage      = 'http://www.ingenico.us'
  spec.license       = 'MIT'
  #
  spec.files         = FileList['ext/**/*', 'lib/**/*.rb', 'Rakefile', 'rs_232.gemspec', 'Gemfile', 'LICENSE.txt'].to_a
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ['lib']
  #
  spec.extensions    = FileList["ext/**/extconf.rb"]
  #
  spec.add_development_dependency 'bundler'
  spec.add_development_dependency 'rake'
  spec.add_development_dependency 'rspec'
  spec.add_development_dependency 'cucumber'
  spec.add_development_dependency 'rake-compiler'
  spec.add_development_dependency 'simplecov'
  #
  spec.post_install_message = <<-MSG
  (::) You've installed binary version of the Rs-232 gem! (::) 
  MSG
end
