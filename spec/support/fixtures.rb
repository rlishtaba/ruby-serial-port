require 'pathname'

module Fixtures
  def fixture_path(name)
    File.join '../fixtures', name
  end

  def absolute_fixture_path(name)
    File.expand_path fixture_path(name), File.dirname(__FILE__)
  end

  def fixture(name)
    File.read absolute_fixture_path(name)
  end

  def binary_fixture(name)
    File.open(absolute_fixture_path(name), 'rb', &:read)
  end

  def fixtures_path
    Pathname(absolute_fixture_path(''))
  end
end
