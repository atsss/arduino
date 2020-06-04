const serviceUuid = "6fbe1da7-0000-44de-92c4-bb6e04fb0212";

let aXCharacteristics;
let aYCharacteristics;
let aZCharacteristics;
let gXCharacteristics;
let gYCharacteristics;
let gZCharacteristics;
let aX;
let aY;
let aZ;
let gX;
let gY;
let gZ;
let myBLE;

let myCharacteristic;

function setup() {
  createCanvas(400, 400);
    // Create a p5ble class
  myBLE = new p5ble();

  createCanvas(600, 400);
  background("#FFF");

  // Create a 'Connect and Start Notifications' button
  const connectButton = createButton('Connect and Start Notifications')
  connectButton.mousePressed(connectAndStartNotify);

  frameRate(10);
}

function draw() {
  noStroke();
  // console.log('accelerator: ', aX, aY, aZ);
  // console.log('gyro: ', gX, gY, gZ);
}

function connectAndStartNotify() {
  // Connect to a device by passing the service UUID
  myBLE.connect(serviceUuid, gotCharacteristics);
}

// A function that will be called once got characteristics
function gotCharacteristics(error, characteristics) {
  if (error) console.log('error: ', error);

  console.log(characteristics);

  for(let i = 0; i < characteristics.length;i++){
    if(characteristics[i].uuid == BLEsense.aX.uuid){
      console.log("Got aX");
      aXCharacteristics = characteristics[i];
      myBLE.read(aXCharacteristics, 'float32', handleAX);
    } else if(characteristics[i].uuid == BLEsense.aY.uuid){
      console.log("Got aY");
      aYCharacteristics = characteristics[i];
      myBLE.read(aYCharacteristics, 'float32', handleAY);
    } else if(characteristics[i].uuid == BLEsense.aZ.uuid){
      console.log("Got aZ");
      aZCharacteristics = characteristics[i];
      myBLE.read(aZCharacteristics, 'float32', handleAZ);
    } else if(characteristics[i].uuid == BLEsense.gX.uuid){
      console.log("Got gX");
      gXCharacteristics = characteristics[i];
      myBLE.read(gZCharacteristics, 'float32', handleGX);
    } else if(characteristics[i].uuid == BLEsense.gY.uuid){
      console.log("Got gY");
      gYCharacteristics = characteristics[i];
      myBLE.read(gYCharacteristics, 'float32', handleGY);
    } else if(characteristics[i].uuid == BLEsense.gZ.uuid){
      console.log("Got gZ");
      gZCharacteristics = characteristics[i];
      myBLE.read(gZCharacteristics, 'float32', handleGZ);
    }
  }
}

function handleAX(error, value) {
  if (error) console.log('error: ', error);
  aX = floor(value * 100) / 100;
  myBLE.read(aXCharacteristics, 'float32', handleAX);
}

function handleAY(error, value) {
  if (error) console.log('error: ', error);
  aY = floor(value * 100) / 100;
  myBLE.read(aYCharacteristics, 'float32', handleAY);
}

function handleAZ(error, value) {
  if (error) console.log('error: ', error);
  aZ = floor(value * 100) / 100;
  myBLE.read(aZCharacteristics, 'float32', handleAZ);
}

function handleGX(error, value) {
  if (error) console.log('error: ', error);
  gX = floor(value * 100) / 100;
  myBLE.read(gXCharacteristics, 'float32', handleGX);
}

function handleGY(error, value) {
  if (error) console.log('error: ', error);
  gY = floor(value * 100) / 100;
  myBLE.read(gYCharacteristics, 'float32', handleGY);
}

function handleGZ(error, value) {
  if (error) console.log('error: ', error);
  gZ = floor(value * 100) / 100;
  myBLE.read(gZCharacteristics, 'float32', handleGZ);
}

const BLEsense = {
  aX: { uuid: '6fbe1da7-3001-44de-92c4-bb6e04fb0212' },
  aY: { uuid: '6fbe1da7-3002-44de-92c4-bb6e04fb0212' },
  aZ: { uuid: '6fbe1da7-3003-44de-92c4-bb6e04fb0212' },
  gX: { uuid: '6fbe1da7-3011-44de-92c4-bb6e04fb0212' },
  gY: { uuid: '6fbe1da7-3012-44de-92c4-bb6e04fb0212' },
  gZ: { uuid: '6fbe1da7-3013-44de-92c4-bb6e04fb0212' }
};
