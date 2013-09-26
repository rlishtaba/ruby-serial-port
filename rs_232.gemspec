# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'rs_232/version'

Gem::Specification.new do |spec|
  spec.name          = "rs_232"
  spec.version       = Rs232::VERSION
  spec.authors       = ["Roman Lishtaba"]
  spec.email         = ["roman@lishtaba.com"]
  spec.description   = %q{rs-232 lib}
  spec.summary       = %q{rs-232 lib gem summary}
  spec.homepage      = ""
  spec.license       = "MIT"

  spec.files         = Dir["**/*"]
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]

  spec.extensions  = %w(ext/rs_232/extconf.rb)

  spec.add_development_dependency "bundler", "~> 1.3"
  spec.add_development_dependency "rake"
  spec.add_development_dependency "rspec", "~> 2.8.0"
  spec.add_development_dependency "cucumber", "~> 1.1.0"
  spec.add_development_dependency "rake-compiler"
  spec.add_development_dependency "pry"

  spec.post_install_message     = "You've installed the binary version of Rs-232 gem!"

end
