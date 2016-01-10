require 'spec_helper'

describe Rs232 do
  it 'should have an VERSION constant' do
    expect(described_class.constants.include?(:VERSION)).to be_truthy
  end
end
