require 'simplecov'
task :cov do
  ENV['SIMPLECOV'] = 'features'
  Rake::Task['default'].invoke
end
