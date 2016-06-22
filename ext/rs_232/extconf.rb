require 'mkmf'
require 'rbconfig'

EXTENSION_NAME = 'rs_232_native'.freeze
dir_config(EXTENSION_NAME)

if ENV['DEBUG']
  $CFLAGS << ' -DDEBUG'
  $CFLAGS << ' -g'
  $stdout.puts "compiling in debug mode... flags: #{$CFLAGS}"
end

$CFLAGS << ' -Wall -g'

$warnflags = '-Wall'

OS = case RbConfig::CONFIG['host_os'].downcase
     when /linux/
       'linux'
     when /darwin/
       'darwin'
     when /freebsd/
       'freebsd'
     when /openbsd/
       'openbsd'
     when /sunos|solaris/
       'solaris'
     when /mswin|mingw/
       'windows'
     else
       RbConfig::CONFIG['host_os'].downcase
     end

have_header('ruby.h')
have_header('stdio.h')
have_library( 'stdc++' )

if OS == 'windows'
  $VPATH << '$(srcdir)/windows'
  $INCFLAGS += ' -I$(srcdir)/windows'
  have_header('windows.h')
  have_header('fcntl.h')
  have_header('io.h')
  have_header('ruby/io.h')
  have_header('rubyio.h')
elsif %w(linux darwin).include? OS
  $VPATH << ' $(srcdir)/posix'
  $INCFLAGS += ' -I$(srcdir)/posix'
  have_header('termios.h')
  have_header('unistd.h')
  have_header('string.h')
  have_header('fcntl.h')
  have_header('errno.h')
  have_header('sys/ioctl.h')
else
  fail "RS-233 implementation wasn't been tested for #{OS} platform."
end

$objs = %w(Constants.o Port.o Rs232.o).freeze

$CFLAGS += " -DOS_#{OS.upcase}"

$stdout.puts <<-MSG

Extending with: #{$CFLAGS}

MSG

create_makefile(EXTENSION_NAME)
