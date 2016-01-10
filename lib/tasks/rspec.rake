require 'rspec/core/rake_task'
desc 'Run RSpec'
RSpec::Core::RakeTask.new do |t|
  t.fail_on_error = false
  t.verbose = true
  t.rspec_opts = '--format RspecJunitFormatter  --out rspec.xml --tag ~wip'
end
