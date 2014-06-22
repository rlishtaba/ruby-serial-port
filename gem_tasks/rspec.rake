require 'rspec/core/rake_task'

# - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * -
#
desc 'Run RSpec coverage'
RSpec::Core::RakeTask.new do |t|
  t.verbose = true
end
