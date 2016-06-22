require 'spec_helper'

describe Rs232 do
  EXPECTED_CONSTANTS = [
    :BAUD_110, :BAUD_300, :BAUD_600, :BAUD_1200,
    :BAUD_2400, :BAUD_4800, :BAUD_9600, :BAUD_19200,
    :BAUD_38400, :BAUD_57600, :BAUD_115200, :DATA_BITS_5,
    :DATA_BITS_6, :DATA_BITS_7, :DATA_BITS_8, :PAR_NONE,
    :PAR_ODD, :PAR_EVEN, :STOP_BITS_1, :STOP_BITS_3,
    :FLOW_OFF, :FLOW_HARDWARE, :FLOW_XONXOFF
  ].sort.freeze

  it 'should have an VERSION constant' do
    current_constants = Rs232::Constants.constants.sort
    expect(current_constants).to eq(EXPECTED_CONSTANTS)
  end
end
