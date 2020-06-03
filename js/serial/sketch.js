//  an instance of the serialport library:
let serial;
// Change this to the name of your serial port here:
const portName = '/dev/cu.usbmodem14201';

function setup() {
  createCanvas(500, 600, WEBGL);
  // instantiate serial port:
  serial = new p5.SerialPort();
  // set callback for port open:
  serial.on('open', startSerial);
  // set callback for incoming data:
  serial.on('data', serialEvent);
  // open serial port:
  console.log(serial.list());
  serial.open(portName);
  // console.log(portName);
  // console.log('connected: ', serial.isConnected());
}

// callback function for when serial port opens:
function startSerial() {
  // send an initial byte
  // to get data from the microcontroller:
  serial.write('x');
  console.log('serial port opened');
}

// callback function for incoming serial data:
function serialEvent() {
  // read from port until new line:
  let message = serial.readStringUntil('\n');
  if (message != null) {
    console.log(message);
    // send a byte to the microcontroller to get new data:
    serial.write('x');
  }
}
