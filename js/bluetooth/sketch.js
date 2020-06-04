let myBLE;
let sound;

function preload() {
  sound = loadSound('assets/loop.mp3');
}

function setup() {
  createCanvas(400, 400);
  sound.loop();

  // Create a p5ble class
  myBLE = new p5ble();


  // Create a 'Connect and Start Notifications' button
  const connectButton = createButton('Connect and Start Notifications')
  connectButton.mousePressed(connectAndStartNotify);

  frameRate(5);
}

function draw() {
  background("#FFF");

  let volume = map(BLEsense.accelerometer.value, 60, 180, 0, 1);
  volume = constrain(volume, 0, 1);
  sound.setVolume(volume, 0.5);

  noStroke();
  fill('red');
  circle(width/2, height/2, volume * 200);
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
  console.log('Accelerometer: ', data);
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
