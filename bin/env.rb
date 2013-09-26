#!/usr/bin/env ruby
require 'bundler'
require 'bundler/setup'
require 'irb'
require 'irb/completion'
require './features/support/env'

$stdout.puts 'Rs232 console started...'

IRB.start()