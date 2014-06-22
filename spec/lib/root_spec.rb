require 'spec_helper'

describe Rs232::VERSION do

  it 'should have a VERSION constants' do
    Rs232.constants.include?(:VERSION).should be_true
  end

end