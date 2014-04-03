# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'rs_232/version'

Gem::Specification.new do |spec|
  spec.name          = 'rs_232'
  spec.version       = Rs232::VERSION
  spec.authors       = ['Roman Lishtaba']
  spec.email         = ['roman@lishtaba.com']
  spec.description   = %q{This is a rs-232 posix implementation as a Ruby extension in C.}
  spec.summary       = %q{This is a rs-232 implementation as a Ruby extension in C.}
  spec.homepage      = 'http://www.lishtaba.com'
  spec.license       = 'MIT'

  spec.files         = Dir['**/*']
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ['lib']

  spec.extensions  = %w(ext/rs_232/extconf.rb)

  spec.add_development_dependency 'bundler','~> 1.5', '>= 1.5.3'
  spec.add_development_dependency 'rake', '~> 10.1', '>= 10.1.1'
  spec.add_development_dependency 'rspec', '~> 2.14', '>= 2.14.1'
  spec.add_development_dependency 'cucumber', '~> 1.3', '>= 1.3.11'
  spec.add_development_dependency 'rake-compiler', '~> 0.9', '>= 0.9.2'
  spec.add_development_dependency 'simplecov', '~> 0.8', '>= 0.8.2'

  spec.post_install_message     = <<-MSG
  (::) You've installed binary version of the Rs-232 gem! (::) 
  MSG
end
