module Rs232
  module Version
    MAJOR, MINOR, PATCH = 2, 0, 7
    STRING              = [MAJOR, MINOR, PATCH].join('.')
  end

  VERSION = Version::STRING
end
