let myBLE;
let sound;
let isPlayed = false;
let value = 0;
let prevValue = 0;
const targetHour = 20;
const targetMinute = 45;
const targetSecound = 00;
const ThresholdGap = 100;

function preload() {
  sound = loadSound('assets/trailer.mp3');
}

function setup() {
  createCanvas(400, 400);

  // Create a p5ble class
  myBLE = new p5ble();

  // Create a 'Connect and Start Notifications' button
  const connectButton = createButton('Connect and Start Notifications')
  connectButton.mousePressed(connectAndStartNotify);

  frameRate(2);
}

function draw() {
  background("#FFF");

  value = BLEsense.accelerometer.value;
  console.log(value);

  if(!isPlayed && hour() === targetHour && minute() === targetMinute && second() === targetSecound) {
    sound.play();

    isPlayed = true;
  }

  if(isPlayed && abs(value - prevValue) > 80) {
    sound.stop();

    isPlayed = false;
  }

  noStroke();
  fill('red');
  circle(width/2, height/2, value);
  prevValue = value;
}

function connectAndStartNotify() {
  // Connect to a device by passing the service UUID
  myBLE.connect(BLEsense.serviceUuid, gotCharacteristics);
}

// A function that will be called once got characteristics
function gotCharacteristics(error, characteristics) {
  if (error) console.log('error: ', error);
  console.log(characteristics[1].uuid);

  for(let i = 0; i < characteristics.length;i++){
    if(characteristics[i].uuid == BLEsense.accelerometer.uuid){
      console.log("Got accelerometer");
      BLEsense.accelerometer.characteristics = characteristics[i];
      // Start notifications on the characteristic by passing the characteristic
      // And a callback function to handle notifications
      myBLE.startNotifications(BLEsense.accelerometer.characteristics, handleAccelerometer);
    }
  }
}

// A function that will be called once got characteristics
function handleAccelerometer(data) {
  // console.log('Accelerometer: ', data);
  BLEsense.accelerometer.value = data;
}

var BLEsense = {
  serviceUuid : "6fbe1da7-0000-44de-92c4-bb6e04fb0212",

  accelerometer:
  {
    uuid: '6fbe1da7-3001-44de-92c4-bb6e04fb0212',
    characteristics: null,
    value: 0
  }
};

function touchStarted() {
  getAudioContext().resume();
}
